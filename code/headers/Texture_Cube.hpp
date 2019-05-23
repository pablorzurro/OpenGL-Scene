/**
 * @file Texture_Cube.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_TEXTURE_CUBE_H_
#define OPENGL_SCENE_TEXTURE_CUBE_H_

#include <Texture.hpp>

namespace prz
{
	
	class Texture_Cube : public Texture
	{
	public:
		
		Texture_Cube(PBuffer<PString>& imagePaths, const PString& name):
			Texture(GL_TEXTURE_CUBE_MAP, imagePaths, name)
		{
			/*images_[2].flipHorizontally();
			images_[3].flipHorizontally();*/
			/*images_[2].flipVertically();
			images_[3].flipVertically();*/
			
			initialize();
		}

	protected:

		void on_initialize() override;

	protected:

		void apply_wrap_mode() override
		{
			// Apply the wrap mode to each space coordinate axis. A cube map is a tridimensional texture so three axes
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_S, wrapMode_);
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_T, wrapMode_);
			glTexParameteri(textureType_, GL_TEXTURE_WRAP_R, wrapMode_);
		}

	private:

		static const GLenum textureTarget_[];
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_CUBE_H_
