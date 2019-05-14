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

	public:

		operator GLuint () const
		{
			return (shaderObjID_);
		}

	protected:

		Shader(const Source_Code& sourceCode, GLenum shaderType);

		~Shader();

	protected:

		void on_delete()
		{

		}

	private:

		Shader(const Shader& other);

	private:

		GLuint shaderObjID_;
		PString logStr_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SHADER_H_
