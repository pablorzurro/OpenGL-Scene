/**
 * @file Texture.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_TEXTURE_H_
#define OPENGL_SCENE_TEXTURE_H_

#include "Drawable.hpp"

#include "Declarations.hpp"

namespace prz
{
	
	class Texture : Drawable
	{
	public:

		enum Wrap_Mode
		{
			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		};

		enum Filter_Mode
		{
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};

	public:

		Texture(GLenum textureType, PBuffer<PString&> images):
			textureType_(textureType),
			error_(GL_NO_ERROR)
		{
			load_images(images);

			glGenTextures(1, &textureID_);
			glActiveTexture(GL_TEXTURE0);

			bind();
			{
				on_construction();

			} unbind();

			error_ = glGetError();
			assert(is_ok());
		}

		~Texture()
		{
			glDeleteTextures(1, &textureID_);
		}

	public:
		 
		virtual void draw() override = 0;

	public:

		void bind()
		{
			glBindTexture(textureType_, textureID_);
		}

		void unbind()
		{
			glBindTexture(textureType_, 0);
		}

	public:

		bool is_ok() const
		{
			return error_ == GL_NO_ERROR;
		}

	public:

		GLenum get_error() const
		{
			return error_;
		}

	protected:

		virtual void load_images(PBuffer<PString&> imagePaths)
		{
			size_t size = imagePaths.size();

			for (size_t i = 0; i < size; ++i)
			{
				PImage imgData;
				
				if (!imgData.loadFromFile(imagePaths[i]))
				{
					error_ = GL_INVALID_OPERATION;
					cout << "Could not load any image from the following path: " + imagePaths[i] << endl; // DEBUG

					break;
				}

				images_.push_back(imgData);
			}
		}

		virtual void on_construction() = 0;

	protected:

		GLenum textureType_;
		GLenum error_;
		GLuint textureID_;

	protected:

		PBuffer<PImage> images_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_H_
