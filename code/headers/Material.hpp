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
#include "Shader_Program.hpp"

#include "Declarations.hpp"

#include <variant>

namespace prz
{
	
	class Texture;

	class Material
	{
	public:

		Material(const PString& name, PSPtr< Shader_Program >& shaderProgram)
		{}
		
		~Material()
		{}

	private:

		static unsigned instance_count;

		static PSPtr< Material > default_material();

	private:

		PBuffer< Texture > textures_;
		PSPtr< Shader_Program > shaderProgram_;
		PMap< PString, Uniform> uniforms;

	private:

		unsigned int instanceID_;

	};

} //!namespace prz

#endif // !OPENGL_SCENE_MATERIAL_H_
