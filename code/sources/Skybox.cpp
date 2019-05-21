#include <Skybox.hpp>

#include <Camera.hpp>
#include <Material.hpp>
#include <Texture.hpp>

#include <Utilities.hpp>

namespace prz
{
	Skybox::Skybox(const PString& textureRootPath, const PString& pathVertexShader, const PString& pathFragmentShader) :
		material_(make_shared< Material >("Skybox_Material", pathVertexShader, pathFragmentShader)),
		textureCube_(material_->add_texture_cube(textureRootPath, "skybox"))
	{}

	Skybox::Skybox(PSPtr<Texture> cubeMap, PSPtr<Shader_Program> shaderProgram) :
		material_(make_shared< Material >("Skybox_Material", shaderProgram)),
		textureCube_(material_->add_texture(cubeMap, "skybox"))
	{}

	void Skybox::draw(PSPtr< Camera > camera)
	{
		if (textureCube_ && camera)
		{
			glDepthMask(GL_FALSE);
			{
				material_->use();
				{
					glm::mat4 view = glm::mat4(glm::mat3(camera->viewMatrix())); // Deny the position in the view matrix 

					material_->set_uniform("projection", "projection", camera->projectionMatrix());
					material_->set_uniform("view", "view", camera->viewMatrix());
					material_->set_uniform("skybox", "skybox", textureCube_->textureID());
					material_->apply_local_uniforms();

					cube_.draw();
				}

			} glDepthMask(GL_TRUE);
		}
	}
}