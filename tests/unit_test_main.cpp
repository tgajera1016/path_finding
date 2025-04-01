#include <gtest/gtest.h>
#include "../headers/pathFinder.hpp"
#include "../headers/battleField.hpp"
#include "../headers/point2d.hpp"

using namespace path_finding;

namespace path_finding_unit_tests
{
	/// <summary>
	/// To create a battlefield with given dimensions but no units or terrains
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	battle_field create_simple_battlefield(const int width, const int height) {
		battle_field bf;
		bf.generate_random_field(width, height, 0, 0);
		return bf;
	}

	/// <summary>
	/// Test case: only one tile where start is the target
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, one_tile_test) {
		const battle_field bf = create_simple_battlefield(1, 1);
		const pathfinder pf(bf);

		const point_2d pos(0, 0);
		const std::unordered_set<point_2d> occupied;

		const auto path = pf.find_path(pos, pos, occupied);
		EXPECT_TRUE(path.empty());
	}

	/// <summary>
	/// Test case: start and target both are same
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, start_is_target_test) {
		const battle_field bf = create_simple_battlefield(5, 5);
		const pathfinder pf(bf);

		const point_2d start(2, 2);
		const point_2d target(2, 2);
		const std::unordered_set<point_2d> occupied;

		const auto path = pf.find_path(start, target, occupied);

		EXPECT_TRUE(path.empty());
	}

	/// <summary>
	/// Test case: reachable target
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, can_reach_target_test) {
		const battle_field bf = create_simple_battlefield(5, 5);
		const pathfinder pf(bf);

		const point_2d start(0, 0);
		const point_2d target(4, 4);
		const std::unordered_set<point_2d> occupied;

		const auto path = pf.find_path(start, target, occupied);

		ASSERT_FALSE(path.empty());
		EXPECT_EQ(path.back(), target);
	}

	/// <summary>
	/// Test case: no path
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, cannot_reach_target_test) {
		const battle_field bf = create_simple_battlefield(5, 5);
		const pathfinder pf(bf);

		// Block every path to (4,4)
		std::unordered_set<point_2d> occupied;
		occupied.insert(point_2d(3, 4));
		occupied.insert(point_2d(4, 3));
		occupied.insert(point_2d(3, 3));

		const point_2d start(0, 0);
		const point_2d target(4, 4);

		const auto path = pf.find_path(start, target, occupied);

		EXPECT_TRUE(path.empty());
	}

	/// <summary>
	/// Test case: Path with occupied neighbors
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, avoid_occupied_tiles_test) {
		const battle_field bf = create_simple_battlefield(5, 5);
		const pathfinder pf(bf);

		std::unordered_set<point_2d> occupied;
		occupied.insert(point_2d(1, 0));
		occupied.insert(point_2d(1, 1));
		occupied.insert(point_2d(1, 2));

		const point_2d start(0, 0);
		const point_2d target(2, 2);

		const auto path = pf.find_path(start, target, occupied);

		ASSERT_FALSE(path.empty());
		EXPECT_EQ(path.back(), target);
		bool contains_occupied = false;
		for (const auto& p : path) {
			if (occupied.count(p) > 0) {
				contains_occupied = true;
				break;
			}
		}
		EXPECT_FALSE(contains_occupied);
	}

	/// <summary>
	/// Target is occupied but still reachable
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, target_occupied_by_another_unit_test) {
		const battle_field bf = create_simple_battlefield(5, 5);
		const pathfinder pf(bf);

		const point_2d start(0, 0);
		const point_2d target(2, 2);
		std::unordered_set<point_2d> occupied;
		occupied.insert(point_2d(1, 1));
		occupied.insert(point_2d(2, 1));
		occupied.insert(point_2d(1, 2));

		const auto path = pf.find_path(start, target, occupied);

		EXPECT_FALSE(path.empty());
		EXPECT_EQ(path.back(), target);
	}

	/// <summary>
	/// Fully blocked grid
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	TEST(path_finding_unit_tests, fully_blocked_grid_test) {
		const battle_field bf = create_simple_battlefield(3, 3);
		const pathfinder pf(bf);

		const point_2d start(0, 0);
		const point_2d target(2, 2);
		std::unordered_set<point_2d> occupied;
		occupied.insert(point_2d(0, 1));
		occupied.insert(point_2d(0, 2));
		occupied.insert(point_2d(1, 0));
		occupied.insert(point_2d(1, 1));
		occupied.insert(point_2d(1, 2));
		occupied.insert(point_2d(2, 0));
		occupied.insert(point_2d(2, 1));

		const auto path = pf.find_path(start, target, occupied);
		EXPECT_TRUE(path.empty());
	}



}
