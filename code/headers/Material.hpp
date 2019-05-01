/**
 * @file Material.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 29-04-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_MATERIAL_H_
#define OPENGL_SCENE_MATERIAL_H_

#include "Shader.hpp"
#include "ShaderProgram.hpp"

#include "internal/Declarations.hpp"

#include <variant>

namespace prz
{
	class Texture;

	class Material
	{
	public:

		Material()
		{}

	private:

		PBuffer< Texture > textures_;
		Shader shader_;
		ShaderProgram shaderProgram_;
		/*PMap< PString, Variant> noIdea_;*/
	};

} //!namespace prz

#endif // !OPENGL_SCENE_MATERIAL_H_
