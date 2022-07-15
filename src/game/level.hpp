#pragma once

#include <vector>

#include "tile_data.hpp"
#include "mesh.hpp"

// Level class
// This will have a vector of vector of numbers, these numbers will be the ID of the current tile

using LevelTiles = std::vector<std::vector<tile_t>>;
class Level {
public:
	// All tiles
	LevelTiles tiles{
		{5, 5, 5, 5, 4, 4},
		{4, 3, 1, 1, 1, 4, 4, 4},
		{4, 4, 4, 1, 1, 1, 1, 4, 4},
		{0, 0, 4, 1, 3, 3, 1, 1, 4},
		{4, 4, 4, 3, 3, 4, 4, 4, 4},
		{4, 1, 1, 3, 3, 4},
		{4, 4, 4, 4, 4, 4}
	};

	// Builds the levels mesh
	void buildMesh();
	// Levels mesh
	Mesh mesh;

	tile_t getTile(glm::vec2 pos);
};