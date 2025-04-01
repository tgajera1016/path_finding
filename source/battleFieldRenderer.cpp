#include "../headers/battleFieldRenderer.hpp"

#include <sstream>
#include <windows.h>

namespace path_finding
{
	/// <summary>
	/// Constructor to initialize the screen buffer
	/// </summary>
	/// <param name="battle_field"></param>
	battle_field_renderer::battle_field_renderer(const battle_field& battle_field)
	{
		// Get the battlefield grid's size
		battlefield_grid_ = battle_field.get_battlefield_grid();
		const size_t battlefield_grid_width = battlefield_grid_.empty() ? 0 : battlefield_grid_[0].size();
		const size_t battlefield_grid_height = battlefield_grid_.size();

		// Screen buffer is twice the size of grid because of the space between each tile
		// +2 to accommodate the left and right border characters
		screen_buffer_width_ = static_cast<int>(battlefield_grid_width * 2 + 2);
		screen_buffer_height_ = static_cast<int>(battlefield_grid_height + 2); // top and bottom borders

		// Initialize char info buffer to draw colorful characters
		char_info_buffer_.resize(screen_buffer_width_ * screen_buffer_height_);

		// Create a secondary screen buffer
		screen_buffer_ = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0,
			nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr);

		SetConsoleActiveScreenBuffer(screen_buffer_);
	}

	/// <summary>
	/// Draw battlefield grid using updated unit positions
	/// </summary>
	/// <param name="unit_positions"></param>
	void battle_field_renderer::update(const std::unordered_set<point_2d>& unit_positions)
	{
		// Clear buffer with default char + color
		std::fill(char_info_buffer_.begin(), char_info_buffer_.end(), CHAR_INFO{ {' '}, 7 });

		const int grid_width = static_cast<int>(battlefield_grid_[0].size());
		const int grid_height = static_cast<int>(battlefield_grid_.size());

		// Draw top border
		write_char_buffer(0, 0, '+', 7);
		for (int i = 0; i < grid_width * 2; ++i)
			write_char_buffer(i + 1, 0, '-', 7);
		write_char_buffer(grid_width * 2 + 1, 0, '+', 7);

		// Grid contents
		for (int y = 0; y < grid_height; ++y) {
			// Left border
			write_char_buffer(0, y + 1, '|', 7); 
			for (int x = 0; x < grid_width; ++x) {
				point_2d pos(x, y);
				const int screen_x = x * 2 + 1;
				char ch = ' ';
				WORD color = 7;

				if (unit_positions.find(pos) != unit_positions.end()) {
					ch = 'U';
					color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // Yellow
				}
				else {
					switch (battlefield_grid_[y][x]) {
					case tile_type::start:
						//ch = '0';
						color = FOREGROUND_GREEN | FOREGROUND_RED;
						break;
					case tile_type::target:
						ch = 'X';
						color = FOREGROUND_RED | FOREGROUND_INTENSITY;
						break;
					case tile_type::elevated:
						ch = '*';
						color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
						break;
					case tile_type::walkable:
						ch = ' ';
						color = 7;
						break;
					default:
						ch = '?';
						color = 7;
						break;
					}
				}
				// Character
				write_char_buffer(screen_x, y + 1, ch, color);
				// Spacing
				write_char_buffer(screen_x + 1, y + 1, ' ', color);
			}
			// Right border
			write_char_buffer(grid_width * 2 + 1, y + 1, '|', 7); 
		}

		// Bottom border
		write_char_buffer(0, grid_height + 1, '+', 7);
		for (int i = 0; i < grid_width * 2; ++i)
			write_char_buffer(i + 1, grid_height + 1, '-', 7);
		write_char_buffer(grid_width * 2 + 1, grid_height + 1, '+', 7);

		// Flush to console
		const COORD buffer_size = { static_cast<SHORT>(screen_buffer_width_), static_cast<SHORT>(screen_buffer_height_) };
		const COORD buffer_coordinates = { 0, 0 };
		SMALL_RECT write_region = { 0, 0, static_cast<SHORT>(screen_buffer_width_ - 1), static_cast<SHORT>(screen_buffer_height_ - 1) };
		WriteConsoleOutputA(screen_buffer_, char_info_buffer_.data(), buffer_size, buffer_coordinates, &write_region);
	}

	/// <summary>
	/// Write given character with color to a specific x, y location in the char buffer
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="ch"></param>
	/// <param name="color"></param>
	void battle_field_renderer::write_char_buffer(const int x, const int y, const char ch, const WORD color)
	{
		if (x < 0 || y < 0 || x >= screen_buffer_width_ || y >= screen_buffer_height_) return;
		const auto char_buffer_index = y * screen_buffer_width_ + x;
		char_info_buffer_[char_buffer_index].Char.AsciiChar = ch;
		char_info_buffer_[char_buffer_index].Attributes = color;
	}
}
