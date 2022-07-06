#pragma once

#include <vector>

#include "tile_data.hpp"

// Level class
// This will have a vector of vector of numbers, these numbers will be the ID of the current tile
class Level {
	std::vector<std::vector<tile_t>> tiles;
};