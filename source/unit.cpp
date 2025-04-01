#include "unit.hpp"
#include <iostream>

namespace path_finding
{
    /// <summary>
    /// Constructor 
    /// </summary>
    /// <param name="position"></param>
    /// <param name="path_finder"></param>
    unit::unit(const point_2d position, const pathfinder& path_finder)
        : position_(position), path_index_(0), path_finder_(&path_finder) {
    }

    /// <summary>
    /// Move unit to the given target position while avoiding the occupied position by other units 
    /// </summary>
    /// <param name="target"></param>
    /// <param name="occupied_positions"></param>
    /// <returns></returns>
    move_status unit::move(point_2d target, std::unordered_set<point_2d>& occupied_positions) {
        if (position_ == target) {
            std::cout << "Unit already at target." << '\n';
            return move_status::at_target;
        }

        // Compute path if not already set
        if (path_.empty()) {
            path_ = path_finder_->find_path(position_, target, occupied_positions);
            if (path_.empty()) {
                std::cout << "No valid path to target!" << '\n';
                return move_status::no_path;
            }
            path_index_ = 0;
        }

        // Move one step at a time
        if (path_index_ < path_.size()) {
            point_2d nextPosition = path_[path_index_];

            // Do not use occupied positions 
            if (occupied_positions.find(nextPosition) != occupied_positions.end()) {
                std::cout << "Next position is occupied! Recomputing path..." << '\n';
                path_.clear();
                return move_status::blocked;
            }

            // Remove previous position from occupied set
            occupied_positions.erase(position_);

            // Move to the next position
            position_ = nextPosition;

            // Mark new position as occupied
            occupied_positions.insert(position_);
            path_index_++;
            return move_status::moved;
        }

        return move_status::at_target;
    }

    /// <summary>
    /// Get unit's current position
    /// </summary>
    /// <returns></returns>
    point_2d unit::get_position() const { return position_; }
}
