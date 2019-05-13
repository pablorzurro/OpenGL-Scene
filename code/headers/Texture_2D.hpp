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

		Texture_2D(PBuffer<PString>& image)
		{
			PBuffer<PImage&> imageToBuffer{ image };

			Texture(GL_TEXTURE_2D, imageToBuffer);
		}

	public:

		virtual void on_construction(){}

		virtual void draw() override
		{}
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_2D_H_
