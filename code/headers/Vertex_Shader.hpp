/**
 * @file Vertex_Shader.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 11-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_VERTEX_SHADER_H_
#define OPENGL_SCENE_VERTEX_SHADER_H_

#include <Shader.hpp>

namespace prz
{

	class Vertex_Shader : public Shader
	{
	public:

		Vertex_Shader(const Source_Code& sourceCode, const PString& name) :
			Shader(sourceCode, name, VERTEX_SHADER)
		{}

	};

} // !namespace prz

#endif // !OPENGL_SCENE_VERTEX_SHADER_H_
