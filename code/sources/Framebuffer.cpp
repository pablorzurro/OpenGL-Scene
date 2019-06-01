#include <Framebuffer.hpp>

#include <Mesh.hpp>
#include <Texture_2D.hpp>
#include <Shader_Program.hpp>
#include <Shader_Program_Loader.hpp>
#include <Projected_Plane.hpp>
#include <Scene.hpp>
#include <Camera.hpp>

namespace prz
{
	Framebuffer::Framebuffer(Scene& scene, PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height) :
		scene_(scene)
	{
		create(shaderProgram, width, height);
	}

	Framebuffer::Framebuffer(Scene& scene, const PString& pathVertexShader, const PString& pathFragmentShader, unsigned int width, unsigned int height) :
		Framebuffer(scene, Shader_Program_Loader::instance().load_shader_program(pathVertexShader, pathFragmentShader), width, height)
	{}

	void Framebuffer::render()
	{
		// Bind the window buffer
		unbind();

		glDisable(GL_DEPTH_TEST);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram_->use();

		glBindVertexArray(quadVAO_);
		glBindTexture(GL_TEXTURE_2D, textureId_);	// use the color attachment texture as the texture of the quad plane

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//mesh_->draw();
	}
		

	void Framebuffer::reset(PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height)
	{
		shaderProgram_ = shaderProgram;

		reset(width, height);
	}

	void Framebuffer::reset(unsigned int width, unsigned int height)
	{
		if (width_ != width && height_ != height)
		{
			width_ = width;
			height_ = height;

			// Create the framebuffer

			// Code from LearnOpenGL, mine didn't work :(

			glGenFramebuffers(1, &framebufferId_);
			glBindFramebuffer(GL_FRAMEBUFFER, framebufferId_);

			// create a color attachment texture

			glGenTextures(1, &textureId_);
			glBindTexture(GL_TEXTURE_2D, textureId_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId_, 0);

			// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

			glGenRenderbuffers(1, &renderBufferObjectId_);
			glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObjectId_);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_); // use a single renderbuffer object for both a depth AND stencil buffer.
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObjectId_); // now actually attach it

			// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			//glGenFramebuffers(1, &framebufferId_);
			//bind();
			//{
			//	// Attach the texture for the frambuffer
			//	{
			//		glGenTextures(1, &textureId_);
			//		glBindTexture(GL_TEXTURE_2D, textureId_);

			//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId_, 0);

			//		glTexImage2D(
			//			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0,
			//			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
			//		);
			//	}

			//	// Renderbuffer object 
			//	{
			//		glGenRenderbuffers(1, &renderBufferObjectId_);
			//		glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObjectId_);

			//		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
			//		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObjectId_);
			//	}

			//	// Attach the texture to the rbo 

			//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureId_, 0);

			//	// Check if the frame buffer is ready or has been a failure
			//	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
			//	assert(glGetError() == GL_NO_ERROR);

			//} unbind();
		}
	}

	void Framebuffer::create(PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height)
	{
		
		// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		static float quadVertices[] = 
		{ 
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
		};

		glGenVertexArrays(1, &quadVAO_);
		glGenBuffers(1, &quadVBO_);

		glBindVertexArray(quadVAO_);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO_);

		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		reset(shaderProgram, width, height);

		//mesh_ = make_shared< Projected_Plane >("Framebuffer_Projected_Plane");
	}
}