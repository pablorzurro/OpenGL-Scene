/**
 * @file Skybox.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Class that is similar to a material but with a cube map
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
	class Material;

	/**
	 * @brief Class that is similar to a material but with only a cube map
	 * 
	 */
	class Skybox : public Drawable
	{
	public:

		/**
		 * @brief Construct a new Skybox
		 * 
		 * @param textureRootPath 
		 * @param pathVertexShader 
		 * @param pathFragmentShader 
		 */
		Skybox(const PString& textureRootPath, const PString& pathVertexShader, const PString& pathFragmentShader);

		/**
		 * @brief Construct a new Skybox
		 * 
		 * @param cubeMap 
		 * @param shaderProgram 
		 */
		Skybox(PSPtr< Texture > cubeMap, PSPtr< Shader_Program > shaderProgram);

		/**
		 * @brief Destroy the Skybox
		 * 
		 */
		~Skybox()
		{}

	public:

		/**
		 * @brief Draw the skybox by the camera matrix
		 * 
		 * @param camera 
		 */
		void draw(PSPtr< Camera > camera) override;

		/**
		 * @brief Draw the skybox
		 * 
		 */
		void draw() override {}

	private:

		PSPtr< Material > material_;
		PSPtr< Texture > textureCube_;
		Cube cube_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SKYBOX_H_
