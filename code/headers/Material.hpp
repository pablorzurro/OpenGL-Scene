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

		struct TextureSlot
		{
			PSPtr< Texture > texture;
			GLuint uniformID;
		};
		
	public:


		Material(const PString& name, PSPtr< Shader_Program > shaderProgram):
			name_(name),
			shaderProgram_(shaderProgram),
			instanceID_(instanceCount_++)
		{}
		Material(const PString& name, const PString& pathVertexShader, const PString& pathFragmentShader);

	public:

		static PSPtr< Material > default_material();

	public:

		void use();

	public:

		void apply_local_uniforms();
		void apply_shared_uniforms();

	public:

		PSPtr< Texture > add_texture(PSPtr< Texture > texture, const PString& uniformName);
		PSPtr< Texture > add_texture_cube(const PString& texturePath, const PString& uniformName);
		PSPtr< Texture > add_texture_2D(const PString& texturePath, const PString& uniformName);
		PSPtr< Texture > add_texture_by_name(const PString& textureName, const PString& uniformName);

	public:

		bool exists_texture_with_name(const PString& textureName);
		bool exists_texture(PSPtr< Texture > texture);
		
	public:

		bool set_uniform(const char* id, const PString& name, const GLint    value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const GLuint   value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const GLfloat  value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PVec2&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PVec3&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PVec4&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PMat3&	 value, bool isSharedUniform = false);
		bool set_uniform(const char* id, const PString& name, const PMat4&	 value, bool isSharedUniform = false);

	public:

		PSPtr< Texture > get_texture_with_name(const PString& textureName);
	
	public:

		unsigned instanceID() const
		{
			return instanceID_;
		}

		const PString& name() const
		{
			return name_;
		}

		Shader_Program* shaderProgramPtr() const
		{
			return shaderProgram_.get();
		}

		PSPtr< Shader_Program > shaderProgram() const
		{
			return shaderProgram_;
		}

	protected:

		Uniform* allocate_uniform(const char* id, const PString& name, Var_GL::Type type, bool isSharedUniform = false);

	protected:

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
	};

} //!namespace prz

#endif // !OPENGL_SCENE_MATERIAL_H_
