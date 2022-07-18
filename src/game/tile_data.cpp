#include "tile_data.hpp"

std::unordered_map<std::string, tile_t> TileDataManager::nameIDs;
std::vector<TileData> TileDataManager::tiles;

void TileDataManager::initialise() {
	// Add default tiles

	// TODO: store height of tile seperately so i dont have to keep repeating myself!!!!!!!!!!!!!!!!
	// Thats what I'm gonna work on tomorrow, then I'm gonna add entites
	addTilesData({
		{"Void",       { TileColor::White, TileColor::Black, 63 }},
		{"Grass",      { TileColor::Lime, TileColor::Green, 24 }, { TileColor::Lime, TileColor::Purple, 25 }},
		{"Wall",       { TileColor::LightGray, TileColor::Gray, 0 }},
		{"Metal",      { TileColor::LightGray, TileColor::Gray, 1 }},
		{"Grating",    { TileColor::LightGray, TileColor::Gray, 26 }}

		// MAYBE Special stuff
		//{"Player", 0, TileColor::Orange,    TileColor::Black,  16, 16},
		//{"Box",    0, TileColor::Orange,    TileColor::Purple, 8,  8}
	});
}


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


TileData TileDataManager::getTileData(const tile_t& id) {
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

TileData TileDataManager::getTileData(const std::string& name) {
	return getTileData(getIdFromName(name));
}

tile_t TileDataManager::getIdFromName(const std::string& name) {
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