#include "level_builder.hpp"

#include "tile_data.hpp"

Mesh LevelBuilder::buildLevel(Level lvl) {
	Mesh mesh;
	LevelTiles tiles = lvl.tiles;

	// For every tile
	int x = 0, z = 0;
	for (const auto& rows : tiles) {
		for (const auto& tileID : rows) {
			// Get tile data
			auto data = TileDataManager::getTileData(tileID);
			auto height = lvl.getHeight({ x, z });
			// If the tile isnt air
			if (data.id != 0) {
				// Add the top face
				mesh.addFace(TOP_FACE, { x-1.5f, height, z }, data.top.id, data.top.backCol, data.top.foreCol, getLightingChange(height));
				
				// This function adds the side faces
				static auto addSides = [&](glm::vec2 lookOffset, MeshFace face) {
					// Position of adjacent tile
					glm::vec2 lookPos = glm::vec2(x, z) + lookOffset;
					// Get the height of the adjacent tile
					int lookRaised = lvl.getHeight(lookPos);
					// If the current tile is higher than the one thats next to us...
					if (lookRaised < height) {
						// For every unit of height inbetween top of this tile and the tile next to us...
						for (int h = height; h > lookRaised; h--) {
							// Add a horizontal face!!!
							mesh.addFace(face, { x-1.5f, h, z }, data.side.id, data.side.backCol, data.side.foreCol, getLightingChange(h-1));
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
	return (-(abs(depth) / 5.f) + 1);
}