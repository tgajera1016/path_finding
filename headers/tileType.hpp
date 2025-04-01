#pragma once

namespace path_finding
{
    /// <summary>
    /// Tile type enumerator to identify each tiles in the grid (battlefield)
    /// </summary>
    enum class tile_type
    {
         walkable = -1, 
		 start = 0, 
		 elevated = 3, 
		 target = 8
    };
}
