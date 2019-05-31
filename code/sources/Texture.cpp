#include <Texture.hpp>

namespace prz
{
	Texture::Texture(GLenum textureType, const PString& name, Wrap_Mode wrapMode, Filter_Mode filterMode, const Color_Format& colorFormat) :
		textureID_(8000),
		textureType_(textureType),
		name_(name),
		wrapMode_(wrapMode),
		filterMode_(filterMode),
		colorFormat_(colorFormat),
		error_(GL_NO_ERROR)
	{}

	Texture::Texture(GLenum textureType, PBuffer<PString>& imagePaths, const PString& name, Wrap_Mode wrapMode, Filter_Mode filterMode, const Color_Format& colorFormat, bool flipImages) :
		Texture(textureType, name, wrapMode, filterMode, colorFormat)
	{
		error_ = glGetError();
		load_images(imagePaths);

		if (flipImages)
		{
			flip_images();
		}
	}

	void Texture::initialize()
	{
		if (is_ok()) // Check if the images have been loaded succesfully 
		{
			glGenTextures(1, &textureID_);
			glActiveTexture(GL_TEXTURE0);

			bind();
			{
				apply_wrap_mode();
				apply_filter_mode();
				on_initialize(); // Never call a pure virtual function in constructor, it calls the base method instead of the children's

			} unbind();

			error_ = glGetError();

			assert(is_ok()); //Check if has been an error loading the texture in OpenGL
		}
	}

	void Texture::load_images(PBuffer<PString>& imagePaths)
	{
		size_t size = imagePaths.size();

		for (size_t i = 0; i < size; ++i)
		{
			PImage imgData;

			if (!imgData.loadFromFile(imagePaths[i]))
			{
				error_ = GL_INVALID_OPERATION;
			}
			else
			{
				cout << "Loaded image from path: \"" + imagePaths[i] + "\"" << endl; // DEBUG
				images_.push_back(imgData);
			}
		}
	}

	void Texture::apply_filter_mode()
	{
		glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, filterMode_);

		bool generateMipmap = false;

		switch (filterMode_)
		{
		case LINEAR_MIPMAP_NEAREST:
		case LINEAR_MIPMAP_LINEAR:

			generateMipmap = true;

		case LINEAR:

			glTexParameteri(textureType_, GL_TEXTURE_MAG_FILTER, LINEAR);

			break;

		case NEAREST_MIPMAP_NEAREST:
		case NEAREST_MIPMAP_LINEAR:

			generateMipmap = true;

		case NEAREST:

			glTexParameteri(textureType_, GL_TEXTURE_MAG_FILTER, Filter_Mode::NEAREST);

			break;
		}

		if (generateMipmap)
		{
			glGenerateMipmap(textureType_);
		}
	}
}
