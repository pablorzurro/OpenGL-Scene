#include <Scene.hpp>
#include <Entity.hpp>
#include <Transform.hpp>
#include <Texture_Loader.hpp>
#include <Skybox.hpp>
#include <Game.hpp>
#include <Model.hpp>
#include <Cube.hpp>
#include <Camera.hpp>

namespace prz
{

	Scene::Scene(Window& window) :
		window_(window),
		renderer_(*this)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE); // By enabling GL_CULL_FACE, is set to cull back faces by default
	}

	Scene::Scene(Window& window, PSPtr<Camera> activeCamera, PSPtr<Skybox> skybox) : 
		Scene(window)	
	{ 
		activeCamera_ = activeCamera;
		skybox_ = skybox;

		on_window_resized();
	}

	void Scene::update(float deltaTime)
	{
		activeCamera_->update(deltaTime);

		for (auto& pair : entities_)
		{
			pair.second->update(deltaTime);
		}

		renderer_.update();
	}

	void Scene::render(float deltaTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1.0);

		skybox_->draw(activeCamera_);
		renderer_.render(activeCamera_);
	}

	void Scene::on_window_resized()
	{
		Vector2u windowSize = window_.getSize();

		activeCamera_->set_ratio(float(windowSize.x) / windowSize.y);

		glViewport(0, 0, windowSize.x, windowSize.y);
	}

	PSPtr< Entity > Scene::add_entity(PSPtr< Entity > entity, PSPtr< Entity > parent, bool subscribeToRenderer)
	{
		if (!exists_entity(entity))
		{
			entities_[entity->name()] = entity;

			if (subscribeToRenderer && !renderer_.is_entity_subscribed(entity))
			{
				renderer_.subscribe_entity(entity);
			}

			if (!entity->transform().parent() && exists_entity(parent))
			{
				entity->set_parent(parent);
			}
			
			return entity;
		}

		return PSPtr<Entity>();
	}

	PSPtr< Entity > Scene::create_entity(const PString& name, PSPtr<Entity> parent)
	{
		return add_entity(make_shared< Entity >(*this, name, parent));
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
