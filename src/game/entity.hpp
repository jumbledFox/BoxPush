#pragma once

#include <glm/glm.hpp>

#include "mesh.hpp"

struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;

	Transform() : position({ 0, 0, 0 }), rotation({ 0, 0, 0 }) {}
	Transform(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot) {}

	Transform operator +(const Transform& obj) {
		Transform result;
		result.position = position + obj.position;
		result.rotation = rotation + obj.rotation;
		return result;
	}
};

class Entity {
public:
	Entity(glm::vec3 pos = { 0, 0, 0 }, glm::vec3 rot = { 0, 0, 0 });

	Transform transform;
	Mesh mesh;

	gl::VertexArray va;
	glm::mat4 modelMatrix;
	void updateMatrix();

	void buildMesh(unsigned tex, TileColor col1, TileColor col2);
	void buildMesh(unsigned topTex, TileColor topCol1, TileColor topCol2, unsigned sideTex, TileColor sideCol1, TileColor sideCol2);
};