#pragma once

#include <vector>

#include "tile_data.hpp"
#include "mesh.hpp"

// Level class
// This will have a vector of vector of numbers, these numbers will be the ID of the current tile

using LevelTiles = std::vector<std::vector<tile_t>>;
using LevelHeightMap = std::vector<std::vector<int8_t>>;
class Level {
public:
	// Constructor
	Level(LevelTiles t, LevelHeightMap h);

	// All tiles
	LevelTiles tiles;
	// Height map
	LevelHeightMap heights;

	// Levels mesh
	Mesh mesh;

	tile_t getTile(glm::vec2 pos);
	int8_t getHeight(glm::vec2 pos);
};