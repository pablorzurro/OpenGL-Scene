/**
 * @file Texture_Cube.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that represents 6 textures 2D which forms a cube
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
	
	/**
	 * @brief Class that represents 6 textures 2D which forms a cube
	 * 
	 */
	class Texture_Cube : public Texture
	{
	public:
		
		/**
		 * @brief Construct a new Texture_Cube
		 * 
		 * @param imagePaths 
		 * @param name 
		 * @param colorFormat 
		 */
		Texture_Cube
		(
			PBuffer<PString>& imagePaths,
			const PString& name,
			const Color_Format& colorFormat = Color_Format::RGBA
		);

	protected:

		/**
		 * @brief Overrided method called on texture initialize
		 * 
		 */
		void on_initialize() override;

	protected:

		/**
		 * @brief Overrided wrap mode application
		 * 
		 */
		void apply_wrap_mode() override;
	
	private:

		static const GLenum textureTarget_[];
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_CUBE_H_
