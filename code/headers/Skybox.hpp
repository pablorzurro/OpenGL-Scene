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

#include <Declarations.hpp>

namespace prz
{

	class Camera;
	class Texture;
	class Texture_Cube;

	class Skybox
	{
	public:

		Skybox(const PString& textureRootPath, const PString& textureName);

		Skybox(PSPtr< Texture > cubeMap);

		Skybox(Texture_Cube* cubeMap)
		{
			assert(cubeMap);
			cubeMap_ = cubeMap;
		}

		~Skybox()
		{}
	
	public:

	protected:

	private:

		Texture_Cube* cubeMap_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SKYBOX_H_
