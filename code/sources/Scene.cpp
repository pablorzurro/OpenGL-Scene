#include <Scene.hpp>
#include <Entity.hpp>
#include <Transform.hpp>
#include <Texture_Loader.hpp>
#include <Skybox.hpp>
#include <Game.hpp>

#include <Shader_Program_Loader.hpp>

namespace prz
{

	Scene::Scene(Window& window) :
		window_(window),
		renderer_(*this),
		activeCamera_(*this, "Active_Camera_For_Testing"),
		skybox(Texture_Loader::instance().load_cube_map(Game::assetsFolderPath() + "textures/cube_maps/sky/sky-cube-map-.tga"))
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE); // By enabling GL_CULL_FACE, is set to cull back faces by default

		PSPtr < Entity> entityP(new Entity(*this, "Test-Entity"));
		entityP->transform().translate(0.f, 0.f, 10.f);
		//entityP->add_model(Game::assetsFolderPath() + "models/fbx/Tank.fbx");
		entityP->add_model(Game::assetsFolderPath() + "models/obj/m4mw3.obj");
		renderer_.subscribe_entity(entityP);

		renderer_.update();

		on_window_resized();
	}

	void Scene::update(float deltaTime)
	{
		activeCamera_.update(deltaTime);

		for (auto& pair : entities_)
		{
			pair.second->update(deltaTime);
		}

		renderer_.update();
	}

	void Scene::render(float deltaTime)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1.0);

		//skybox.render(activeCamera_);

		renderer_.render(activeCamera_);
	}

	void Scene::on_window_resized()
	{
		Vector2u windowSize = window_.getSize();

		activeCamera_.set_ratio(float(windowSize.x) / windowSize.y);

		glViewport(0, 0, windowSize.x, windowSize.y);
	}

	bool Scene::add_entity(PSPtr<Entity> entity, bool subscribeToRenderer)
	{
		if (!exists_entity(entity))
		{
			entities_[entity->name()] = entity;

			if (subscribeToRenderer && !renderer_.is_entity_subscribed(entity))
			{
				renderer_.subscribe_entity(entity);
			}

			return true;
		}

		return false;
	}

	bool Scene::exists_entity(PSPtr<Entity> entity) const
	{
		if (entity)
		{
			return exists_entity(entity->name());
		}

		return false;
	}
}
