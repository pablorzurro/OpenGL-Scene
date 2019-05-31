
#ifndef OPENGL_SCENE_FRAMEBUFFER_H_
#define OPENGL_SCENE_FRAMEBUFFER_H_

#include <Declarations.hpp>

namespace prz
{
	
	class Material;
	class Shader_Program;
	class Mesh;
	class Texture;
	class Scene;

	class Framebuffer
	{
	public:

		Framebuffer
		(
			Scene& scene,
			PSPtr< Shader_Program > shaderProgram,
			unsigned int width,
			unsigned int height
		);

		Framebuffer
		(
			Scene& scene,
			const PString& pathVertexShader,
			const PString& pathFragmentShader,
			unsigned int width,
			unsigned int height
		);
		
		~Framebuffer()
		{
			unbind();
			glDeleteBuffers(1, &framebufferId_);
		}

	public:

		void render_first_pass();
		void render_second_pass();

	public:

		void bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, framebufferId_);
		}

		void unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	public:

		void reset(PSPtr< Shader_Program > shaderProgram, unsigned int width, unsigned int height);
		void reset(unsigned int width, unsigned int height);

	public:

		unsigned int framebufferId()
		{
			return framebufferId_;
		}

	private:

		void create(PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height);

	private:

		PSPtr< Material > material_;
		PSPtr< Mesh > mesh_;

	private:
		
		Scene& scene_;

	private:

		unsigned int framebufferId_;
		unsigned int depthBufferId_;

	private:

		unsigned int width_;
		unsigned int height_;

	};

} // !namespace prz

#endif // !OPENGL_SCENE_FRAMEBUFFER_H_
