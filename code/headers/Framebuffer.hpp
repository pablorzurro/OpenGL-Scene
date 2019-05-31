/**
 * @file Framebuffer.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that fills a texture with the render information of each tick
 * @version 0.1
 * @date 30-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

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

	/**
	 * @brief Class that fills a texture with the render information of each tick (#WIP)
	 * 
	 */
	class Framebuffer
	{
	public:

		/**
		 * @brief Construct a new Framebuffer
		 * 
		 * @param scene 
		 * @param shaderProgram 
		 * @param width 
		 * @param height 
		 */
		Framebuffer
		(
			Scene& scene,
			PSPtr< Shader_Program > shaderProgram,
			unsigned int width,
			unsigned int height
		);
		

		/**
		 * @brief Construct a new Framebuffer
		 * 
		 * @param scene 
		 * @param pathVertexShader 
		 * @param pathFragmentShader 
		 * @param width 
		 * @param height 
		 */
		Framebuffer
		(
			Scene& scene,
			const PString& pathVertexShader,
			const PString& pathFragmentShader,
			unsigned int width,
			unsigned int height
		);
		
		Framebuffer(Framebuffer& other) = delete;

		/**
		 * @brief Destroy the Framebuffer and the members
		 * 
		 */
		~Framebuffer()
		{
			unbind();
			glDeleteBuffers(1, &framebufferId_);
			glDeleteBuffers(1, &renderBufferObjectId_);
			glDeleteTextures(1, &textureId_);
			glDeleteBuffers(1, &quadVBO_);
			glDeleteVertexArrays(1, &quadVAO_);
		}

	public:

		/**
		 * @brief render the framebuffer
		 * 
		 */
		void render();

	public:

		/**
		 * @brief bind the framebuffer
		 * 
		 */
		void bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, framebufferId_);
		}

		/**
		 * @brief select the main window buffer
		 * 
		 */
		void unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	public:

		/**
		 * @brief reset almost all members of this object 
		 * 
		 * @param shaderProgram 
		 * @param width 
		 * @param height 
		 */
		void reset(PSPtr< Shader_Program > shaderProgram, unsigned int width, unsigned int height);

		/**
		 * @brief reset the framebuffer by the changed size of the window 
		 * 
		 * @param width 
		 * @param height 
		 */
		void reset(unsigned int width, unsigned int height);

	public:

		/**
		 * @brief Return the current id of the framebuffer
		 * 
		 * @return unsigned int 
		 */
		unsigned int framebufferId()
		{
			return framebufferId_;
		}

	private:

		/**
		 * @brief Create the framebuffer
		 * 
		 * @param shaderProgram 
		 * @param width 
		 * @param height 
		 */
		void create(PSPtr<Shader_Program> shaderProgram, unsigned int width, unsigned int height);

	private:

		PSPtr< Shader_Program > shaderProgram_;
		PSPtr< Mesh > mesh_;

	private:
		
		Scene& scene_;

	private:

		unsigned int framebufferId_;
		unsigned int renderBufferObjectId_;
		unsigned int textureId_;
		unsigned int quadVBO_;
		unsigned int quadVAO_;

	private:

		unsigned int width_;
		unsigned int height_;

	};

} // !namespace prz

#endif // !OPENGL_SCENE_FRAMEBUFFER_H_
