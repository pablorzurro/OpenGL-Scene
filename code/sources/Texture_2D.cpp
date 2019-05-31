#include "Texture_2D.hpp"

namespace prz
{
	Texture_2D::Texture_2D(PBuffer<PString>& imagePaths, const PString& name, const Color_Format& colorFormat, bool flipImages) :
		Texture(GL_TEXTURE_2D, imagePaths, name, CLAMP_TO_EDGE, LINEAR, colorFormat, flipImages),
		width_(0),
		height_(0)
	{
		initialize();
	}

	Texture_2D::Texture_2D(const PString& name, unsigned int width, unsigned int height, const Color_Format& colorFormat) :
		Texture(GL_TEXTURE_2D, name, CLAMP_TO_EDGE, LINEAR, colorFormat),
		width_(width),
		height_(height)
	{
		initialize();
	}

	void Texture_2D::on_initialize()
	{
		if (images_.size() > 0)
		{
			PImage& image = images_[0];

			glTexImage2D
			(
				textureType_,
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
		else
		{
			glTexImage2D
			(
				textureType_,
				0,
				colorFormat_,
				width_,
				height_,
				0,
				colorFormat_,
				GL_UNSIGNED_BYTE,
				0
			);
		}
	}
}

