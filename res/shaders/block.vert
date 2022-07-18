#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in float textureCoords;
layout (location = 2) in float textureID;
layout (location = 3) in float light;
layout (location = 4) in vec2 colors;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

out float fLighting;
out vec2 fTexCoords;
flat out unsigned int fTextureID;
flat out unsigned ivec2 fColors;

vec2 texCoords[4] = vec2[4](
	vec2(1, 1),
	vec2(0, 1),
	vec2(0, 0),
	vec2(1, 0)
);

void main() {
	fLighting = light / 5;
	fTexCoords = texCoords[int(textureCoords)];
	fTextureID = uint(textureID);
	fColors = unsigned ivec2(colors);

    gl_Position = projectionViewMatrix * modelMatrix * vec4(position, 1);
}

// Maybe
// Position as vec3
// Unsigned int to store texCoords, texID, lighting, and colors
// bits:				 2          6      3             5   5
// 21 bits total