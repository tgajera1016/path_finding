#pragma once

#include <vector>
#include <string>
#include "../headers/point2d.hpp"
#include "../headers/tileType.hpp"

namespace path_finding
{
    /// <summary>
    /// Battlefield class to represent a grid of tiles
    /// </summary>
    class battle_field {
    public:

        /// <summary>
        /// Constructor to initialize the field
        /// </summary>
        battle_field();

        /// <summary>
        /// A way to create a battlefield (grid) using json file 
        /// </summary>
        /// <param name="json_filename"></param>
        void load_from_json(const std::string& json_filename);

        /// <summary>
        /// A way to randomly generate a battlefield grid 
        /// </summary>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="number_of_units"></param>
        /// <param name="number_of_terrains"></param>
        void generate_random_field(int width, int height, int number_of_units, int number_of_terrains);

        /// <summary>
        /// Find out whether the given tile position is walkable or not
        /// </summary>
        /// <param name="position"></param>
        /// <returns></returns>
        bool is_walkable(point_2d position) const;

        /// <summary>
        /// Generate random 2D point
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        static point_2d generate_random_point(point_2d min, point_2d max);

        /// <summary>
        /// To access the battlefield grid
        /// </summary>
        /// <returns></returns>
        std::vector<std::vector<tile_type>> get_battlefield_grid() const { return grid_; }

        /// <summary>
        /// Get the start position of the units
        /// </summary>
        /// <returns></returns>
        std::vector<point_2d>& get_start_positions() { return start_positions_; }

        /// <summary>
        /// Get target position of the units
        /// </summary>
        /// <returns></returns>
        std::vector<point_2d>& get_target_positions() { return target_positions_; }

    private:

        /// <summary>
        /// Width and height of the grid (battlefield)
        /// </summary>
        int width_, height_;

        /// <summary>
        /// Battlefield grid
        /// </summary>
        std::vector<std::vector<tile_type>> grid_;

        /// <summary>
        /// Unit start positions
        /// </summary>
        std::vector<point_2d> start_positions_;

        /// <summary>
        /// Unit target position
        /// </summary>
        std::vector<point_2d> target_positions_;
    };
}
