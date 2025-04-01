#pragma once

#include "point2d.hpp"

namespace path_finding
{
	/// <summary>
	/// Node structure to represent the node in the A Start pathfinding graph
	/// Each node tracks
	/// 1. position on the grid
	/// 2. cost to reach from start (g_cost)
	/// 3. estimated cost from the goal (h_cost)
	/// 4. total cost (f_cost) 
	/// </summary>
	struct node {

		/// <summary>
		/// Grid location of the node
		/// </summary>
		point_2d position;

		/// <summary>
		/// Cost from start node to this current node
		/// </summary>
		float g_cost;

		/// <summary>
		/// Heuristic cost to estimate to get to the goal node
		/// </summary>
		float h_cost;

		/// <summary>
		/// Total cost 
		/// </summary>
		/// <returns></returns>
		float f_cost() const { return g_cost + h_cost; }

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="g"></param>
		/// <param name="h"></param>
		node(const point_2d pos, const float g, const float h)
			: position(pos), g_cost(g), h_cost(h) {
		}

		/// <summary>
		/// Compare nodes for the priority queue 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator>(const node& other) const {
			return f_cost() > other.f_cost();
		}
	};
}
