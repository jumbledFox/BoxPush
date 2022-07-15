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

	
	Level lvl;
	lvl.buildMesh();


	Camera cam(35.0f, 1.0f);

	Entity ent(0.1f, { 0, 5, 0 }, { 90, 0, 0 }, { 0, 0, 0 });

	glm::mat4 model{1};

	while (Window::running) {
		Window::update();
		


		if (Keyboard::keyHeld(GLFW_KEY_W))
			ent.position.z -= 0.2f;

		if (Keyboard::keyHeld(GLFW_KEY_S))
			ent.position.z += 0.2f;

		if (Keyboard::keyHeld(GLFW_KEY_Q))
			ent.rotation.x -= 1;

		if (Keyboard::keyHeld(GLFW_KEY_E))
			ent.rotation.x += 1;

		if (Keyboard::keyHeld(GLFW_KEY_R))
			ent.rotation.y -= 1;

		if (Keyboard::keyHeld(GLFW_KEY_F))
			ent.rotation.y += 1;

		cam.update(ent);
		glClearColor(26.f / 255.f, 28.f / 255.f, 44.f / 255.f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		spriteSheet.bind();

		model = glm::mat4(1);

		//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 10.f), { 0, 0, 1 });
		model = glm::translate(model, { 0, -5, 0 });

		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getViewProjection()));
		glUniformMatrix4fv(shader.getUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));

		lvl.mesh.vertexArray.draw(GL_TRIANGLES);

		Window::endUpdate();
	}
	glfwTerminate();
	return 0;
}
