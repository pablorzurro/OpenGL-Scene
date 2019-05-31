#include <Material.hpp>

#include <Shader_Program_Loader.hpp>
#include <Texture_Loader.hpp>
#include <Texture.hpp>
#include <Game.hpp>

namespace prz
{
	unsigned int Material::instanceCount_ = 0;

	Material::Material(const PString& name, PSPtr<Shader_Program> shaderProgram, bool usesTransparency):
		name_(name),
		shaderProgram_(shaderProgram),
		instanceID_(instanceCount_++),
		usesTransparency_(usesTransparency)
	{}

	Material::Material(const PString& name, const PString& pathVertexShader, const PString& pathFragmentShader, bool usesTransparency) :
		Material(name, Shader_Program_Loader::instance().load_shader_program(pathVertexShader, pathFragmentShader), usesTransparency)
	{}

	bool Material::exists_texture_with_name(const PString& textureName)
	{
		return textures_.find(textureName) != textures_.end();
	}

	bool Material::exists_texture(PSPtr<Texture> texture)
	{
		if (texture)
		{
			return exists_texture_with_name(texture->name());
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const GLint value, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::INT, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_int = value;

			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const GLuint value, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::UNSIGNED_INT, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_uint = value;

			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const GLfloat value, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::FLOAT, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_float = value;

			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const PVec2 & vector2, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::VECTOR2, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_vec2 = vector2;

			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const PVec3 & vector3, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::VECTOR3, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_vec3 = vector3;

			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const PVec4 & vector4, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::VECTOR4, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_vec4[0] = vector4[0];
			uniform->value.data.gl_vec4[1] = vector4[1];
			uniform->value.data.gl_vec4[2] = vector4[2];
			uniform->value.data.gl_vec4[3] = vector4[3];

			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const PMat3 & value, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::MATRIX33, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_mat33 = value;
			return true;
		}

		return false;
	}

	bool Material::set_uniform(const char* id, const PString & name, const PMat4 & value, bool isSharedUniform)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::MATRIX44, isSharedUniform);

		if (uniform)
		{
			uniform->value.data.gl_mat44 = value;
			return true;
		}

		return false;
	}

	PSPtr<Texture> Material::get_texture_with_name(const PString& textureName)
	{
		return exists_texture_with_name(textureName) ? textures_[textureName].texture : PSPtr< Texture >();
	}

	void Material::apply_local_uniforms()
	{
		apply_uniforms(localUniforms_);
	}

	void Material::apply_shared_uniforms()
	{
		apply_uniforms(sharedUniforms_);
	}

	PSPtr< Texture > Material::add_texture(PSPtr<Texture> texture, const PString& uniformName)
	{
		if (texture && shaderProgram_)
		{
			GLuint uniformID = shaderProgram_->get_uniform_id(uniformName.c_str()) != -1;
			if (uniformID != -1)
			{
				TextureSlot textureSlot;

				textureSlot.texture = texture;
				textureSlot.uniformID = uniformName;

				textures_[texture->name()] = textureSlot;

				return textures_[texture->name()].texture;
			}
		}

		return PSPtr< Texture >();
	}

	PSPtr< Texture > Material::add_texture_cube(const PString& texturePath, const PString& uniformName)
	{
		return add_texture(Texture_Loader::instance().load_cube_map(texturePath), uniformName);
	}

	PSPtr< Texture > Material::add_texture_2D(const PString& texturePath, const PString& uniformName)
	{
		return add_texture(Texture_Loader::instance().load_texture2D(texturePath), uniformName);
	}

	PSPtr< Texture > Material::add_texture_by_name(const PString& textureName, const PString& uniformName)
	{
		return add_texture(Texture_Loader::instance().get_texture_by_name(textureName), uniformName);
	}

	Uniform* Material::allocate_uniform(const char* id, const PString & name, Var_GL::Type type, bool isSharedUniform)
	{
		if (shaderProgram_)
		{
			Uniform uniform;

			uniform.index = shaderProgram_->get_uniform_id(id);

			if (uniform.index >= 0)
			{
				uniform.value.type = type;

				if (isSharedUniform)
				{
					sharedUniforms_[name] = uniform;
					return &sharedUniforms_[name];
				}
				else
				{
					localUniforms_[name] = uniform;
					return &localUniforms_[name];
				}
			}
		}
		
		return nullptr;
	}

	void Material::apply_uniforms(PMap<PString, Uniform>& uniformsMap)
	{
		for (auto& pair : uniformsMap)
		{
			Uniform& uniform = pair.second;

			switch (uniform.value.type)
			{
			case Var_GL::Type::INT:				shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_int); break;
			case Var_GL::Type::UNSIGNED_INT:	shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_uint); break;
			case Var_GL::Type::FLOAT:			shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_float); break;
			case Var_GL::Type::VECTOR2:			shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_vec2); break;
			case Var_GL::Type::VECTOR3:			shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_vec3); break;
			case Var_GL::Type::VECTOR4:			shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_vec4); break;
			case Var_GL::Type::MATRIX33:		shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_mat33); break;
			case Var_GL::Type::MATRIX44:		shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_mat44); break;
			default:
				assert(false);
			}
		}
	}

	void Material::use()
	{
		if (shaderProgram_)
		{
			shaderProgram_->use();
			
			unsigned int i = 0;

			for (auto& pair : textures_)
			{
				TextureSlot& textureSlot = pair.second;

				if (i > 15)
				{
					break; // A shader program can have only 16 texture slots
				}

				if (i == 1)
				{
					i;
				}

				glActiveTexture(GL_TEXTURE0 + i);
				assert(glGetError() == GL_NO_ERROR);
				textureSlot.texture->bind();
				assert(glGetError() == GL_NO_ERROR);
				glUniform1i(shaderProgram_->get_uniform_id(textureSlot.uniformID.c_str()), i);
				assert(glGetError() == GL_NO_ERROR);

				i++;
			}
		}	
	}

	void Material::desuse()
	{
		unsigned int i = 0;

		for (auto& pair : textures_)
		{
			TextureSlot& textureSlot = pair.second;

			if (i > 15)
			{
				break; // A shader program can have only 16 texture slots
			}

			if (i == 1)
			{
				i;
			}

			glActiveTexture(GL_TEXTURE0 + i);
			glDisable(GL_TEXTURE_2D);

			i++;
		}
	}
}
