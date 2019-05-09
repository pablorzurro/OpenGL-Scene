/**
 * @file Skybox.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_SKYBOX_H_
#define OPENGL_SCENE_SKYBOX_H_

#include "Texture_Cube.hpp"

namespace prz
{

	class Skybox : public Texture_Cube
	{
	public:

		Skybox(const PString& texture_path)
		{}

		~Skybox()
		{}

	protected:

	private:

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SKYBOX_H_
