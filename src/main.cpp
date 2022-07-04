#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stb_image implementation
#include "gl/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

#include "window.hpp"

#include "gl/vertex_array.hpp"
#include "gl/shader.hpp"
#include "gl/camera.hpp"
#include "gl/texture.hpp"


int main() {
	Window::loadOpenGL("jumbledFox's pushingBoxes");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::vector <GLfloat> verts {
		-0.5f, -0.5f, 0.0f,  0, 0,  8,  1,
		 0.5f, -0.5f, 0.0f,  1, 0,  8,  1,
		 0.5f,  0.5f, 0.0f,  1, 1,  8,  1,
		-0.5f,  0.5f, 0.0f,  0, 1,  8,  1
	};

	std::vector<GLuint> ind{
		0, 1, 2,
		2, 3, 0
	};

	gl::VertexArray va;

	va.addVertexBuffer(verts, { { GL_FLOAT, 3, 0 }, { GL_FLOAT, 2, 0 }, { GL_FLOAT, 1, 0 }, { GL_FLOAT, 1, 0 } });
	va.addIndexBuffer(ind);

	gl::Shader shader("res/shaders/block.vert", "res/shaders/block.frag");
	shader.use();

	Camera cam(35.0f, 1.0f);


	gl::Texture spriteSheet("res/sprites.png", GL_RGB);

	while (Window::running) {
		Window::update();
		
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		spriteSheet.bind();
		glUniformMatrix4fv(shader.getUniform("projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getViewProjection()));
		va.draw(GL_TRIANGLES);

		Window::endUpdate();
	}
	glfwTerminate();
	return 0;
}
