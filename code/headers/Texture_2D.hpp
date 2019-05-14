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

#include "Texture.hpp"

namespace prz
{
	
	class Texture_2D : public Texture
	{
	public:

		Texture_2D(PBuffer<PString>& imagePaths, const PString& name):
			Texture(GL_TEXTURE_2D, imagePaths, name)
		{
			initialize();
		}

	protected:

		virtual void on_initialize() override
		{
			PImage& image = images_[0];

			glTexImage2D
			(
				textureType_,
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

		void apply_wrap_mode() override
		{
			// Apply the wrap mode to each space coordinate axis. A texture 2D is a bidimensional texture so two axes
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_S, wrapMode_);
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_T, wrapMode_);
		}
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_2D_H_
