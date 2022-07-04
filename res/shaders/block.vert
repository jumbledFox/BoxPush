#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in float textureID;
layout (location = 3) in float lighting;

uniform mat4 projectionViewMatrix;

out float fLighting;
out vec2 fTexCoords;
flat out unsigned int fTextureID;

void main() {
	fLighting = lighting;
	fTexCoords = textureCoords;
	fTextureID = uint(textureID);

    gl_Position = projectionViewMatrix * vec4(position, 1);
}

// Maybe
// Position as vec3
// Unsigned int to store texCoords, texID, lighting, and colors
// bits:				 2          6      3             5   5
// 21 bits total