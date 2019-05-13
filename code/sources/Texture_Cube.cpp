#include "Texture_Cube.hpp"

namespace prz
{
	const GLenum Texture_Cube::textureTarget_[] = 
	{
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X, // Left
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z, // Back
			GL_TEXTURE_CUBE_MAP_POSITIVE_X, // Right
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, // Forward
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, // Down
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y, // Up
	};

}