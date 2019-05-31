#include <Texture_Cube.hpp>

namespace prz
{
	Texture_Cube::Texture_Cube(PBuffer<PString>& imagePaths, const PString& name, const Color_Format& colorFormat) :
		Texture(GL_TEXTURE_CUBE_MAP, imagePaths, name, CLAMP_TO_EDGE, LINEAR, colorFormat)
	{
		initialize();
	}

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
				colorFormat_,
				image.getSize().x,
				image.getSize().y,
				0,
				colorFormat_,
				GL_UNSIGNED_BYTE,
				image.getPixelsPtr()
			);
		}	
	}

	void Texture_Cube::apply_wrap_mode()
	{
		// Apply the wrap mode to each space coordinate axis. A cube map is a tridimensional texture so three axes
		glTexParameteri(textureType_, GL_TEXTURE_WRAP_S, wrapMode_);
		glTexParameteri(textureType_, GL_TEXTURE_WRAP_T, wrapMode_);
		glTexParameteri(textureType_, GL_TEXTURE_WRAP_R, wrapMode_);
	}

	const GLenum Texture_Cube::textureTarget_[] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,	// Right
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,	// Left
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,	// Bottom
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,	// Top
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,	// Back
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,	// Front
	};
}
