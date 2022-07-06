#include "tile_data.hpp"

TileDataManager::TileDataManager() { }


void TileDataManager::addTileData(const TileData& tile) {
	// Add the tile to tiles
	tiles.push_back(tile);

	// Set the ID of the tile
	unsigned int lastElement = tiles.size() - 1;
	tiles[lastElement].id = lastElement;
	// Add tile name to nameIDs
	nameIDs.insert({ tile.name, lastElement });
}

void TileDataManager::addTilesData(const std::vector<TileData>& tileV) {
	// For every tile in the vector...
	for (const auto& t : tileV)
		// Add it!!
		addTileData(t);
}


TileData TileDataManager::getTileData(const tile_t& id) const {
	// If the ID is in range
	if (int(id) < int(tiles.size())) {
		// Return the voxel of ID
		return tiles[id];
	}
	else {
		// Oops!
		std::cerr << "Error! Tried to get tile of unknown ID " << int(id) << "!\n";
		// Return the error voxel
		return tiles[0];
	}
}

TileData TileDataManager::getTileData(const std::string& name) const {
	return getTileData(getIdFromName(name));
}

tile_t TileDataManager::getIdFromName(const std::string& name) const {
	// If the name is found in the names map
	if (nameIDs.find(name) != nameIDs.end()) {
		// Return the ID
		return nameIDs.at(name);
	}
	else {
		// Oops!
		std::cout << "Error! Tried to get tile of unknown name '" << name << "'!\n";
		// Return the error voxel
		return 0;
	}
}