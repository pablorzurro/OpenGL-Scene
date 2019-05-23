#include "Shader_Loader.hpp"

namespace prz
{
	PSPtr<Shader> Shader_Loader::load_shader(const PString& sourceCodeFilePath)
	{
		if (is_shader_loaded(sourceCodeFilePath))
		{
			return get_shader(sourceCodeFilePath);
		}

		Source_Code sourceCode(sourceCodeFilePath);
		PString name = split_string_by_separator(sourceCodeFilePath, "/");
		PString fileExtension = "." + split_string_by_separator(name, ".");

		if (sourceCode.is_not_empty())
		{
			PSPtr< Shader > shader;
			PSPtr<Fragment_Shader> fragShader;
			PSPtr<Vertex_Shader> vertShader;

			if (fileExtension == ".frag")
			{
				fragShader = make_shared< Fragment_Shader >(sourceCode, name);
				shader = fragShader;
			}
			else if (fileExtension == ".vert")
			{
				vertShader = make_shared< Vertex_Shader >(sourceCode, name);
				shader = vertShader;
			}

			if (shader && shader->is_compiled())
			{
				loadedShaders_[sourceCodeFilePath] = shader;
				loadedShadersByName_[name] = shader;

				if (fragShader)
				{
					loadedFragmentShaders_[sourceCodeFilePath] = loadedFragmentShadersByName_[name] = fragShader;
				}
				else if (vertShader)
				{
					loadedVertexShaders_[sourceCodeFilePath] = loadedVertexShadersByName_[name] = vertShader;
				}

				return loadedShaders_[sourceCodeFilePath];
			}
		}

		return PSPtr< Shader >();
	}


}
