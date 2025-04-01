#pragma once

#include "../headers/point2d.hpp"
#include "../headers/battleField.hpp"
#include "../headers/pathFinder.hpp"
#include <windows.h>

namespace path_finding
{
	/// <summary>
	/// Battlefield renderer that uses windows console buffer for double buffering
	/// </summary>
	class battle_field_renderer {
	public:

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="battle_field"></param>
		explicit battle_field_renderer(const battle_field& battle_field);

		/// <summary>
		/// Update the rendering using given unit positions
		/// </summary>
		/// <param name="unit_positions"></param>
		void update(const std::unordered_set<point_2d>& unit_positions);

	private:

		/// <summary>
		/// Screen buffer
		/// </summary>
		HANDLE screen_buffer_;

		/// <summary>
		/// Character info buffer to set the color to each of the character to be displayed on the console 
		/// </summary>
		std::vector<CHAR_INFO> char_info_buffer_;

		/// <summary>
		/// Battlefield grid
		/// </summary>
		std::vector<std::vector<tile_type>> battlefield_grid_;

		/// <summary>
		/// Width and height for the screen buffer
		/// </summary>
		int screen_buffer_width_, screen_buffer_height_;

		/// <summary>
		/// Write given character with color to a specific x, y location in the char buffer
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="ch"></param>
		/// <param name="color"></param>
		void write_char_buffer(int x, int y, char ch, WORD color);
	};
}
