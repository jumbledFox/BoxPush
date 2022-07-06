#pragma once

#include <iostream>
#include <stdint.h>
#include <vector>
#include <unordered_map>

// Data for tiles, i.e. if its raised up or not, its colors, name, and ID

using tile_t = uint8_t;

enum class TileColor {
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

struct TileData {
	tile_t id = 0;
	std::string name;
	TileColor foregroundColor; // Color that will replace white
	TileColor backgroundColor; // Color that will replace black
	uint8_t topTextureID = 63;
	uint8_t sideTextureID = 63;

	int raised = 0;

	TileData(std::string name, int r, TileColor fg, TileColor bg, uint8_t ttid, uint8_t stid)  :
	name(name), raised(r), foregroundColor(fg), backgroundColor(bg), topTextureID(ttid), sideTextureID(stid) {}
};


class TileDataManager {
public:
	TileDataManager();

	// Adds a tile to the data manager
	void addTileData(const TileData& tile);
	// Adds a vector of tile to the data manager
	void addTilesData(const std::vector<TileData>& tileV);

	// Gets a tile from its ID
	TileData getTileData(const tile_t& id) const;
	// Gets a tile from its name
	TileData getTileData(const std::string& name) const;

	// Get the ID of a tile from its name
	tile_t getIdFromName(const std::string& name) const;

private:
	// Vector of TileDatas
	std::vector<TileData> tiles;
	// Map of names and their IDs
	std::unordered_map<std::string, tile_t> nameIDs;
};
