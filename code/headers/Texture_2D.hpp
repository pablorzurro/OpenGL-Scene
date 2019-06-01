/**
 * @file Texture_2D.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that represents an image 2D
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_TEXTURE_2D_H_
#define OPENGL_SCENE_TEXTURE_2D_H_

#include <Texture.hpp>

namespace prz
{
	
	/**
	 * @brief Class that represents an image 2D
	 * 
	 */
	class Texture_2D : public Texture
	{
	public:

		/**
		 * @brief Construct a new Texture_2D
		 * 
		 * @param imagePaths 
		 * @param name 
		 * @param colorFormat 
		 * @param flipImages 
		 */
		Texture_2D
		(
			PBuffer<PString>& imagePaths,
			const PString& name,
			const Color_Format& colorFormat = Color_Format::RGBA,
			bool flipImages = true
		);

		/**
		 * @brief Construct a new Texture_2D
		 * 
		 * @param name 
		 * @param width 
		 * @param height 
		 * @param colorFormat 
		 */
		Texture_2D
		(
			const PString& name,
			unsigned int width,
			unsigned int height,
			const Color_Format& colorFormat = Color_Format::RGBA
		);

	protected:

		/**
		 * @brief Method called on initialize  
		 * 
		 */
		virtual void on_initialize() override;
		
	protected:

		/**
		 * @brief Overrided wrap mode application
		 * 
		 */
		void apply_wrap_mode() override
		{
			// Apply the wrap mode to each space coordinate axis. A texture 2D is a bidimensional texture so two axes
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_S, wrapMode_);
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_T, wrapMode_);
		}

	protected:

		unsigned int width_;
		unsigned int height_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_2D_H_
