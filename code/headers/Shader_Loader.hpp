/**
 * @file Shader_Loader.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to load and store shaders
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

	/**
	 * @brief Class to load and store materials
	 * 
	 */
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

		/**
		 * @brief Load a shader by:
		 * 
		 * @param sourceCodeFilePath 
		 * @return PSPtr< Shader > 
		 */
		PSPtr< Shader > load_shader(const PString& sourceCodeFilePath);
		
	public:

		/**
		 * @brief Unload a previously loaded shader
		 * 
		 * @param shader 
		 * @return true 
		 * @return false 
		 */
		bool unload_shader(PSPtr< Shader > shader)
		{
			if (shader && is_shader_loaded(shader->path()))
			{
				loadedShadersByName_.erase(shader->name());
				loadedShaders_.erase(shader->path());
				
				if (shader->type() == Shader::Type::FRAGMENT_SHADER)
				{
					loadedFragmentShaders_.erase(shader->path());
					loadedFragmentShadersByName_.erase(shader->name());
				}
				else if (shader->type() == Shader::Type::VERTEX_SHADER)
				{
					loadedVertexShaders_.erase(shader->path());
					loadedVertexShadersByName_.erase(shader->name());
				}

				return true;
			}

			return false;
		}

		/**
		 * @brief Unload a shader by: 
		 * 
		 * @param shaderPath 
		 * @return true 
		 * @return false 
		 */
		bool unload_shader(const PString& shaderPath)
		{
			return unload_shader(get_shader(shaderPath));
		}

		/**
		 * @brief Umload a shader by:
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool unload_shader_by_name(const PString& name)
		{
			return unload_shader(get_shader_by_name(name));
		}

	public:

		/**
		 * @brief Return if a shader is loaded by:
		 * 
		 * @param shaderPath 
		 * @return true 
		 * @return false 
		 */
		bool is_shader_loaded (const PString& shaderPath) const // Remember that a texture with multiple images is stored with the first path received
		{
			return loadedShaders_.find(shaderPath) != loadedShaders_.end();
		}

		/**
		 * @brief  Return if a shader is loaded by:
		 * 
		 * @param shaderName 
		 * @return true 
		 * @return false 
		 */
		bool is_shader_loaded_by_name(const PString& shaderName) const
		{
			return loadedShadersByName_.find(shaderName) != loadedShadersByName_.end();
		}

		/**
		 * @brief Return if a vertex shader is loaded by:
		 * 
		 * @param vertexShaderPath 
		 * @return true 
		 * @return false 
		 */
		bool is_vertex_shader_loaded(const PString& vertexShaderPath) const // Remember that a texture with multiple images is stored with the first path received
		{
			return loadedVertexShaders_.find(vertexShaderPath) != loadedVertexShaders_.end();
		}

		/**
		 * @brief Return if a vertex shader is loaded by:
		 * 
		 * @param vertexShaderName 
		 * @return true 
		 * @return false 
		 */
		bool is_vertex_shader_loaded_by_name(const PString& vertexShaderName) const
		{
			return loadedVertexShadersByName_.find(vertexShaderName) != loadedVertexShadersByName_.end();
		}

		/**
		 * @brief Return if a fragment shader is loaded by:
		 * 
		 * @param fragmentShaderPath 
		 * @return true 
		 * @return false 
		 */
		bool is_fragment_shader_loaded(const PString& fragmentShaderPath) const // Remember that a texture with multiple images is stored with the first path received
		{
			return loadedFragmentShaders_.find(fragmentShaderPath) != loadedFragmentShaders_.end();
		}

		/**
		 * @brief Return if a fragment shader is loaded by:
		 * 
		 * @param fragmentShaderName 
		 * @return true 
		 * @return false 
		 */
		bool is_fragment_shader_loaded_by_name(const PString& fragmentShaderName) const
		{
			return loadedFragmentShadersByName_.find(fragmentShaderName) != loadedFragmentShadersByName_.end();
		}

	public:

		/**
		 * @brief Return the shader by: 
		 * 
		 * @param shaderPath 
		 * @return PSPtr< Shader > 
		 */
		PSPtr< Shader > get_shader(const PString& shaderPath)
		{
			return is_shader_loaded(shaderPath) ? loadedShaders_[shaderPath] : PSPtr< Shader >();
		}

		/**
		 * @brief Return the shader by name
		 * 
		 * @param shaderName 
		 * @return PSPtr< Shader > 
		 */
		PSPtr< Shader > get_shader_by_name(const PString& shaderName)
		{
			return is_shader_loaded_by_name(shaderName) ? loadedShadersByName_[shaderName] : PSPtr< Shader >();
		}

		/**
		 * @brief Return the vertex shader by: 
		 * 
		 * @param vertexShaderPath 
		 * @return PSPtr< Vertex_Shader > 
		 */
		PSPtr< Vertex_Shader > get_vertex_shader(const PString& vertexShaderPath)
		{
			return is_vertex_shader_loaded(vertexShaderPath) ? loadedVertexShaders_[vertexShaderPath] : PSPtr< Vertex_Shader >();
		}

		/**
		 * @brief Return the vertex shader by name
		 * 
		 * @param vertexShaderName 
		 * @return PSPtr< Vertex_Shader > 
		 */
		PSPtr< Vertex_Shader > get_vertex_shader_by_name(const PString& vertexShaderName)
		{
			return is_vertex_shader_loaded_by_name(vertexShaderName) ? loadedVertexShadersByName_[vertexShaderName] : PSPtr< Vertex_Shader >();
		}

		/**
		 * @brief Return the fragment shader by: 
		 * 
		 * @param fragmentShaderPath 
		 * @return PSPtr< Fragment_Shader > 
		 */
		PSPtr< Fragment_Shader > get_fragment_shader(const PString& fragmentShaderPath)
		{
			return is_fragment_shader_loaded(fragmentShaderPath) ? loadedFragmentShaders_[fragmentShaderPath] : PSPtr< Fragment_Shader >();
		}

		/**
		 * @brief Return the fragment shader by name
		 * 
		 * @param fragmentShaderName 
		 * @return PSPtr< Fragment_Shader > 
		 */
		PSPtr< Fragment_Shader > get_fragment_shader_by_name(const PString& fragmentShaderName)
		{
			return is_fragment_shader_loaded_by_name(fragmentShaderName) ? loadedFragmentShadersByName_[fragmentShaderName] : PSPtr< Fragment_Shader >();
		}

	private:

		/**
		 * @brief Construct a new Shader_Loader (private)
		 * 
		 */
		Shader_Loader(){}

	private:

		PMap< PString, PSPtr< Shader >> loadedShaders_;
		PMap< PString, PSPtr< Shader> > loadedShadersByName_;

	private:

		PMap< PString, PSPtr< Fragment_Shader> > loadedFragmentShaders_;
		PMap< PString, PSPtr< Fragment_Shader> > loadedFragmentShadersByName_;
		
		PMap< PString, PSPtr< Vertex_Shader> > loadedVertexShaders_;
		PMap< PString, PSPtr< Vertex_Shader> > loadedVertexShadersByName_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SHADER_LOADER_H_
