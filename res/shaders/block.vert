#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in float textureID;
layout (location = 3) in float lighting;
layout (location = 4) in vec2 colors;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

out float fLighting;
out vec2 fTexCoords;
flat out unsigned int fTextureID;
flat out unsigned ivec2 fColors;

void main() {
	fLighting = lighting;
	fTexCoords = textureCoords;
	fTextureID = uint(textureID);
	fColors = unsigned ivec2(colors);

    gl_Position = projectionViewMatrix * modelMatrix * vec4(position, 1);
}

// Maybe
// Position as vec3
// Unsigned int to store texCoords, texID, lighting, and colors
// bits:				 2          6      3             5   5
// 21 bits total