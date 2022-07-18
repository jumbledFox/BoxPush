#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// stb_image implementation
#include "gl/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

#include "window.hpp"
#include "input/keyboard.hpp"
#include "game/tile_data.hpp"
#include "game/mesh.hpp"
#include "game/level_builder.hpp"
#include "game/level_loader.hpp"

#include "gl/vertex_array.hpp"
#include "gl/shader.hpp"
#include "gl/camera.hpp"
#include "gl/texture.hpp"


int main() {
	Window::loadOpenGL("jumbledFox's pushingBoxes");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	TileDataManager::initialise();

	gl::Shader shader("res/shaders/block.vert", "res/shaders/block.frag");
	gl::Texture spriteSheet("res/sprites.png", GL_RGB);
	shader.use();


	Level lvl = LevelLoader::loadLevel("0");

	Camera cam(40.0f, 1.0f);

	Entity pl;
	pl.buildMesh(16, TileColor::Black, TileColor::Orange, 20, TileColor::Orange, TileColor::White);

	Entity box;
	box.buildMesh(8, TileColor::Purple, TileColor::Orange);

	Transform cameraPosition({0.5, 13, 0.5}, {90, 0, 0});

	glm::mat4 model{1};

	while (Window::running) {
		Window::update();
		
		if (Keyboard::keyHeld(GLFW_KEY_W))
			pl.transform.position.z -= 0.2f;

		if (Keyboard::keyHeld(GLFW_KEY_S))
			pl.transform.position.z += 0.2f;

		if (Keyboard::keyHeld(GLFW_KEY_A))
			pl.transform.position.x -= 0.2f;

		if (Keyboard::keyHeld(GLFW_KEY_D))
			pl.transform.position.x += 0.2f;

		if (Keyboard::keyHeld(GLFW_KEY_Q))
			pl.transform.rotation.x -= 1;

		if (Keyboard::keyHeld(GLFW_KEY_E))
			pl.transform.rotation.x += 1;

		if (Keyboard::keyHeld(GLFW_KEY_R))
			pl.transform.rotation.y += 1;

		if (Keyboard::keyHeld(GLFW_KEY_F))
			pl.transform.rotation.y -= 1;

		pl.updateMatrix();

		cam.update(cameraPosition + pl.transform);
		glClearColor(26.f / 255.f, 28.f / 255.f, 44.f / 255.f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		spriteSheet.bind();

		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getViewProjection()));

		model = glm::mat4(1);
		model = glm::translate(model, { 1.5, -1, 0 });
		glUniformMatrix4fv(shader.getUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
		lvl.mesh.vertexArray.draw(GL_TRIANGLES);

		model = glm::mat4(1);
		model = glm::translate(model, pl.transform.position);
		glUniformMatrix4fv(shader.getUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
		pl.mesh.vertexArray.draw(GL_TRIANGLES);
		Window::endUpdate();
	}
	glfwTerminate();
	return 0;
}
