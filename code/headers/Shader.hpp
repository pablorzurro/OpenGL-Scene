/**
 * @file Shader.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_SHADER_H_
#define OPENGL_SCENE_SHADER_H_

#include <Declarations.hpp>

namespace prz
{
	class Source_Code;

	class Shader
	{
	public:

		enum Type
		{
			//COMPUTE_SHADER = GL_COMPUTE_SHADER, // 4.3 or higher
			VERTEX_SHADER = GL_VERTEX_SHADER, 
			//TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER, // unknown version
			//TESS_EVALUATION = GL_TESS_EVALUATION_SHADER, // unknown version
			GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
			SIZE
		};

	public:

		bool is_compiled() const
		{
			return (shaderObjID_ != 0);
		}

		bool has_compilation_failed() const
		{
			return (shaderObjID_ == 0);
		}

		const PString& log() const
		{
			return (logStr_);
		}

		const PString& path() const { return path_; };
		Type type() const { return type_; };
		const PString& name() const { return name_; }

	public:

		operator GLuint () const
		{
			return (shaderObjID_);
		}

	protected:

		Shader(const Source_Code& sourceCode, const PString& name, Type shaderType);
		~Shader();

	protected:

		GLuint shaderObjID_;
		Type type_;

	protected:

		PString logStr_;
		
	protected:

		PString path_;
		PString name_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SHADER_H_
