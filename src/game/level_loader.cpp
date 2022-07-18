#include "level_loader.hpp"

#include <iostream>
#include <fstream>
#include <string>

namespace {
	// Aliases
	static std::unordered_map<char, std::pair<tile_t, int8_t>> tileChars;
}
namespace LevelLoader {
	void defineAliases() {
		tileChars[' '] = { 0, -5 }; // void
		tileChars['.'] = { 1,  0 }; // grass
		tileChars['o'] = { 1, -1 }; // hole
		tileChars['#'] = { 2,  1 }; // wall
	}

	Level loadLevel(const std::string& levelName) {
		// Open the file
		std::ifstream levelFile("res/levels/" + levelName + ".lvl");

		// Vector
		LevelTiles tiles {{}};
		LevelHeightMap heightMap {{}};

		// Read through the file line by line
		std::string line;
		while (std::getline(levelFile, line)) {
			// If the line starts with //, it's a comment!
			if (line.rfind("//", 0) == 0)
				continue;

			// For each character
			for (const auto& c : line) {
				tile_t tile = 1;
				int8_t height = 0;

				if (tileChars.find(c) != tileChars.end()) {
					tile = tileChars[c].first;
					height = tileChars[c].second;
				}
				else {
					//tile = 1;
					//height = 0;
				}

				// Add the tile and height to their vectors
				tiles    [tiles.size() - 1]    .push_back(tile);
				heightMap[heightMap.size() - 1].push_back(height);
			}
			tiles    .push_back(std::vector<tile_t>());
			heightMap.push_back(std::vector<int8_t>());
		}

		// Close the file
		levelFile.close();

		const auto& lvl = Level(tiles, heightMap);
		return lvl;
	}
}