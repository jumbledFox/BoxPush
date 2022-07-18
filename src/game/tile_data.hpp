#pragma once

#include <iostream>
#include <stdint.h>
#include <vector>
#include <unordered_map>

// Data for tiles, i.e. if its raised up or not, its colors, name, and ID

using tile_t = uint8_t;

// Color enum
enum class TileColor : int {
	Black = 0,
	Purple = 1,
	Red = 2,
	Orange = 3,
	Yellow = 4,
	Lime = 5,
	Green = 6,
	DarkGreen = 7,
	DarkBlue = 8,
	Blue = 9,
	LightBlue = 10,
	Cyan = 11,
	White = 12,
	LightGray = 13,
	Gray = 14,
	DarkGray = 15
};

struct TextureData {
	TileColor foreCol; // Color that will replace white
	TileColor backCol; // Color that will replace black
	uint8_t id;
};

struct TileData {
	tile_t id = 0;
	std::string name;
	TextureData top;
	TextureData side;

	TileData(std::string name, TextureData top, TextureData side) :
		name(name), top(top), side(side) {}

	TileData(std::string name, TextureData t) :
		name(name), top(t), side(t) {}
};


namespace TileDataManager {
	// Initialise stuff
	void initialise();

	// Adds a tile to the data manager
	void addTileData(const TileData& tile);
	// Adds a vector of tile to the data manager
	void addTilesData(const std::vector<TileData>& tileV);

	// Gets a tile from its ID
	TileData getTileData(const tile_t& id);
	// Gets a tile from its name
	TileData getTileData(const std::string& name);

	// Get the ID of a tile from its name
	tile_t getIdFromName(const std::string& name);


	// Vector of TileDatas
	extern std::vector<TileData> tiles;
	// Map of names and their IDs
	extern std::unordered_map<std::string, tile_t> nameIDs;
};
