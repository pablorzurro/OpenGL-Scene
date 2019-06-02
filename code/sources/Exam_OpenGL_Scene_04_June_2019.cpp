#include <Exam_OpenGL_Scene_04_June_2019.hpp>

#include <Game.hpp>
#include <Model.hpp>
#include <Entity.hpp>
#include <Cube.hpp>
#include <Skybox.hpp>
#include <Camera.hpp>
#include <Material_Loader.hpp>

#include <Cube.hpp>
#include <Plane.hpp>
#include <Projected_Plane.hpp>

namespace prz
{
	Exam_OpenGL_Scene_04_June_2019::Exam_OpenGL_Scene_04_June_2019(Window& window) :
		Scene
		(
			window,
			make_shared< Camera >(*this, "Active_Camera_For_Testing"),
			PSPtr< Framebuffer > (),
			make_shared< Skybox >(Game::assetsFolderPath() + "textures/cube_maps/lake/goldrush_.tga", Game::assetsFolderPath() + "shaders/skybox.vert", Game::assetsFolderPath() + "shaders/skybox.frag")
		)
	{}
	void Exam_OpenGL_Scene_04_June_2019::initialize()
	{
	}
	void Exam_OpenGL_Scene_04_June_2019::update(float deltaTime)
	{
		Scene::update(deltaTime);
	}
}