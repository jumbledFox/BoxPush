#pragma once

#include <array>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../gl/vertex_array.hpp"
#include "tile_data.hpp"

// Mesh class - faces can be added

// Represents a face
struct MeshFace {
	std::array<GLbyte, 12> vertices;
	GLbyte lightLevel;
};

class Mesh {
public:
	// Adds a face to the mesh
	void addFace(const MeshFace& face, const glm::vec3 position, GLuint texture, TileColor col1, TileColor col2, float light);

	// Updates vertex array
	void updateVertexArray();
	
	std::vector<float> vertices;
	std::vector<GLuint> indices;
	int indicesCount = 0;

	gl::VertexArray vertexArray;
};