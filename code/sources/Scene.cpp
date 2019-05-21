#include <Scene.hpp>
#include <Entity.hpp>
#include <Transform.hpp>
#include <Texture_Loader.hpp>
#include <Skybox.hpp>
#include <Game.hpp>
#include <Model.hpp>
#include <Cube.hpp>

#include <Shader_Program_Loader.hpp>

namespace prz
{

	Scene::Scene(Window& window) :
		window_(window),
		renderer_(*this),
		activeCamera_(make_shared< Camera >( *this, "Active_Camera_For_Testing")),
		skybox_(make_shared< Skybox >(Game::assetsFolderPath() + "textures/cube_maps/sky/sky-cube-map-.tga", Game::assetsFolderPath() + "shaders/skybox.vert", Game::assetsFolderPath() + "shaders/skybox.frag"))
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE); // By enabling GL_CULL_FACE, is set to cull back faces by default

		/*add_entity(make_shared< Entity >(*this, "Test-Entity"));*/

		/*PSPtr< Entity > entityP =  create_entity("test_entity");
		entityP->add_model(Game::assetsFolderPath() + "models/fbx/Tank.fbx");
		entityP->transform().translate_in_z(-10.f);*/

		PSPtr< Entity > entityXX = create_entity("test_entityhhhh");
		entityXX->add_model(Game::assetsFolderPath() + "models/obj/head.obj");
		entityXX->transform().scale(0.2f, 0.2f, 0.2f);
		entityXX->transform().translate_in_z(-1.f);

		PSPtr< Entity > entity5 = create_entity("test_entity2222");
		PSPtr< Model >model(std::make_shared<Model >(1, "Model with a cube"));
		model->add_piece(std::make_shared< Cube >("cube_mesh"));
		entity5->add_model(model);
		entity5->transform().scale(5.f, 5.f, 5.f);
		entity5->transform().translate_in_z(-20.f);

		PSPtr< Entity > entity2 = create_entity("test_entity2");
		entity2->add_model(Game::assetsFolderPath() + "models/obj/m4mw3.obj");
		entity2->transform().translate_in_z(-4.f);
		entity2->transform().translate_in_x(100.f);

		//PSPtr< Entity > entity3 = create_entity("test_entity3");
		//entity3->add_model(Game::assetsFolderPath() + "models/fbx/Tank.fbx");
		//entity3->transform().translate_in_y(100.f);

		on_window_resized();
	}

	void Scene::update(float deltaTime)
	{
		activeCamera_->update(deltaTime);

		PSPtr < Entity > entity = get_entity("test_entity2");
		entity->transform().rotate(0.f, 50.f * deltaTime, 0.f);

		PSPtr < Entity > entity1 = get_entity("test_entityhhhh");
		entity1->transform().rotate(0.f, 50.f * deltaTime, 50.f * deltaTime);

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

		renderer_.render(activeCamera_);
		skybox_->draw(activeCamera_);
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
