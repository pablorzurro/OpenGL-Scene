/**
 * @file ShaderProgram.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_SHADER_PROGRAM_H_
#define OPENGL_SCENE_SHADER_PROGRAM_H_

#include <Shader.hpp>

#include <Declarations.hpp>

namespace prz
{

	class Shader_Program
	{
	public:

		Shader_Program() :
			instanceID_(instanceCount_++),
			programObjID_(glCreateProgram()),
			islinkSuccessful_(false),
			name_("empty")
		{
			assert(programObjID_ != 0);
		}

		~Shader_Program()
		{
			glDeleteProgram(programObjID_);

			programObjID_ = 0;
		}

	public:

		bool link();

		void use() const
		{
			assert(is_usable());

			if (this != activeShaderProgram_)
			{
				glUseProgram(programObjID_);

				activeShaderProgram_ = this;
			}
		}

		static void disable()
		{
			glUseProgram(0);
		}

	public:

		bool attach(PSPtr< Shader > shader)
		{
			if (!is_shader_attached(shader) && shader->is_compiled())
			{
				glAttachShader(programObjID_, *shader);
				attachedShaders_[shader->name()] = shader;

				reset_name();
				return true;
			}

			return false;
		}

		bool detach(PSPtr< Shader > shader)
		{
			return shader ? detach(shader->name()) : false;
		}

		bool detach(const PString& shaderName)
		{
			if (is_shader_attached(shaderName))
			{
				glDetachShader(programObjID_, *attachedShaders_[shaderName]);
				attachedShaders_.erase(shaderName);

				reset_name();
				return true;
			}

			return false;
		}

	public:

		void set_uniform_value(GLint uniformID, const GLint & value) const { glUniform1i(uniformID, value); }
		void set_uniform_value(GLint uniformID, const GLuint & value) const { glUniform1ui(uniformID, value); }
		void set_uniform_value(GLint uniformID, const float& value) const { glUniform1f(uniformID, value); }
		void set_uniform_value(GLint uniformID, const float(&vector)[2]) const { glUniform2f(uniformID, vector[0], vector[1]); }
		void set_uniform_value(GLint uniformID, const float(&vector)[3]) const { glUniform3f(uniformID, vector[0], vector[1], vector[2]); }
		void set_uniform_value(GLint uniformID, const float(&vector)[4]) const { glUniform4f(uniformID, vector[0], vector[1], vector[2], vector[3]); }
		void set_uniform_value(GLint uniformID, const PVec2 & vector) const { glUniform2f(uniformID, vector[0], vector[1]); }
		void set_uniform_value(GLint uniformID, const PVec3 & vector) const { glUniform3f(uniformID, vector[0], vector[1], vector[2]); }
		void set_uniform_value(GLint uniformID, const PVec4 & vector) const { glUniform4f(uniformID, vector[0], vector[1], vector[2], vector[3]); }
		void set_uniform_value(GLint uniformID, const PMat2 & matrix) const { glUniformMatrix2fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix)); }
		void set_uniform_value(GLint uniformID, const PMat3 & matrix) const { glUniformMatrix3fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix)); }
		void set_uniform_value(GLint uniformID, const PMat4 & matrix) const { glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix)); }

	public:

		void set_vertex_attribute(GLint attributeID, const float& value) { glVertexAttrib1f(attributeID, value); }
		void set_vertex_attribute(GLint attributeID, const PVec2 & vector) { glVertexAttrib2fv(attributeID, glm::value_ptr(vector)); }
		void set_vertex_attribute(GLint attributeID, const PVec3 & vector) { glVertexAttrib3fv(attributeID, glm::value_ptr(vector)); }
		void set_vertex_attribute(GLint attributeID, const PVec4 & vector) { glVertexAttrib4fv(attributeID, glm::value_ptr(vector)); }

	public:

		bool is_usable() const
		{
			return islinkSuccessful_;
		}

		bool is_shader_attached(PSPtr< Shader > shader)
		{
			return shader ? is_shader_attached(shader->name()) : false;
		}

		bool is_shader_attached(const PString& name)
		{
			return attachedShaders_.find(name) != attachedShaders_.end();
		}

	public:

		GLint get_vertex_attribute_id(const char* id) const
		{
			assert(is_usable());

			GLint attributeID = glGetAttribLocation(programObjID_, id);

			assert(attributeID != -1);

			return (attributeID);
		}

		GLint get_uniform_id(const char* id) const
		{
			assert(is_usable());

			GLint uniformID = glGetUniformLocation(programObjID_, id);

			/*assert(uniformID != -1);*/

			return (uniformID);
		}

		PSPtr< Shader > get_attached_shader(const PString& shaderName)
		{
			return is_shader_attached(shaderName) ? attachedShaders_[shaderName] : PSPtr< Shader >();
		}

	public: 

		unsigned int get_number_of_attached_shaders()
		{
			return (unsigned int)attachedShaders_.size();
		}

	public:

		static const Shader_Program* activeShaderProgram() { return activeShaderProgram_; }
		unsigned instanceID() const { return instanceID_; }
		const PString& log() const { return (logStr_); }
		const PString& name() const { return name_; }

	public:

		static PString form_shader_program_name(PBuffer< PString >& shaderNames)
		{
			PString name = "Shader_program_with_shaders:";

			for (size_t i = 0; i < shaderNames.size(); i++)
			{
				name += " -" + shaderNames[i];
			}

			return name;
		}

		static PString form_shader_program_name(PBuffer< PSPtr< Shader> >& shaders)
		{
			PBuffer< PString > shaderNames(shaders.size());

			for (size_t i = 0; i < shaderNames.size(); ++i)
			{
				PSPtr< Shader > shader = shaders[i];

				if (!shader)
				{
					return "A shader is empty";
				}

				shaderNames[i] = shader->name();
			}

			return form_shader_program_name(shaderNames);
		}

	private:

		void reset_name()
		{
			PBuffer< PString > shaderNames(attachedShaders_.size());

			unsigned int i = 0;
			for (auto& pair : attachedShaders_)
			{
				shaderNames[i++] = pair.first;
			}

			name_ = form_shader_program_name(shaderNames);
		}

	private:

		unsigned    instanceID_;
		GLuint      programObjID_;
		bool        islinkSuccessful_;

	private:

		PMap< PString, PSPtr < Shader > > attachedShaders_;

	private:

		PString logStr_;
		PString name_;

	private:

		static const Shader_Program* activeShaderProgram_;
		static unsigned int instanceCount_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SHADER_PROGRAM_H_

