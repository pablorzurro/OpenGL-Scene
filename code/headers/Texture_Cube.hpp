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
		
		Texture_Cube
		(
			PBuffer<PString>& imagePaths,
			const PString& name,
			const Color_Format& colorFormat = Color_Format::RGBA
		);

	protected:

		void on_initialize() override;

	protected:

		void apply_wrap_mode() override;
	
	private:

		static const GLenum textureTarget_[];
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_CUBE_H_
