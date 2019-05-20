#include <Material.hpp>

#include <Shader_Program_Loader.hpp>
#include <Texture_Loader.hpp>
#include <Texture.hpp>
#include <Game.hpp>

namespace prz
{
	unsigned int Material::instanceCount_ = 0;

	Material::Material(const PString& name, const PString& pathVertexShader, const PString& pathFragmentShader) :
		Material(name, Shader_Program_Loader::instance().load_shader_program(pathVertexShader, pathFragmentShader))
	{}

	PSPtr< Material > Material::default_material()
	{
		static PSPtr< Material > material(new Material
		(
			"default_material",
			Shader_Program_Loader::instance().load_shader_program
			(
				Game::assetsFolderPath() + "shaders/fragment_shader.frag",
				Game::assetsFolderPath() + "shaders/vertex_shader.vert"
			)
		));

		return material;
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

	void Material::apply_local_uniforms()
	{
		apply_uniforms(localUniforms_);
	}

	void Material::apply_shared_uniforms()
	{
		apply_uniforms(sharedUniforms_);
	}

	bool Material::add_texture(PSPtr<Texture> texture)
	{
		if (texture)
		{
			textures_.push_back(texture);
			return true;
		}

		return false;
	}

	bool Material::add_texture_cube(const PString& texturePath)
	{
		return add_texture(Texture_Loader::instance().load_cube_map(texturePath));
	}

	bool Material::add_texture_2D(const PString& texturePath)
	{
		return add_texture(Texture_Loader::instance().load_texture2D(texturePath));
	}

	bool Material::add_texture_by_name(const PString& textureName)
	{
		add_texture(Texture_Loader::instance().get_texture_by_name(textureName));
	}

	Uniform* Material::allocate_uniform(const char* id, const PString & name, Var_GL::Type type, bool isSharedUniform)
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
		shaderProgram_->use();

		for (PSPtr< Texture> texture : textures_)
		{
			texture->bind();
		}

		apply_shared_uniforms();
	}


}