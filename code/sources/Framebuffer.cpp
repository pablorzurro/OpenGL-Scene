#include <Framebuffer.hpp>

#include <Material.hpp>
#include <Mesh.hpp>
#include <Texture_2D.hpp>
#include <Shader_Program.hpp>
#include <Shader_Program_Loader.hpp>
#include <Projected_Plane.hpp>
#include <Scene.hpp>
#include <Plane.hpp>
#include <Camera.hpp>

namespace prz
{
	Framebuffer::Framebuffer(Scene& scene, PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height) :
		scene_(scene),
		framebufferId_(4294967295),
		depthBufferId_(4294967295)
	{
		create(shaderProgram, width, height);
	}

	Framebuffer::Framebuffer(Scene& scene, const PString& pathVertexShader, const PString& pathFragmentShader, unsigned int width, unsigned int height) :
		Framebuffer(scene, Shader_Program_Loader::instance().load_shader_program(pathVertexShader, pathFragmentShader), width, height)
	{}

	void Framebuffer::render_first_pass()
	{
		glViewport(0, 0, width_, height_);

		bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Framebuffer::render_second_pass()
	{
		// Check the state of the shader program

		PVec2 windowSize = scene_.get_window_size();
		glViewport(0, 0, windowSize.x, windowSize.y);

		// Bind the window buffer
		unbind();

		material_->use();

		mesh_->draw();
	}

	void Framebuffer::reset(PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height)
	{
		if (!material_ || material_->shaderProgram() != shaderProgram)
		{
			material_ = make_shared< Material >("Framebuffer_Material", shaderProgram);
		}

		reset(width, height);
	}

	void Framebuffer::reset(unsigned int width, unsigned int height)
	{
		if ((width_ != width && height_ != height)  || !material_->get_texture_with_name("Framebuffer_Texture"))
		{
			width_ = width;
			height_ = height;

			PSPtr<Texture > texture = make_shared< Texture_2D >
			(
				"Framebuffer_Texture",
				width_,
				height_,
				Texture::Color_Format::RGB
			);

			material_->add_texture(texture, "no_uniform_value");

			bind();
			{
				// Modify and create the depthBuffer(if not existing)
				{
					if (depthBufferId_ == 4294967295)
					{
						glGenRenderbuffers(1, &depthBufferId_);
					}

					glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId_);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId_);
				}

				unsigned int textureID = material_->get_texture_with_name("Framebuffer_Texture")->textureID();

				// Set the framebuffer
				{
					glFramebufferTexture
					(
						GL_FRAMEBUFFER,
						GL_COLOR_ATTACHMENT0,
						textureID,
						0
					);

					const GLenum draw_buffer = GL_COLOR_ATTACHMENT0;

					glDrawBuffers(1, &draw_buffer);
				}

				// Check if the frame buffer is ready or has been a failure
				assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
				assert(glGetError() == GL_NO_ERROR);

			} unbind();
		}
	}

	void Framebuffer::create(PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height)
	{
		// Generate the framebuffer
		glGenFramebuffers(1, &framebufferId_);
		
		reset(shaderProgram, width, height);

		mesh_ = make_shared< Projected_Plane >("Framebuffer_Projected_Plane");
	}
}