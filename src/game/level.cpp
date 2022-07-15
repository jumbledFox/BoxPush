#include "level.hpp"

#include "level_builder.hpp"

void Level::buildMesh() {
	mesh = LevelBuilder::buildLevel(*this);
}

tile_t Level::getTile(glm::vec2 pos) {
	if (pos.y > tiles.size() - 1 || pos.y < 0) {
		return 0;
	}
	if (pos.x > tiles[pos.y].size() - 1 || pos.x < 0) {
		return 0;
	}

	return tiles[pos.y][pos.x];
}