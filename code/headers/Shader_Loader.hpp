/**
 * @file Shader_Loader.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_SHADER_LOADER_H_
#define OPENGL_SCENE_SHADER_LOADER_H_

#include <Fragment_Shader.hpp>
#include <Vertex_Shader.hpp>
#include <Source_Code.hpp>

#include <Declarations.hpp>
#include <Utilities.hpp>

namespace prz
{

	class Shader_Loader
	{
	public:

		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return Shader_Loader&
		 */
		static Shader_Loader& instance()
		{
			static Shader_Loader instance;
			return instance;
		}

	public:

		PSPtr< Shader > load_shader(const PString& sourceCodeFilePath)
		{
			Source_Code sourceCode(sourceCodeFilePath);
			PString name = split_string_by_separator(sourceCodeFilePath, "/");
			PString fileExtension = "." + split_string_by_separator(name, ".");
			
			if (sourceCode.is_not_empty())
			{
				PSPtr< Shader > shader;

				if (fileExtension == ".frag")
				{
					shader = make_shared< Fragment_Shader >(sourceCode, name);
				}
				else if (fileExtension == ".vert")
				{
					shader = make_shared< Vertex_Shader >(sourceCode, name);
				}

				if (!shader->has_compilation_failed())
				{
					loadedShaders_[sourceCodeFilePath] = shader;

					loadedShadersByName_[name] = shader.get();

					return loadedShaders_[sourceCodeFilePath];
				}
			}
			
			return PSPtr< Shader >();
		}
	
	public:

		bool unload_shader(const PString& shaderPath)
		{
			if (is_shader_loaded(shaderPath))
			{
				loadedShadersByName_.erase(loadedShaders_[shaderPath]->name());
				loadedShaders_.erase(shaderPath);
			}
		}

		bool unload_shader_by_name(const PString& shaderName)
		{
			if (is_shader_loaded_by_name(shaderName))
			{
				loadedShaders_.erase(loadedShaders_[shaderName]->path());
				loadedShadersByName_.erase(shaderName);
			}
		}

	public:

		bool is_shader_loaded (const PString& shaderPath) const // Remember that a texture with multiple images is stored with the first path received
		{
			return loadedShaders_.find(shaderPath) != loadedShaders_.end();
		}

	
		bool is_shader_loaded_by_name(const PString& shaderName) const
		{
			return loadedShadersByName_.find(shaderName) != loadedShadersByName_.end();
		}

	public:

		PSPtr< Shader > get_shader(const PString& shaderPath)
		{
			return is_shader_loaded(shaderPath) ? loadedShaders_[shaderPath] : nullptr;
		}

		Shader* get_shader_by_name(const PString& shaderName)
		{
			return is_shader_loaded_by_name(shaderName) ? loadedShadersByName_[shaderName] : nullptr;
		}

	private:

		Shader_Loader(){}

	private:

		PMap< PString, PSPtr< Shader >> loadedShaders_;
		PMap< PString, Shader*> loadedShadersByName_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SHADER_LOADER_H_
