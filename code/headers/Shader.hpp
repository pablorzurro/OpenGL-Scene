/**
 * @file Shader.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that store a source code and compiles it to OpenGL
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
	
	/**
	 * @brief Class that store a source code and compiles it to OpenGL
	 * 
	 */
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

		/**
		 * @brief Return if is compiled succesfully
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_compiled() const
		{
			return (shaderObjID_ != 0);
		}

		/**
		 * @brief Return if the compilation has failed
		 * 
		 * @return true 
		 * @return false 
		 */
		bool has_compilation_failed() const
		{
			return (shaderObjID_ == 0);
		}

		/**
		 * @brief Return the error log
		 * 
		 * @return const PString& 
		 */
		const PString& log() const
		{
			return (logStr_);
		}

		/**
		 * @brief Return the origin path
		 * 
		 * @return const PString& 
		 */
		const PString& path() const { return path_; };

		/**
		 * @brief Return the type
		 * 
		 * @return Type 
		 */
		Type type() const { return type_; };

		/**
		 * @brief Return the name
		 * 
		 * @return const PString& 
		 */
		const PString& name() const { return name_; }

	public:

		/**
		 * @brief Operator to return the identification object 
		 * 
		 * @return GLuint 
		 */
		operator GLuint () const
		{
			return (shaderObjID_);
		}

	protected:

		/**
		 * @brief Construct a new Shader. Private mode
		 * 
		 * @param sourceCode 
		 * @param name 
		 * @param shaderType 
		 */
		Shader(const Source_Code& sourceCode, const PString& name, Type shaderType);

		/**
		 * @brief Destroy the Shader
		 * 
		 */
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
