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
		skybox_(Texture_Loader::instance().load_cube_map(Game::assetsFolderPath() + "textures/cube_maps/sky/sky-cube-map-.tga"))
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE); // By enabling GL_CULL_FACE, is set to cull back faces by default

		/*add_entity(make_shared< Entity >(*this, "Test-Entity"));*/

		//PSPtr< Entity > entityP =  create_entity("test_entity");
		//entityP->transform().set_translation(PVec3(0.f, 2.f, 2.f));
		////entityP->add_model(Game::assetsFolderPath() + "models/fbx/Tank.fbx");

		PSPtr< Entity > entity5 = create_entity("test_entity2222");
		PSPtr< Model >model(std::make_shared<Model >(1, "Model with a cube"));
		model->add_piece(std::make_shared< Cube >("cube_mesh"));
		entity5->add_model(model);
		//entity5->transform().scale(5.f, 5.f, 5.f);

		PSPtr< Entity > entity2 = create_entity("test_entity2");
		entity2->add_model(Game::assetsFolderPath() + "models/obj/m4mw3.obj");
		entity2->transform().translate_in_z(-100.f);
		entity2->transform().rotate_around_y(10.f);
		entity2->transform().rotate_around_z(-20.f);

		/*	PSPtr< Entity > entity3 = create_entity("test_entity3");
			entity3->add_model(Game::assetsFolderPath() + "models/fbx/Tank.fbx");
			entity3->transform().translate_in_y(100.f);
	*/
		on_window_resized();
	}

	void Scene::update(float deltaTime)
	{
		PSPtr < Entity > entity = get_entity("test_entity2");
		/*entity->transform().rotate(0.f, 0.f, 0.0000005f * deltaTime);*/
		activeCamera_->update(deltaTime);

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
		skybox_.draw(activeCamera_);
	}

	void Scene::on_window_resized()
	{
		Vector2u windowSize = window_.getSize();

		activeCamera_->set_ratio(float(windowSize.x) / windowSize.y);

		glViewport(0, 0, windowSize.x, windowSize.y);
	}

	PSPtr< Entity >  Scene::add_entity(PSPtr< Entity > entity, PSPtr< Entity > parent, bool subscribeToRenderer)
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
			else
			{
				entity->set_parent(activeCamera_);
			}

			return entity;
		}

		return PSPtr<Entity>();
	}

	PSPtr< Entity > Scene::create_entity(const PString& name, PSPtr<Entity> parent, bool modelIsViewMatrix)
	{
		return add_entity(make_shared< Entity >(*this, name, parent, modelIsViewMatrix));
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
