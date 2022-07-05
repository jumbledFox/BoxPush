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

#include "gl/vertex_array.hpp"
#include "gl/shader.hpp"
#include "gl/camera.hpp"
#include "gl/texture.hpp"


int main() {
	Window::loadOpenGL("jumbledFox's pushingBoxes");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	gl::Shader shader("res/shaders/block.vert", "res/shaders/block.frag");
	gl::Texture spriteSheet("res/sprites.png", GL_RGB);
	shader.use();

	std::vector <GLfloat> verts {
		-0.5f, -0.5f, -1.5f,  0, 0,  8,  1,  1, 3,
		 0.5f, -0.5f, -1.5f,  1, 0,  8,  1,  1, 3,
		 0.5f,  0.5f, -1.5f,  1, 1,  8,  1,  1, 3,
		-0.5f,  0.5f, -1.5f,  0, 1,  8,  1,  1, 3
	};

	std::vector<GLuint> ind{
		0, 1, 2,
		2, 3, 0
	};

	gl::VertexArray va;

	va.addVertexBuffer(verts, { { GL_FLOAT, 3, 0 }, { GL_FLOAT, 2, 0 }, { GL_FLOAT, 1, 0 }, { GL_FLOAT, 1, 0 }, { GL_FLOAT, 2, 0 } });
	va.addIndexBuffer(ind);


	Camera cam(35.0f, 1.0f);

	Entity ent(0.1f, { 0, 0, 0 }, { 90, 0, 0 }, { 0, 0, 0 });

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

		cam.update(ent);
		glClearColor(0.2f, 0.2f, 0.2f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		spriteSheet.bind();

		model = glm::mat4(1);

		//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 10.f), { 0, 0, 1 });
		model = glm::translate(model, { 0, -5, 0 });

		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getViewProjection()));
		glUniformMatrix4fv(shader.getUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
		va.draw(GL_TRIANGLES);

		Window::endUpdate();
	}
	glfwTerminate();
	return 0;
}
