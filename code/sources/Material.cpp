#include <Material.hpp>
#include <Shader_Program_Loader.hpp>
#include <Game.hpp>

namespace prz
{
	unsigned int Material::instanceCount_ = 0;

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

	bool Material::set(const char* id, const PString& name, const GLint value)
    {
        Uniform * uniform = allocate_uniform(id, name, Var_GL::Type::INT);

        if (uniform)
        {
            uniform->value.data.gl_int = value;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const GLuint value)
    {
        Uniform * uniform = allocate_uniform(id, name, Var_GL::Type::UNSIGNED_INT);

        if (uniform)
        {
            uniform->value.data.gl_uint = value;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const GLfloat value)
    {
        Uniform * uniform = allocate_uniform(id, name, Var_GL::Type::FLOAT);

        if (uniform)
        {
            uniform->value.data.gl_float = value;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const PVec2& vector2)
    {
        Uniform * uniform = allocate_uniform(id, name, Var_GL::Type::VECTOR2);

        if (uniform)
        {
            uniform->value.data.gl_vec2 = vector2;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const PVec3& vector3)
    {
        Uniform * uniform = allocate_uniform(id, name, Var_GL::Type::VECTOR3);

        if (uniform)
        {
            uniform->value.data.gl_vec3 = vector3;

            return true;
        }

        return false;
    }

	bool Material::set(const char* id, const PString& name, const PVec4& vector4)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::VECTOR4);

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

	bool Material::set(const char* id, const PString& name, const PMat3& value)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::MATRIX33);

		if (uniform)
		{
			uniform->value.data.gl_mat33 = value;
			return true;
		}

		return false;
	}

	bool Material::set(const char* id, const PString& name, const PMat4& value)
	{
		Uniform* uniform = allocate_uniform(id, name, Var_GL::Type::MATRIX44);

		if (uniform)
		{
			uniform->value.data.gl_mat44 = value;
			return true;
		}

		return false;
	}

	Uniform* Material::allocate_uniform(const char* id, const PString& name, Var_GL::Type type)
	{
		Uniform uniform;

		uniform.index = shaderProgram_->get_uniform_id(id);

		if (uniform.index >= 0)
		{
			uniform.value.type = type;

			uniforms_[name] = uniform;

			return &uniforms_[name];
		}

		return nullptr;
	}

	void Material::use()
	{
		shaderProgram_->use();

		for (auto& pair : uniforms_)
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

}