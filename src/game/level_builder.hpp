#pragma once

#include "level.hpp"
#include "mesh.hpp"

namespace LevelBuilder {
	const MeshFace TOP_FACE = { {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}, 5 };
	const MeshFace FRONT_FACE = { {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, 3 };
	const MeshFace BACK_FACE = { {0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, 3 };
	const MeshFace LEFT_FACE = { {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 2 };
	const MeshFace RIGHT_FACE = { {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, 2 };

	Mesh buildLevel(Level lvl);
	float getLightingChange(float depth);
}