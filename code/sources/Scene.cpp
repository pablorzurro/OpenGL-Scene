#include <Scene.hpp>

#include <Entity.hpp>
#include <Transform.hpp>
#include <Texture_Loader.hpp>
#include <Skybox.hpp>
#include <Game.hpp>
#include <Model.hpp>
#include <Cube.hpp>
#include <Camera.hpp>
#include <Framebuffer.hpp>

namespace prz
{

	Scene::Scene(Window& window) :
		window_(window),
		renderer_(*this),
		isWireframeModeActive_(false),
		applyFrameBufferEffect_(false),
		inputTimer_(0)
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
		// Enable and disable the wireframe view mode 

		inputTimer_ += deltaTime;

		if(inputTimer_ >= 0.125f)
		{
			bool resetTimer = false;

			if (Input_Manager::instance().is_key_pressed(PKey::G))
			{
				isWireframeModeActive_ ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				isWireframeModeActive_ = isWireframeModeActive_ ? false : true;
				inputTimer_ = 0.f;
			}

			if (Input_Manager::instance().is_key_pressed(PKey::F))
			{
				applyFrameBufferEffect_ = applyFrameBufferEffect_ ? false : true;
				inputTimer_ = 0.f;
			}
		}

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

		if (applyFrameBufferEffect_ && framebuffer_)
		{
			framebuffer_->render_first_pass();
		}

		glClearColor(0.5, 0.5, 0.5, 1.0);

		if (skybox_)
		{
			skybox_->draw(activeCamera_);
		}

		renderer_.render(activeCamera_);
		
		if (applyFrameBufferEffect_ && framebuffer_)
		{
			framebuffer_->render_second_pass();
		}
	}

	void Scene::on_window_resized()
	{
		Vector2u windowSize = window_.getSize();

		activeCamera_->set_ratio(float(windowSize.x) / windowSize.y);

		if (framebuffer_)
		{
			framebuffer_->reset(windowSize.x, windowSize.y);
		}

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

			if (parent)
			{
				if (!entity->transform().parent() && exists_entity(parent))
				{
					entity->set_parent(parent);
				}
			}
			//else
			//{
			//	// Implement the system in next versions. Camera transform should return to the hierarchy the view matrix automatically.
			//	entity->set_parent(activeCamera_);
			//}
			
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
