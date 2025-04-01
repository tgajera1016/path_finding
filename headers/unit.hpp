#pragma once

#include "../headers/moveStatus.hpp"
#include "../headers/point2d.hpp"
#include "../headers/pathFinder.hpp"

namespace path_finding
{
    /// <summary>
    /// Unit class represents the unit's position on the battlefield grid
    /// </summary>
    class unit {
    public:

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="position"></param>
        /// <param name="path_finder"></param>
        unit(point_2d position, const pathfinder& path_finder);

        /// <summary>
        /// To move the unit to a new target position
        /// Occupied positions is used so that two units cannot occupy the same position on the battlefield grid
        /// </summary>
        /// <param name="target"></param>
        /// <param name="occupied_positions"></param>
        /// <returns></returns>
        move_status move(point_2d target, std::unordered_set<point_2d>& occupied_positions);

        /// <summary>
        /// Get current position of the unit on the battlefield grid
        /// </summary>
        /// <returns></returns>
        point_2d get_position() const;

    private:

        /// <summary>
        /// Position of the unit
        /// </summary>
        point_2d position_;

        /// <summary>
        /// Unit's path index
        /// </summary>
        size_t path_index_;

        /// <summary>
        /// Reference to pathfinder
        /// </summary>
        const pathfinder* path_finder_;

        /// <summary>
        /// Unit's path
        /// </summary>
        std::vector<point_2d> path_;
    };
}