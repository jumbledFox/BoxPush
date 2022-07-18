#version 330 core

// info from vertex shader
in float fLighting;
in vec2 fTexCoords;
flat in unsigned int fTextureID;
flat in unsigned ivec2 fColors;

// Out fragment color
out vec4 FragColor;

// The texture atlas
uniform sampler2D textureAtlas;

vec3 colors[16] = vec3[16](
	vec3(26,  28,  44) / 255,
	vec3(93,  39,  93) / 255,
	vec3(177, 62,  83) / 255,
	vec3(239, 125, 87) / 255,
	vec3(255, 205, 117) / 255,
	vec3(167, 240, 112) / 255,
	vec3(56 , 183, 100) / 255,
	vec3(37 , 113, 121) / 255,
	vec3(41 , 54 , 111) / 255,
	vec3(59 , 93 , 201) / 255,
	vec3(65 , 166, 246) / 255,
	vec3(115, 239, 247) / 255,
	vec3(244, 244, 244) / 255,
	vec3(148, 176, 194) / 255,
	vec3(86 , 108, 134) / 255,
	vec3(51 , 60 , 87) / 255
);


void main() {
	// Coordinate of the texture on the atlas
	vec2 atlasCoord = vec2((fTextureID % 8u) + fTexCoords.x, 7 - floor(float(fTextureID) / 8.f) + fTexCoords.y);

	// To turn the coordinate of the texture on the atlas to be the actual texture:
	// You add the texCoord to it
	// Then multiply it by the size of each texture
	// Then divide it by (texture size * amount of textures)

	// Changing the colors
	vec4 BAWtext = texture(textureAtlas, (atlasCoord) * 8 / 64);

	uint color = (BAWtext.x == 0) ? fColors.x : fColors.y;

	vec4 tex = vec4(colors[color], BAWtext.w);


	// Multiplied by the lighting value
	// TODO - fix this mess of a shader... 
	FragColor = mix(vec4(colors[0], 1), tex, clamp(fLighting, 0, 1));
	
	// Discard the fragment if it's transparent
	if (FragColor.w == 0) { discard; }
}