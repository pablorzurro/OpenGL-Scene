/**
 * @file View.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_VIEW_H_
#define OPENGL_SCENE_VIEW_H_

#include <Renderer.hpp>
#include <Camera.hpp>
#include <Skybox.hpp>

#include <Declarations.hpp>

#include <SFML/Window.hpp>

using namespace sf;

namespace prz
{

	class Scene
	{
	public:

		Scene(Window& window);

	public:

		void update(float deltaTime);
		void render(float deltaTime);

	public:

		void display()
		{
			window_.display();
		}

	public:

		void on_window_resized();

	private:

		Renderer renderer;
		Camera activeCamera_;
		
	private:

		PMap< PString, PSPtr< Entity >> entities_;

	private:

		Skybox skybox;

	private:

		Window& window_;
	};

} // !namespace prz

#endif // !OPENGL_SCENE_VIEW_H_
