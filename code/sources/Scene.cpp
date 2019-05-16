#include <Scene.hpp>
#include <Entity.hpp>
#include <Transform.hpp>
#include <Texture_Loader.hpp>
#include <Model_Loader.hpp>
#include <Skybox.hpp>
#include <Game.hpp>

namespace prz
{

	Scene::Scene(Window& window)
		:
		window_(window),
		activeCamera_(*this),
		skybox(Texture_Loader::instance().load_cube_map(Game::assetsFolderPath() + "textures/cube_maps/sky/sky-cube-map-.tga"))
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE); // By enabling GL_CULL_FACE, is set to cull back faces by default
	
		
		Model_Loader::instance().load_model(Game::assetsFolderPath() + "models/fbx/Tank.fbx");
		Model_Loader::instance().load_model(Game::assetsFolderPath() + "models/obj/m4mw3.obj");

		on_window_resized();
	}

	void Scene::update(float deltaTime)
	{
		for (auto& pair : entities_)
		{
			pair.second->update(deltaTime);
		}
	}

	void Scene::render(float deltaTime)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1.0);

		//skybox.render(activeCamera_);
	}

	void Scene::on_window_resized()
	{
		Vector2u windowSize = window_.getSize();

		activeCamera_.set_ratio(float(windowSize.x) / windowSize.y);

		glViewport(0, 0, windowSize.x, windowSize.y);
	}
}
