/**
 * @file Material.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that represents the union of a shader program and multiple textures 
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

		struct TextureSlot
		{
			PSPtr< Texture > texture;
			PString uniformID;
		};
		
	public:


		/**
		 * @brief Construct a new Material
		 * 
		 * @param name 
		 * @param shaderProgram 
		 * @param usesTransparency 
		 */
		Material
		(
			const PString& name,
			PSPtr< Shader_Program > shaderProgram,
			bool usesTransparency = false
		);

		/**
		 * @brief Construct a new Material
		 * 
		 * @param name 
		 * @param pathVertexShader 
		 * @param pathFragmentShader 
		 * @param usesTransparency 
		 */
		Material
		(
			const PString& name,
			const PString& pathVertexShader,
			const PString& pathFragmentShader,
			bool usesTransparency = false
		);

	public:

		/**
		 * @brief Use this material
		 * 
		 */
		void use();

		/**
		 * @brief Try to disable all the textures // #WIP
		 * 
		 */
		void desuse();

	public:

		/**
		 * @brief apply the local uniforms
		 * 
		 */
		void apply_local_uniforms();

		/**
		 * @brief apply the shared uniforms
		 * 
		 */
		void apply_shared_uniforms();

	public:

		/**
		 * @brief Add a generic texture
		 * 
		 * @param texture 
		 * @param uniformName 
		 * @return PSPtr< Texture > 
		 */
		PSPtr< Texture > add_texture(PSPtr< Texture > texture, const PString& uniformName);

		/**
		 * @brief Add a texture cube
		 * 
		 * @param texturePath 
		 * @param uniformName 
		 * @return PSPtr< Texture > 
		 */
		PSPtr< Texture > add_texture_cube(const PString& texturePath, const PString& uniformName);

		/**
		 * @brief Add a texture 2D
		 * 
		 * @param texturePath 
		 * @param uniformName 
		 * @return PSPtr< Texture > 
		 */
		PSPtr< Texture > add_texture_2D(const PString& texturePath, const PString& uniformName);

		/**
		 * @brief Add a generic texture by name
		 * 
		 * @param textureName 
		 * @param uniformName 
		 * @return PSPtr< Texture > 
		 */
		PSPtr< Texture > add_texture_by_name(const PString& textureName, const PString& uniformName);

	public:

		/**
		 * @brief Delete all the textures
		 * 
		 */
		void clear_textures()
		{
			textures_.clear();
		}

	public:

		/**
		 * @brief Return if exists a texture with name
		 * 
		 * @param textureName 
		 * @return true 
		 * @return false 
		 */
		bool exists_texture_with_name(const PString& textureName);

		/**
		 * @brief Return if is saved the input texture 
		 * 
		 * @param texture 
		 * @return true 
		 * @return false 
		 */
		bool exists_texture(PSPtr< Texture > texture);
		
	public:

		/**
		 * @brief Set the uniforms
		 * 
		 * @param id 
		 * @param name 
		 * @param value 
		 * @param isSharedUniform 
		 * @return true 
		 * @return false 
		 */
		bool set_uniform(const char* id, const PString& name, const GLint    value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const GLuint   value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const GLfloat  value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PVec2&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PVec3&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PVec4&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PMat3&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PMat4&	 value, bool isSharedUniform = false);

	public:

		/**
		 * @brief Returns the texture with name
		 * 
		 * @param textureName 
		 * @return PSPtr< Texture > 
		 */
		PSPtr< Texture > get_texture_with_name(const PString& textureName);
	
	public:

		/**
		 * @brief Return the instance identification
		 * 
		 * @return unsigned 
		 */
		unsigned instanceID() const
		{
			return instanceID_;
		}

		/**
		 * @brief Return the name
		 * 
		 * @return const PString& 
		 */
		const PString& name() const
		{
			return name_;
		}

		/**
		 * @brief Return a pointer to the shader program object
		 * 
		 * @return Shader_Program* 
		 */
		Shader_Program* shaderProgramPtr() const
		{
			return shaderProgram_.get();
		}

		/**
		 * @brief Return the shader program object
		 * 
		 * @return PSPtr< Shader_Program > 
		 */
		PSPtr< Shader_Program > shaderProgram() const
		{
			return shaderProgram_;
		}

		/**
		 * @brief Return if this material uses transparency
		 * 
		 * @return true 
		 * @return false 
		 */
		bool usesTransparency()
		{
			return usesTransparency_;
		}

	protected:

		/**
		 * @brief Allocate a uniform with variant type
		 * 
		 * @param id 
		 * @param name 
		 * @param type 
		 * @param isSharedUniform 
		 * @return Uniform* 
		 */
		Uniform* allocate_uniform(const char* id, const PString& name, Var_GL::Type type, bool isSharedUniform = false);

	protected:

		/**
		 * @brief Apply all the uniforms of any kind
		 * 
		 * @param uniformsMap 
		 */
		void apply_uniforms(PMap< PString, Uniform>& uniformsMap);

	protected:

		PMap< PString, TextureSlot > textures_;
		PSPtr< Shader_Program > shaderProgram_;

	protected:

		PMap< PString, Uniform> localUniforms_;
		PMap< PString, Uniform> sharedUniforms_;

	protected:

		PString name_;
		unsigned int instanceID_;

	private:

		static unsigned instanceCount_;

	private:

		bool usesTransparency_;

	};

} //!namespace prz

#endif // !OPENGL_SCENE_MATERIAL_H_
