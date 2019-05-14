/**
 * @file Fragment_Shader.hpp
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

	class Fragment_Shader : public Shader
	{
	public:

		Fragment_Shader(const Source_Code& sourceCode):
			Shader(sourceCode, GL_VERTEX_SHADER)
		{}

	};

} // !namespace prz

#endif // !OPENGL_SCENE_VERTEX_SHADER_H_
