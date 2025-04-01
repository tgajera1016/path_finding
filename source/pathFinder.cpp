#include "../headers/node.hpp"
#include "../headers/pathFinder.hpp"
#include <queue>
#include <unordered_map>

namespace path_finding {

    /// <summary>
    /// Constructor to initialize battlefield reference and predefine directions to calculate neighboring nodes
    /// </summary>
    /// <param name="battle_field"></param>
    pathfinder::pathfinder(const battle_field& battle_field) :
	battle_field_(&battle_field)
    {
        // Predefine directions into the vector
        directions_.clear();
        directions_.emplace_back(0, -1);    // Up
        directions_.emplace_back(0, 1);     // Down
		directions_.emplace_back(-1, 0);    // Left
        directions_.emplace_back(1, 0);     // Right
    }

    /// <summary>
    /// To find the shortest path from start to goal while avoiding occupied positions by other units 
    /// </summary>
    /// <param name="start"></param>
    /// <param name="goal"></param>
    /// <param name="occupied_positions"></param>
    /// <returns></returns>
    std::vector<point_2d> pathfinder::find_path(point_2d start, point_2d goal,
        const std::unordered_set<point_2d>& occupied_positions) const
    {
        // To keep track of visited nodes
        std::unordered_set<point_2d> visited;

        // To keep track of the cost from start to each node
        std::unordered_map<point_2d, float> g_score;

        // To keep track of the predecessors
        std::unordered_map<point_2d, point_2d> came_from;

        // Priority queue 
        std::priority_queue<node, std::vector<node>, std::greater<node>> open_set;

        // Set initial cost from start to itself as 0
        g_score[start] = 0;

        // Add the start node to the open set with g = 0, and h = estimated distance to goal
        open_set.emplace(start, 0, heuristic(start, goal));

        // Loop: continue until there are no more nodes to explore
        while (!open_set.empty()) {

            // Get the node with the lowest total cost (f = g + h)
            node current_node = open_set.top();
            open_set.pop();

            // Reconstruct the path by walking back through came_from map if the goal is reached
            if (current_node.position == goal) {
                return reconstruct_path(came_from, goal);
            }

            // Avoid going back to already visited nodes
            visited.insert(current_node.position);

            // Check all valid neighboring nodes of the current node
            const auto neighbours = get_neighbors(current_node.position, occupied_positions, goal);
            for (const auto& neighbor : neighbours) {

                // Continue if the neighbour is already visited
                if (visited.find(neighbor) != visited.end()) continue;

                // Tentative g-score is the cost from start to neighbor through current
                // Each move has cost of 1
                const float tentative_g_score = g_score[current_node.position] + 1;

                // If neighbor not yet in g_score, or a better path is found
                if (!g_score.count(neighbor) || tentative_g_score < g_score[neighbor]) {
                    // Record this path as the best so far
                    came_from[neighbor] = current_node.position;
                    g_score[neighbor] = tentative_g_score;

                    // Calculate heuristic cost from neighbor to goal
                    float h = heuristic(neighbor, goal);

                    // Add neighbor to open set with updated scores
                    open_set.emplace(neighbor, tentative_g_score, h);
                }
            }
        }

        return {}; // No path found
    }

    /// <summary>
    /// Calculates heuristic estimates between two positions using manhattan distance 
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    float pathfinder::heuristic(const point_2d& a, const point_2d& b)
    {
        return static_cast<float>(a.manhattan_distance(b));
    }

    /// <summary>
    /// Get all the valid neighbours from the current position.
    /// Neighbour must be walkable and not occupied or target
    /// </summary>
    /// <param name="current"></param>
    /// <param name="occupied_positions"></param>
    /// <param name="goal"></param>
    /// <returns></returns>
    std::vector<point_2d> pathfinder::get_neighbors(const point_2d& current,
        const std::unordered_set<point_2d>& occupied_positions,
        const point_2d& goal) const {

        std::vector<point_2d> neighbors;
        for (const auto& dir : directions_) {
            point_2d neighbor = current + dir;
            const auto isOccupied = occupied_positions.find(neighbor) != occupied_positions.end();
            if (battle_field_->is_walkable(neighbor) &&
                (!isOccupied || neighbor == goal)) {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    /// <summary>
    /// Reconstruct the path by walking back through came_from map if the goal is reached
    /// </summary>
    /// <param name="came_from"></param>
    /// <param name="current"></param>
    /// <returns></returns>
    std::vector<point_2d> pathfinder::reconstruct_path(std::unordered_map<point_2d, point_2d>& came_from,
        point_2d current)
    {
        std::vector<point_2d> path;

        // Back track from the goal to the start and add the nodes into path vector
        while (came_from.find(current) != came_from.end()) {
            path.push_back(current);
            current = came_from[current];
        }

        // Reverse the vector to correct the path from start to goal/target
        std::reverse(path.begin(), path.end());

        // Return the correct path
        return path;
    }
}
