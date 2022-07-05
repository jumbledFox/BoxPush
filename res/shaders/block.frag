#version 330 core

// Lighting and texture info from vertex shader
in float fLighting;
in vec2 fTexCoords;
flat in unsigned int fTextureID;
flat in unsigned ivec2 fColors;

// Out fragment color
out vec4 FragColor;

// The texture atlas
uniform sampler2D textureAtlas;

vec3 colors[4] = vec3[4](
	vec3(26,  28,  44),
	vec3(93,  39,  93),
	vec3(177, 62,  83),
	vec3(239, 125, 87)
);


void main() {
	// Coordinate of the texture on the atlas
	vec2 atlasCoord = vec2((fTextureID % 8u) + fTexCoords.x, 7 - floor(float(fTextureID) / 8.f) + fTexCoords.y);

	// This is a vector that stores the lighting values for multiplication, since i dont want to multiply alpha
	// It also makes it really easy to add rgb lighting if i want to later

	vec4 lighting = vec4(fLighting, fLighting, fLighting, 1);

	// To turn the coordinate of the texture on the atlas to be the actual texture:
	// You add the texCoord to it
	// Then multiply it by the size of each texture
	// Then divide it by (texture size * amount of textures)

	// Changing the colors
	vec4 BAWtext = texture(textureAtlas, (atlasCoord) * 8 / 64);

	uint color = (BAWtext.x == 0) ? fColors.x : fColors.y;

	vec4 tex = vec4(colors[color] / 255, BAWtext.w);


	// Multiplied by the lighting value
	FragColor = lighting * tex;
	
	// Discard the fragment if it's transparent
	if (FragColor.w == 0) { discard; }
}