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

#include <Declarations.hpp>

namespace prz
{
	
	class Texture
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

		Texture(GLenum textureType, PBuffer<PString>& imagePaths, const PString& name, Wrap_Mode wrapMode = Wrap_Mode::CLAMP_TO_EDGE, Filter_Mode filterMode = Filter_Mode::NEAREST, bool flipImages = true):
			textureID_(8000),
			textureType_(textureType),
			name_(name),
			wrapMode_(wrapMode),
			filterMode_(filterMode),
			error_(GL_NO_ERROR)
		{
			error_ = glGetError();
			load_images(imagePaths);

			if (flipImages)
			{
				flip_images();
			}
		}

		~Texture()
		{
			glDeleteTextures(1, &textureID_);
		}

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

		void flip_images()
		{
			for (PImage& image : images_)
			{
				image.flipVertically();
			}
		}

	public:

		virtual void set_wrap_mode(Wrap_Mode wrapMode)
		{
			wrapMode_ = wrapMode;
			apply_wrap_mode();
		}


		virtual void set_filter_mode(Filter_Mode filterMode)
		{
			filterMode_ = filterMode;
			apply_filter_mode();
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

		const PString& name()
		{
			return name_;
		}

		GLuint textureID() const
		{
			return textureID_;
		}

		GLuint textureType() const
		{
			return textureType_;
		}

	protected:

		virtual void initialize();
		virtual void on_initialize() = 0;

	protected:

		virtual void load_images(PBuffer<PString>& imagePaths);
		
	protected:

		virtual void apply_wrap_mode(){}
		virtual void apply_filter_mode();
		

	protected:

		PBuffer<PImage> images_;

	protected:

		GLenum textureType_;
		GLuint textureID_;

	protected:

		Wrap_Mode wrapMode_;
		Filter_Mode filterMode_;

	protected:

		PString name_;

	protected:

		GLenum error_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_H_
