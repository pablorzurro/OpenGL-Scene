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

#include <Cube.hpp>
#include <Drawable.hpp>

#include <Declarations.hpp>

namespace prz
{

	class Camera;
	class Texture;
	class Texture_Cube;
	class Shader_Program;

	class Skybox : public Drawable
	{
	public:

		Skybox(const PString& textureRootPath, const PString& pathVertexShader, const PString& pathFragmentShader);
		Skybox(PSPtr< Texture > cubeMap, PSPtr< Shader_Program > shaderProgram);

		~Skybox()
		{}

	public:

		void draw(PSPtr< Camera > camera) override;
		void draw() override {}

	private:

		PSPtr< Material > material_;
		Cube cube_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SKYBOX_H_
