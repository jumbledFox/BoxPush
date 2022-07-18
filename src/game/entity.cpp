#include "entity.hpp"

#include "../math.hpp"
#include "level_builder.hpp"

Entity::Entity(glm::vec3 pos, glm::vec3 rot) {
	updateMatrix();
}

void Entity::updateMatrix() {
	modelMatrix = makeMatrixFromTransform(transform.position, transform.rotation);
}

void Entity::buildMesh(unsigned tex, TileColor col1, TileColor col2) {
	buildMesh(tex, col1, col2, tex, col1, col2);
}
void Entity::buildMesh(unsigned topTex, TileColor topCol1, TileColor topCol2, unsigned sideTex, TileColor sideCol1, TileColor sideCol2) {
	mesh = Mesh(); // reset mesh
	mesh.addFace(LevelBuilder::TOP_FACE,  { 0, 0, 0 }, topTex, topCol1, topCol2, 1);

	mesh.addFace(LevelBuilder::FRONT_FACE, { 0, 0, 0 }, sideTex, sideCol1, sideCol2, 1);
	mesh.addFace(LevelBuilder::BACK_FACE,  { 0, 0, 0 }, sideTex, sideCol1, sideCol2, 1);
	mesh.addFace(LevelBuilder::LEFT_FACE,  { 0, 0, 0 }, sideTex, sideCol1, sideCol2, 1);
	mesh.addFace(LevelBuilder::RIGHT_FACE, { 0, 0, 0 }, sideTex, sideCol1, sideCol2, 1);

	mesh.updateVertexArray();
}