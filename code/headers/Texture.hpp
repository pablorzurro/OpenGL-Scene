/**
 * @file Texture.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that manage OpenGL textures and images loaded from files
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
	
	/**
	 * @brief Class that manage OpenGL textures and images loaded from files
	 * 
	 */
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

		enum Color_Format
		{
			RGB = GL_RGB,
			RGBA = GL_RGBA
		};

	public:

		/**
		 * @brief Construct a new Texture
		 * 
		 * @param textureType 
		 * @param name 
		 * @param wrapMode 
		 * @param filterMode 
		 * @param colorFormat 
		 */
		Texture
		(
			GLenum textureType,
			const PString& name, 
			Wrap_Mode wrapMode = Wrap_Mode::CLAMP_TO_EDGE, 
			Filter_Mode filterMode = Filter_Mode::LINEAR, 
			const Color_Format& colorFormat = Color_Format::RGBA
		);

		/**
		 * @brief Construct a new Texture
		 * 
		 * @param textureType 
		 * @param imagePaths 
		 * @param name 
		 * @param wrapMode 
		 * @param filterMode 
		 * @param colorFormat 
		 * @param flipImages 
		 */
		Texture
		(
			GLenum textureType,
			PBuffer<PString>& imagePaths,
			const PString& name,
			Wrap_Mode wrapMode = Wrap_Mode::CLAMP_TO_EDGE,
			Filter_Mode filterMode = Filter_Mode::LINEAR,
			const Color_Format& colorFormat = Color_Format::RGBA,
			bool flipImages = true
		);

		/**
		 * @brief Destroy the Texture
		 * 
		 */
		~Texture()
		{
			glDeleteTextures(1, &textureID_);
		}

	public:

		/**
		 * @brief Bind the texture
		 * 
		 */
		void bind()
		{
			glBindTexture(textureType_, textureID_);
		}

		/**
		 * @brief Unbind the texture
		 * 
		 */
		void unbind()
		{
			glBindTexture(textureType_, 0);
		}

	public:

		/**
		 * @brief Flip images
		 * 
		 */
		void flip_images()
		{
			for (PImage& image : images_)
			{
				image.flipVertically();
			}
		}

	public:

		/**
		 * @brief Set the wrap mode
		 * 
		 * @param wrapMode 
		 */
		virtual void set_wrap_mode(Wrap_Mode wrapMode)
		{
			wrapMode_ = wrapMode;
			apply_wrap_mode();
		}

		/**
		 * @brief Set the filter mode
		 * 
		 * @param filterMode 
		 */
		virtual void set_filter_mode(Filter_Mode filterMode)
		{
			filterMode_ = filterMode;
			apply_filter_mode();
		}

	public:

		/**
		 * @brief Return if is good
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_ok() const
		{
			return error_ == GL_NO_ERROR;
		}

	public:

		/**
		 * @brief Return the error
		 * 
		 * @return GLenum 
		 */
		GLenum get_error() const
		{
			return error_;
		}

		/**
		 * @brief Return the name
		 * 
		 * @return const PString& 
		 */
		const PString& name()
		{
			return name_;
		}

		/**
		 * @brief Return the texture identification
		 * 
		 * @return GLuint 
		 */
		GLuint textureID() const
		{
			return textureID_;
		}

		/**
		 * @brief Return the texture type
		 * 
		 * @return GLuint 
		 */
		GLuint textureType() const
		{
			return textureType_;
		}

	protected:

		/**
		 * @brief Initialize
		 * 
		 */
		virtual void initialize();

		/**
		 * @brief Method called on initialize
		 * 
		 */
		virtual void on_initialize() = 0;

	protected:

		/**
		 * @brief Load images from files
		 * 
		 * @param imagePaths 
		 */
		virtual void load_images(PBuffer<PString>& imagePaths);
		
	protected:

		/**
		 * @brief Apply the texture wrap mode
		 * 
		 */
		virtual void apply_wrap_mode(){}

		/**
		 * @brief Apply the filter mode
		 * 
		 */
		virtual void apply_filter_mode();
		

	protected:

		PBuffer<PImage> images_;

	protected:

		GLenum textureType_;
		GLuint textureID_;

	protected:

		Wrap_Mode wrapMode_;
		Filter_Mode filterMode_;
		Color_Format colorFormat_;

	protected:

		PString name_;

	protected:

		GLenum error_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_H_
