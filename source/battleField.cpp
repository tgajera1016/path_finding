#include "../headers/battleField.hpp"

#include <random>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <nlohmann/json.hpp>

/// <summary>
/// Namespace to use json library
/// </summary>
using json = nlohmann::json;

namespace path_finding
{
    /// <summary>
    /// Constructor to initialize members 
    /// </summary>
    battle_field::battle_field() :
        width_(0), height_(0) {
        // Default the entire grid is walkable
        grid_.resize(height_, std::vector(width_, tile_type::walkable));
    }

    /// <summary>
    /// This method loads the json file
    /// 1. Extracts canvas width and height
    /// 2. Extracts tile width and height
    /// 3. Calculate the width and height of the grid and resize it 
    /// 4. Create a grid based on the new width and height
    /// 5. Use the data from the json to assign proper information to each tiles in a grid
    /// </summary>
    /// <param name="json_filename"></param>
    void battle_field::load_from_json(const std::string& json_filename) {

        // Check for the file
        std::ifstream file(json_filename);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file: " + json_filename);

        // Read map data
        json map_data;
        file >> map_data;

        // Extract battlefield dimensions from "canvas"
        auto canvas_width_int = 0;
        auto canvas_height_int = 0;
        auto canvas = map_data["canvas"];
        if (canvas != NULL )
        {
            // Canvas width
            auto canvas_width = canvas["width"];
            if (canvas_width != NULL)
                canvas_width_int = static_cast<int>(canvas_width);

            // Canvas height
            auto canvas_height = canvas["height"];
            if (canvas_height != NULL)
                canvas_height_int = static_cast<int>(canvas_height);

            // Check for width and height
            if (canvas_width_int <= 0 || canvas_height_int <= 0)
            {
                std::stringstream ss;
                ss << "Invalid canvas size: (" << canvas_width_int << ", " << canvas_height_int << ")";
                throw std::runtime_error(ss.str());
            }
        }

        // Extract tile dimensions from "tilesets"
        auto tile_width_int = 0;
        auto tile_height_int = 0;
        auto tile_sets = map_data["tilesets"];
        if (tile_sets != NULL)
        {
            auto tile_set = tile_sets[0];
            if (tile_set != NULL)
            {
                // Tile width
                auto tile_width = tile_set["tilewidth"];
                if (tile_width != NULL)
                    tile_width_int = static_cast<int>(tile_width);

                // Tile height
                auto tile_height = tile_set["tileheight"];
                if (tile_height != NULL)
                    tile_height_int = static_cast<int>(tile_height);

                // Check for width and height
                if (tile_width_int <= 0 || tile_height_int <= 0)
                {
                    std::stringstream ss;
                    ss << "Invalid tile size: (" << tile_width_int << ", " << tile_height_int << ")";
                    throw std::runtime_error(ss.str());
                }
            }
        }

        // Calculate the grid size
        width_ = canvas_width_int / tile_width_int;
        height_ = canvas_height_int / tile_height_int; 

        // Resize the grid (height x width)
        grid_.resize(height_);
        for (auto& row : grid_) {
            row.resize(width_, tile_type::walkable);
        }

        // Load battlefield data into the grid
        const auto& layer_data = map_data["layers"][0]["data"];
        if (layer_data.is_array()) {
            for (size_t i = 0; i < layer_data.size(); ++i) {
                int x = static_cast<int>(i) % width_;
                int y = static_cast<int>(i) / width_;
                int type = layer_data[i];
                auto tile_type = tile_type::walkable;
                switch (type)
                {
					case 0:
                        tile_type = tile_type::start;
                        break;
                    case 8:
                        tile_type = tile_type::target;
                        break;
                    case 3:
                        tile_type = tile_type::elevated;
                        break;
                    default:
                        break;
                }

                if (tile_type == tile_type::start)
                    start_positions_.emplace_back(x, y);
                if (tile_type == tile_type::target)
                    target_positions_.emplace_back(x, y);

                grid_[y][x] = tile_type;
            }
        }
    }

    /// <summary>
    /// A way to randomly generate a battlefield grid (there will be only one target for all the units)
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <param name="number_of_units"></param>
    /// <param name="number_of_terrains"></param>
    void battle_field::generate_random_field(int width, int height, int number_of_units, int number_of_terrains)
    {
        // Check for the valid width and height for the battlefield grid
        if (width <= 0 || height <= 0)
        {
            std::stringstream ss;
            ss << "Invalid battlefield grid size: (" << width << ", " << height << ")";
            throw std::runtime_error(ss.str());
        }

        auto grid_size = width * height;
        // Check for number of units
        if (number_of_units >= grid_size)
        {
            std::stringstream ss;
            ss << "Entered number of units are more than battlefield size";
            throw std::runtime_error(ss.str());
        }

        // Check for number of terrains
        if (number_of_terrains >= grid_size)
        {
            std::stringstream ss;
            ss << "Entered number of terrains are more than battlefield size";
            throw std::runtime_error(ss.str());
        }

        // Set member variables
        width_ = width;
        height_ = height;

        // Create a walkable grid
        grid_.resize(height);
        for (auto& row : grid_) {
            row.resize(width, tile_type::walkable);
        }

        auto min_point = point_2d(0, 0);
        auto max_point = point_2d(width - 1, height - 1);

        // Add target (only one target supported)
        const auto target = generate_random_point(min_point, max_point);
        grid_[target.get_y()][target.get_x()] = tile_type::target;
        target_positions_.push_back(target);

        // Add number of terrains
        auto terrain_positions = std::unordered_set<point_2d>();
        auto number_of_terrain_counter = 0;
        while (number_of_terrain_counter < number_of_terrains)
        {
            // Randomly generated new point on the grid 
            const auto new_point = generate_random_point(min_point, max_point);

            // Add a new position as terrains position when
            // 1. A tile is not a terrain
            // 3. Not a target
            if (terrain_positions.find(new_point) == terrain_positions.end() &&
                new_point != target)
            {
                terrain_positions.emplace(new_point);
                grid_[new_point.get_y()][new_point.get_x()] = tile_type::elevated;
                number_of_terrain_counter++;
            }
        }

        // Add number of units
        auto number_of_unit_counter = 0;
        auto unit_positions = std::unordered_set<point_2d>();
        while (number_of_unit_counter < number_of_units)
        {
            // Randomly generated new point on the grid 
            const auto new_point = generate_random_point(min_point, max_point);

            // Add a new position as unit position when
			// 1. Not a terrain
			// 2. Not a target
            // 3. Not occupied by unit
            if (unit_positions.find(new_point) == unit_positions.end() &&
                terrain_positions.find(new_point) != terrain_positions.end() &&
                new_point != target)
            {
                unit_positions.emplace(new_point);
                grid_[new_point.get_y()][new_point.get_x()] = tile_type::start;
                start_positions_.push_back(new_point);
                number_of_unit_counter++;
            }
        }
    }

    /// <summary>
    /// Check whether given position on the battlefield is walkable or not
    /// </summary>
    /// <param name="position"></param>
    /// <returns></returns>
    bool battle_field::is_walkable(const point_2d position) const {

        // Extract x and y component of the given position
        const auto x = position.get_x();
        const auto y = position.get_y();

        // Check the position is within the canvas/grid size
        if (x < 0 || x >= width_ || y < 0 || y >= height_) {
            return false;
        }

        // Allow walkable, start, and target positions
        const auto tile_type = grid_[y][x];
        return tile_type == tile_type::start ||
            tile_type == tile_type::target ||
            tile_type == tile_type::walkable;
    }

    point_2d battle_field::generate_random_point(point_2d min, point_2d max)
    {
        std::random_device rd;              
        std::mt19937 gen(rd());

        // Randomly generate x and y components 
        std::uniform_int_distribution x_dist(min.get_x(), max.get_x());
        std::uniform_int_distribution y_dist(min.get_y(), max.get_y());
        return point_2d(x_dist(gen), y_dist(gen));
    }
} 
