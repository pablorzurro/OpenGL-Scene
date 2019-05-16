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

#include <Shader_Program.hpp>

#include <Declarations.hpp>

namespace prz
{
	
	class Texture;

	class Material
	{
	public:

		Material(const PString& name, PSPtr< Shader_Program >& shaderProgram):
			name_(name),
			shaderProgram_(shaderProgram),
			instanceID_(instanceCount_++)
		{}

	public:

		static PSPtr< Material > default_material();

	public:

		void use();

	public:

		Uniform* allocate_uniform(const char* id, const PString& name, Var_GL::Type type);

	public:

		bool set(const char* id, const PString& name, const GLint    value);
		bool set(const char* id, const PString& name, const GLuint   value);
		bool set(const char* id, const PString& name, const GLfloat  value);
		bool set(const char* id, const PString& name, const PVec2&	value);
		bool set(const char* id, const PString& name, const PVec3&	value);
		bool set(const char* id, const PString& name, const PVec4&	value);

	public:

		unsigned instanceID() const
		{
			return instanceID_;
		}

		const PString& name() const
		{
			return name_;
		}

		Shader_Program* get_shader_program() const
		{
			return shaderProgram_.get();
		}

	private:

		PBuffer< PSPtr< Texture> > textures_;
		PSPtr< Shader_Program > shaderProgram_;
		PMap< PString, Uniform> uniforms_;

	private:

		PString name_;
		unsigned int instanceID_;

	private:

		static unsigned instanceCount_;
	};

} //!namespace prz

#endif // !OPENGL_SCENE_MATERIAL_H_
