/**
 * @file Texture_2D.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
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
	
	class Texture_2D : public Texture
	{
	public:

		Texture_2D
		(
			PBuffer<PString>& imagePaths,
			const PString& name,
			const Color_Format& colorFormat = Color_Format::RGBA,
			bool flipImages = true
		);

		Texture_2D
		(
			const PString& name,
			unsigned int width,
			unsigned int height,
			const Color_Format& colorFormat = Color_Format::RGBA
		);

	protected:

		virtual void on_initialize() override;
		
	protected:

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
