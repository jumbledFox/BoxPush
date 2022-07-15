#include "level_builder.hpp"

#include "tile_data.hpp"

namespace {
	const MeshFace TOP_FACE = { {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}, 5 };
	const MeshFace FRONT_FACE = { {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, 3 };
	const MeshFace BACK_FACE = { {0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, 3 };
	const MeshFace LEFT_FACE = { {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 2 };
	const MeshFace RIGHT_FACE = { {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, 2 };
}

Mesh LevelBuilder::buildLevel(Level lvl) {
	Mesh mesh;
	LevelTiles tiles = lvl.tiles;

	// For every tile
	int x = 0, z = 0;
	for (const auto& rows : tiles) {
		for (const auto& tileID : rows) {
			// Get tile data
			auto data = TileDataManager::getTileData(tileID);
			// If the tile isnt air
			if (data.id != 0) {
				// Add the top face
				mesh.addFace(TOP_FACE, { x, data.raised, z }, data.top.id, data.top.backCol, data.top.foreCol, getLightingChange(data.raised));
				
				// This function adds the side faces
				static auto addSides = [&](glm::vec2 lookOffset, MeshFace face) {
					// Position of adjacent tile
					glm::vec2 lookPos = glm::vec2(x, z) + lookOffset;
					// Get the height of the adjacent tile
					int lookRaised = TileDataManager::getTileData(lvl.getTile(lookPos)).raised;
					// If the current tile is higher than the one thats next to us...
					if (lookRaised < data.raised) {
						// For every unit of height inbetween top of this tile and the tile next to us...
						for (int h = data.raised; h > lookRaised; h--) {
							// Add a horizontal face!!!
							mesh.addFace(face, { x, h, z }, data.side.id, data.side.backCol, data.side.foreCol, getLightingChange(h-1));
						}
					}
				};

				// Add the side faces
				addSides({ -1,  0 }, LEFT_FACE);
				addSides({  1,  0 }, RIGHT_FACE);
				addSides({  0,  1 }, FRONT_FACE);
				addSides({  0, -1 }, BACK_FACE);
			}
			x++;
		}
		x = 0; z++;
	}

	// Update the vertex array
	mesh.updateVertexArray();

	return mesh;
}

float LevelBuilder::getLightingChange(float depth) {
	// Calculates how lighting should change based on the depth of a tile
	return (-(abs(depth) / 6.f) + 1);
}