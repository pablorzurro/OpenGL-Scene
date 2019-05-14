#include <Texture_Cube.hpp>

namespace prz
{
	void Texture_Cube::on_initialize()
	{
		// Send the image bitmaps to the GPU:
		for (size_t i = 0; i < images_.size(); i++)
		{
			PImage& image = images_[i];

			glTexImage2D
			(
				textureTarget_[i],
				0,
				GL_RGBA,
				image.getSize().x,
				image.getSize().y,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				image.getPixelsPtr()
			);
		}	
	}

	const GLenum Texture_Cube::textureTarget_[] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,	// Right
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,	// Left
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,	// Top
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,	// Bottom
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,	// Back
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,	// Front
	};
}
