#include <Renderer.hpp>

#include <Camera.hpp>
#include <Model.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <Transform.hpp>
#include <Entity.hpp>
#include "Shader_Program.hpp"

namespace prz
{
	void Renderer::render(const PSPtr< Camera > activeCamera)
	{
		for (auto& shaderMaterialPair : renderQueue_)
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
					}
				}
			}
		}
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

	void Renderer::update_render_queue()
	{
		renderQueue_.clear();

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

						renderQueue_[shaderProgram][material][&entityTransform] = meshes;
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
		material->set_uniform("light_color", "light_color", PVec3(255.f, 255.f, 255.f), true);
		material->set_uniform("light_pos", "light_position", PVec3(0.f, 20.f, 0.f), true);
		material->set_uniform("ambient_intensity", "ambient_intensity", 0.15f, true);
	}

	void Renderer::set_material_local_uniforms(PSPtr<Material> material, Transform* transform)
	{
		// Try to set each local uniform with "brute force", setting every known uniform from the created shaders
		material->set_uniform("model_matrix", "model_matrix", transform->worldMatrix());
	}
}
