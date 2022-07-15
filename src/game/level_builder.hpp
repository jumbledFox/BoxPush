#pragma once

#include "level.hpp"
#include "mesh.hpp"

namespace LevelBuilder {
	Mesh buildLevel(Level lvl);
	float getLightingChange(float depth);
}