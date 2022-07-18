#include "level.hpp"

#include "level_builder.hpp"

Level::Level(LevelTiles t, LevelHeightMap h) : tiles(t), heights(h) {
	// Build mesh
	mesh = LevelBuilder::buildLevel(*this);
}

tile_t Level::getTile(glm::vec2 pos) {

	// If outside range, return air
	if (pos.y > tiles.size() - 1 || pos.y < 0)
		return 0;
	if (pos.x > tiles[pos.y].size() - 1 || pos.x < 0)
		return 0;
	// If the row is empty, return
	if (tiles[pos.y].size() == 0)
		return 0;

	return tiles[pos.y][pos.x];
}

int8_t Level::getHeight(glm::vec2 pos) {

	// If outside range, return air
	if (pos.y > heights.size() - 1 || pos.y < 0)
		return -5;
	if (pos.x > heights[pos.y].size() - 1 || pos.x < 0)
		return -5;
	// If air, return -5
	if (getTile(pos) == 0)
		return -5;
	// If the row is empty, return
	if (heights[pos.y].size() == 0)
		return -5;
	return heights[pos.y][pos.x];
}