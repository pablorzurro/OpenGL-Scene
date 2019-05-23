#include <Skybox.hpp>

#include <Camera.hpp>
#include <Material.hpp>
#include <Texture.hpp>
#include <Texture_Loader.hpp>

#include <Utilities.hpp>

namespace prz
{
	Skybox::Skybox(const PString& textureRootPath, const PString& pathVertexShader, const PString& pathFragmentShader) :
		material_(make_shared< Material >("Skybox_Material", pathVertexShader, pathFragmentShader))
	{
		textureCube_ = Texture_Loader::instance().load_cube_map(textureRootPath);
	}

	Skybox::Skybox(PSPtr<Texture> cubeMap, PSPtr<Shader_Program> shaderProgram) :
		material_(make_shared< Material >("Skybox_Material", shaderProgram)),
		textureCube_(cubeMap)
	{}

	void Skybox::draw(PSPtr< Camera > camera)
	{
		//GLint prevCullFaceMode;
		//glGetIntegerv(GL_CULL_FACE_MODE, &prevCullFaceMode);
		//GLint prevDepthFuncMode;
		//glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFuncMode);

		if (textureCube_ && camera)
		{
			glCullFace(GL_FRONT);
			//glDepthFunc(GL_LEQUAL);

			material_->use();

			//glEnable(GL_TEXTURE_CUBE_MAP);
			textureCube_->bind();

			//PMat4 view = PMat4(PMat3(camera->viewMatrix())); // Deny the position in the view matrix 

			material_->set_uniform("proj_matrix", "proj_matrix", camera->projectionMatrix());
			material_->set_uniform("view_matrix", "view_matrix", camera->viewMatrix());
			material_->apply_local_uniforms();

			glDepthMask(GL_FALSE);
			{
				cube_.draw();

			} glDepthMask(GL_TRUE);
		} 
			glCullFace(GL_BACK);
			//glDepthFunc(prevDepthFuncMode);
	}
}