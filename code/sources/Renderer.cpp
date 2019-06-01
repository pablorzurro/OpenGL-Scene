#include <Renderer.hpp>

#include <Camera.hpp>
#include <Model.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <Transform.hpp>
#include <Entity.hpp>
#include "Shader_Program.hpp"
#include <Transform.hpp>

namespace prz
{
	void Renderer::render(const PSPtr< Camera > activeCamera)
	{
		render_queue(renderQueue_, activeCamera);

		// Render the transparency materials queue after the non transparent materials

		glEnable(GL_BLEND);
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			render_queue(transparencyRenderQueue_, activeCamera);
			
		} glDisable(GL_BLEND);
	}

	bool Renderer::subscribe_entity(PSPtr< Entity > entity)
	{
		if (entity && !is_entity_subscribed(entity))
		{
			subscribedEntities_[entity->name()] = entity;
			entity->transform().set_renderer(this);

			return true;
		}

		return false;
	}
	bool Renderer::unsubscribe_entity(PSPtr< Entity > entity)
	{
		return subscribedEntities_.erase(entity->name());
	}

	bool prz::Renderer::is_entity_subscribed(PSPtr<Entity> entity) const
	{
		return entity && is_entity_subscribed(entity->name());
	}

	void Renderer::render_queue(Shader_Program_Batches& queueMap, const PSPtr< Camera > activeCamera)
	{
		for (auto& shaderMaterialPair : queueMap)
		{
			for (auto& materialBatch : shaderMaterialPair.second)
			{
				PSPtr< Material > material = materialBatch.first;

				material->use();

				set_material_shared_uniforms(material, activeCamera);
				material->apply_shared_uniforms();

				for (auto& transformMeshListPair : materialBatch.second)
				{
					Transform* modelTransform = transformMeshListPair.first;

					set_material_local_uniforms(material, modelTransform);
					material->apply_local_uniforms();

					PList < PSPtr< Mesh > >& meshes = *transformMeshListPair.second;

					for (auto& mesh : meshes)
					{
						mesh->draw();
						assert(glGetError() == GL_NO_ERROR);
					}
				}

				// Disable all texture slots after use it. Try of solve the framebuffer texture problem
				/*material->desuse(); */
			}
		}
	}

	void Renderer::update_render_queues()
	{
		renderQueue_.clear();
		transparencyRenderQueue_.clear();

		for (auto& entityPair : subscribedEntities_)
		{
			PSPtr< Entity > entity = entityPair.second;
			assert(entity);

			Transform& entityTransform = entity->transform();

			if (entityTransform.renderer() == this && entityTransform.isVisible())
			{
				PMap< PString, PSPtr< Model > >& entityModels = entity->models();

				for (auto& pair : entityModels)
				{
					PSPtr< Model >& model = pair.second;

					for (auto& meshesByMaterial : model->meshesByMaterial())
					{
						PSPtr< Material > material = meshesByMaterial.first;
						PSPtr< Shader_Program > shaderProgram = material->shaderProgram();
						PList< PSPtr< Mesh > >* meshes = &meshesByMaterial.second;

						assert(material);
						assert(shaderProgram);
						assert(meshes->size() > 0); // There should not be any empty mesh list here.

						if (material->usesTransparency())
						{
							// Fill the transparencies render queue with materials that use transparencies
							transparencyRenderQueue_[shaderProgram][material][&entityTransform] = meshes;
						}
						else
						{
							// Fill the normal render queue with materials that don't use transparencies
							renderQueue_[shaderProgram][material][&entityTransform] = meshes;
						}

						// Add here another layer here to separate the meshes of a transform by material
					}
				}
			}
		}
	}

	void Renderer::set_material_shared_uniforms(PSPtr<Material> material, const PSPtr< Camera > activeCamera)
	{
		// Try to set each shared uniform with "brute force", setting every known uniform from the created shaders

		material->set_uniform("proj_matrix", "projection_matrix", activeCamera->projectionMatrix(), true);
		material->set_uniform("view_matrix", "view_matrix", activeCamera->viewMatrix(), true);
		material->set_uniform("light_color", "light_color", PVec3(1.f, 1.f, 1.f), true);
		material->set_uniform("light_pos", "light_position", PVec3(-100.f, 70.f, -20.f), true);
		material->set_uniform("view_pos", "view_pos", activeCamera->transform().translation() , true);
		material->set_uniform("ambient_intensity", "ambient_intensity", 0.5f, true);
		material->set_uniform("camera_pos", "camera_pos", activeCamera->transform().translation());
	}

	void Renderer::set_material_local_uniforms(PSPtr<Material> material, Transform* transform)
	{
		// Try to set each local uniform with "brute force", setting every known uniform from the created shaders
		material->set_uniform("model_matrix", "model_matrix", transform->worldMatrix());
	}
}
