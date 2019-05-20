#include <Skybox.hpp>

#include <Camera.hpp>
#include <Material.hpp>

namespace prz
{
	/*Skybox::Skybox(const PString& textureRootPath, const PString& textureName, const PString& pathVertexShader, const PString& pathFragmentShader) :
		
		cube_("skybox_cube"),

	{}

	Skybox::Skybox(PSPtr< Texture > cubeMap) :
		cubeMap_(Texture_Loader::instance().get_texture_cube(cubeMap->name()))
	{}*/
	Skybox::Skybox(const PString& textureRootPath, const PString& pathVertexShader, const PString& pathFragmentShader) :
		material_(make_shared< Material >("Skybox_Material", pathVertexShader, pathFragmentShader))
	{
		material_->add_texture_cube(textureRootPath);
	}

	Skybox::Skybox(PSPtr<Texture> cubeMap, PSPtr<Shader_Program> shaderProgram) :
		material_("Skybox_Material", shaderProgram)
	{
		material_->add_texture(cubeMap);
	}

	void Skybox::draw(PSPtr< Camera > camera)
	{
		glDepthMask(GL_FALSE);
		{
			shaderProgram_->use();
			{
				glm::mat4 view = glm::mat4(glm::mat3(camera->viewMatrix()));

				material_->use();
				cube_.draw();
			}

		} glDepthMask(GL_TRUE);
		
	}
}