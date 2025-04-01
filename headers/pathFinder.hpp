#pragma once

#include "../headers/point2d.hpp"
#include "../headers/battleField.hpp"

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace path_finding
{
    /// <summary>
    /// Pathfinder class calculates the shortest path between two positions using A Start algorithm
    /// While calculating the shortest path, it keeps obstacles, elevation and other units in consideration
    /// </summary>
    class pathfinder {
    public:

	    /// <summary>
	    /// Constructor
	    /// </summary>
	    /// <param name="battle_field"></param>
	    explicit pathfinder(const battle_field& battle_field);

        /// <summary>
        /// Finds the shortest path from start to goal
        /// Occupies position is used to avoid sharing the same spot between two units
        /// </summary>
        /// <param name="start"></param>
        /// <param name="goal"></param>
        /// <param name="occupied_positions"></param>
        /// <returns></returns>
        std::vector<point_2d> find_path(point_2d start, point_2d goal,
            const std::unordered_set<point_2d>& occupied_positions) const;

    private:

        /// <summary>
        /// Reference to battlefield 
        /// </summary>
        const battle_field* battle_field_;

        /// <summary>
        /// Directions to calculate neighboring points
        /// </summary>
        std::vector<point_2d> directions_;

        /// <summary>
        /// Estimates the cost from one point to another using manhattan distance
        /// because the unit can only go up, down, left or right
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        static float heuristic(const point_2d& a, const point_2d& b);

        /// <summary>
        /// Calculates the valid neighboring positions from the current point 
        /// </summary>
        /// <param name="current"></param>
        /// <param name="occupied_positions"></param>
        /// <param name="goal"></param>
        /// <returns></returns>
        std::vector<point_2d> get_neighbors(const point_2d& current,
            const std::unordered_set<point_2d>& occupied_positions,
            const point_2d& goal) const;

        /// <summary>
        /// Reconstruct the path from the given map of visited nodes and their predecessors 
        /// </summary>
        /// <param name="came_from"></param>
        /// <param name="current"></param>
        /// <returns></returns>
        static std::vector<point_2d> reconstruct_path(
            std::unordered_map<point_2d, point_2d>& came_from, point_2d current);
    };
}