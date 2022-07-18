#pragma once

#include "level.hpp"

// This will load levels from a lvl file, and return a Level class
namespace LevelLoader {
	// Defines all of the aliases
	void defineAliases();
	// Loads, builds, and returns a level
	Level loadLevel(const std::string& levelName);
}