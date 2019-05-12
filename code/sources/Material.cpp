#include "Material.hpp"

namespace prz
{
	PSPtr< Material > Material::default_material()
	{
		return PSPtr< Material >();
	}

	bool Material::set(const char* id, const PString& name, const GLint value)
    {
        Uniform * uniform = allocate_uniform(id, name, Var::Type::INT);

        if (uniform)
        {
            uniform->value.data.gl_int = value;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const GLuint value)
    {
        Uniform * uniform = allocate_uniform(id, name, Var::Type::UNSIGNED_INT);

        if (uniform)
        {
            uniform->value.data.gl_uint = value;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const GLfloat value)
    {
        Uniform * uniform = allocate_uniform(id, name, Var::Type::FLOAT);

        if (uniform)
        {
            uniform->value.data.gl_float = value;

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const PVec2& vector2)
    {
        Uniform * uniform = allocate_uniform(id, name, Var::Type::VECTOR2);

        if (uniform)
        {
            uniform->value.data.gl_vec2[0] = vector2[0];
            uniform->value.data.gl_vec2[1] = vector2[1];

            return true;
        }

        return false;
    }

    bool Material::set(const char* id, const PString& name, const PVec3& vector3)
    {
        Uniform * uniform = allocate_uniform(id, name, Var::Type::VECTOR3);

        if (uniform)
        {
            uniform->value.data.gl_vec3[0] = vector3[0];
            uniform->value.data.gl_vec3[1] = vector3[1];
            uniform->value.data.gl_vec3[2] = vector3[2];

            return true;
        }

        return false;
    }

	bool Material::set(const char* id, const PString& name, const PVec4& vector4)
	{
		Uniform* uniform = allocate_uniform(id, name, Var::Type::VECTOR4);

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

	Uniform* Material::allocate_uniform(const char* id, const PString& name, Var::Type type)
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
			case Var::Type::INT:			shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_int); break;
			case Var::Type::UNSIGNED_INT:   shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_uint); break;
			case Var::Type::FLOAT:			shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_float); break;
			case Var::Type::VECTOR2:		shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_vec2); break;
			case Var::Type::VECTOR3:		shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_vec3); break;
			case Var::Type::VECTOR4:		shaderProgram_->set_uniform_value(uniform.index, uniform.value.data.gl_vec4); break;
			default:
				assert(false);
			}
		}
	}

}