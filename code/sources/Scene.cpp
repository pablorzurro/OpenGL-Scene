#include "Scene.hpp"

namespace prz
{

	Scene::Scene(Window& window)
		:
		window_(window),
		skybox("../../assets/sky-cube-map-")
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		on_window_resized();
	}

	void Scene::update(float deltaTime)
	{
		/*glm::mat4 camera_rotation;

		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_y), glm::vec3(0.f, 1.f, 0.f));
		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_x), glm::vec3(1.f, 0.f, 0.f));

		activeCamera_.set_target(0, 0, -1);
		activeCamera_.rotate(camera_rotation);*/
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
