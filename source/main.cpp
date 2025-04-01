#include <filesystem>

#include "../headers/unit.hpp"
#include "../headers/point2d.hpp"
#include "../headers/pathFinder.hpp"
#include "../headers/battleField.hpp"
#include "../headers/battleFieldCreator.hpp"
#include "../headers/battleFieldRenderer.hpp"

#include <iostream>
#include <sstream>
#include <thread>

// Add path_finding namespace used for this project
using namespace path_finding;

/// <summary>
/// Main entry point of an application
/// </summary>
/// <returns></returns>
int main() {
	try {

		// Create a battlefield based on user input
		auto battle_field = battle_field_creator::create();

		// Get unit start positions and target positions from battlefield
		const auto& start_positions = battle_field.get_start_positions();
		const auto& target_positions = battle_field.get_target_positions();

		// Ensure valid data
		if (start_positions.empty() || target_positions.empty()) {
			std::cerr << "Error: No valid start or target positions found in JSON!" << '\n';
			return -1;
		}

		// Initialize pathfinder 
		pathfinder path_finder(battle_field);

		// Create units dynamically based on JSON start positions
		std::vector<unit> units;
		std::unordered_set<point_2d> occupied_positions;

		for (const auto& startPos : start_positions) {
			units.emplace_back(startPos, path_finder);
			occupied_positions.insert(startPos);
		}

		// Use only one target for all the units 
		const auto target = target_positions[0];
		battle_field_renderer battle_field_renderer(battle_field);

		// Update the display to display the setup 
		battle_field_renderer.update(occupied_positions);

		// Game loop for unit movement
		while (true) {

			// Mark movement flag to be no movement 
			bool movementHappened = false;

			// Update movement flag if any unit has moved
			for (auto& unit : units)
				if (unit.move(target, occupied_positions) == move_status::moved)
					movementHappened = true;

			// Update the display 
			battle_field_renderer.update(occupied_positions);

			if (!movementHappened) {
				std::cout << "All units reached their targets!" << '\n';
				break;
			}

			// Slow down for effect
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}

	}
	catch (const std::exception& e) {
		std::cout << "An error occurred: " << e.what();
		getchar();
		return 1;
	}

	getchar();
	return 0;
}