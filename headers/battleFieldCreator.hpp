#pragma once

#include "../headers/battleField.hpp"

namespace path_finding
{
	/// <summary>
	/// Battlefield creator based on the user input
	/// </summary>
	class battle_field_creator {
	public:

		/// <summary>
		/// Create battlefield based on the user input
		/// </summary>
		static battle_field create();
	};
}
