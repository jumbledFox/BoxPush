#include "mesh.hpp"

void Mesh::addFace(const MeshFace& face, const glm::vec3 position, GLuint texture, TileColor col1, TileColor col2, float light) {
	int index = 0;

	// Add vertices
	for (unsigned i = 0; i < 4; i++) {
		float x = face.vertices[index++] + position.x;
		float y = face.vertices[index++] + position.y;
		float z = face.vertices[index++] + position.z;

		vertices.push_back(x); // Pos
		vertices.push_back(y);
		vertices.push_back(z);
		vertices.push_back(i); // TexCoords
		vertices.push_back(texture); // Texture ID
		vertices.push_back(face.lightLevel * light); // Light
		vertices.push_back(int(col1));
		vertices.push_back(int(col2));
	}
	// Add indices
	// First triangle
	indices.push_back(indicesCount);
	indices.push_back(indicesCount + 1);
	indices.push_back(indicesCount + 2);
	// Second triangle
	indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 3);
	indices.push_back(indicesCount);

	indicesCount += 4;
}

void Mesh::updateVertexArray() {
	vertexArray.destroy();
	vertexArray.create();

	vertexArray.addIndexBuffer(indices);
	vertexArray.addVertexBuffer(vertices, { { GL_FLOAT, 3, 0 }, { GL_FLOAT, 1, 0 }, { GL_FLOAT, 1, 0 }, { GL_FLOAT, 1, 0 }, { GL_FLOAT, 2, 0 } });
}