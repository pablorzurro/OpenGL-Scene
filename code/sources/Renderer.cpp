#include "Renderer.hpp"
#include <Model.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <Transform.hpp>
#include <Entity.hpp>
#include "Shader_Program.hpp"

namespace prz
{
	void Renderer::render()
	{
		for (auto& shaderMaterialPair : renderQueue_)
		{
			PSPtr< Shader_Program > shaderProgram = shaderMaterialPair.first;
			shaderProgram->use();

			for (auto& materialBatch : shaderMaterialPair.second)
			{
				PSPtr< Material > material = materialBatch.first;
				material->use();

				for (auto& transformMeshListPair : materialBatch.second)
				{
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

			if (entityTransform.renderer() == this)
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
}
