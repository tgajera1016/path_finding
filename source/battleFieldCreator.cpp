#include "../headers/battleFieldCreator.hpp"

#include <filesystem>
#include <sstream>

namespace path_finding
{
	/// <summary>
	/// Create battlefield based on the user input
	/// </summary>
	battle_field battle_field_creator::create()
	{
		// Ask for grid generator selection
		auto grid_generator_selection = 0;
		std::cout << "[1] Load default JSON file " << "\n";
		std::cout << "[2] Generate Randomly " << "\n";
		std::cout << "Enter your option to generate a battlefield: ";
		std::cin >> grid_generator_selection;

		// Check for entered selection
		if (grid_generator_selection <= 0 || grid_generator_selection >= 3)
			throw std::runtime_error("Invalid input.");

		// Create battlefield based on the selection
		battle_field battle_field;
		switch (grid_generator_selection)
		{
		case 1:
			{
				// Load battlefield configuration from a JSON file
				std::string config_file = "../resources/tile_set_woodland_1.json";
				if (!std::filesystem::exists(config_file))
					throw std::runtime_error("Resource file not found: " + config_file);
				battle_field.load_from_json(config_file);
				break;
			}
		case 2:
			{
			// Randomly create battlefield grid
			auto battlefield_width = 0;
			std::cout << "Enter battlefield width: ";
			std::cin >> battlefield_width;

			// Check for width
			if (battlefield_width <= 0)
				throw std::runtime_error("Invalid input.");

			auto battlefield_height = 0;
			std::cout << "Enter battlefield height: ";
			std::cin >> battlefield_height;

			// Check for height
			if (battlefield_height <= 0)
				throw std::runtime_error("Invalid input.");

			auto number_of_units = 0;
			std::cout << "Enter number of units: ";
			std::cin >> number_of_units;

			auto number_of_terrains = 0;
			std::cout << "Enter number of terrains: ";
			std::cin >> number_of_terrains;

			battle_field.generate_random_field(battlefield_width, battlefield_height, number_of_units, number_of_terrains);
			break;
			}
			
		default:
			throw std::runtime_error("Invalid input.");
		}
		return battle_field;
	}
}
