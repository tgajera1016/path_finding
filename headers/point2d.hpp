#pragma once

#include <iostream>
#include <cmath>

namespace path_finding
{
    /// <summary>
    /// Class to manage 2D points (integer)
    /// </summary>
    class point_2d {
    
    public:
        
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        explicit point_2d(const int x = 0, const int y = 0) :
    	x_(x), y_(y) {}

        /// <summary>
        /// Get x coordinate of the point
        /// </summary>
        /// <returns></returns>
        int get_x() const { return x_; }

        /// <summary>
        /// Get y coordinate of the point
        /// </summary>
        /// <returns></returns>
        int get_y() const { return y_; }

        /// <summary>
        /// Distance between to points by summing the absolute differences of their coordinates (x, y)
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        int manhattan_distance(const point_2d& other) const {
            return std::abs(x_ - other.x_) + std::abs(y_ - other.y_);
        }

        /// <summary>
        /// To add two points 
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        point_2d operator+(const point_2d& other) const {
            return point_2d(x_ + other.x_, y_ + other.y_);
        }

        /// <summary>
        /// To compare two points
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        bool operator==(const point_2d& other) const {
            return x_ == other.x_ && y_ == other.y_;
        }

        /// <summary>
		/// To check if two points are not equal
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
        bool operator!=(const point_2d& other) const {
            return !(*this == other);
        }

    private:
        /// <summary>
        /// x and y component of the point
        /// </summary>
        int x_, y_;

    };
}

// Add a hash function specialization for Point2D
template <>
struct std::hash<path_finding::point_2d> {
	std::size_t operator()(const path_finding::point_2d& point) const noexcept
	{
		// Combine the hash values of x and y coordinates
		return hash<int>()(point.get_x()) ^ (hash<int>()(point.get_y()) << 1);
	}
};

