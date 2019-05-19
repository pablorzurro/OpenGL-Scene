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

#ifndef OPENGL_SCENE_SCENE_H_
#define OPENGL_SCENE_SCENE_H_

#include <Renderer.hpp>
#include <Camera.hpp>
#include <Skybox.hpp>

#include <Declarations.hpp>

#include <SFML/Window.hpp>

using namespace sf;

namespace prz
{

	class Entity;

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

	public:

		bool add_entity(PSPtr< Entity > entity, bool subscribeToRenderer = true);
		
	public:

		bool exists_entity(PSPtr< Entity > entity) const;
		bool exists_entity(const PString& name) const { return entities_.find(name) != entities_.end(); }

	public:

		PSPtr< Entity > get_entity(const PString& name) { return exists_entity(name) ? entities_[name] : PSPtr< Entity >(); }

	public:

		const Renderer& renderer() const { return renderer_; }
		const Camera& activeCamera() const { return activeCamera(); }

	private:

		Renderer renderer_;
		Camera activeCamera_;
		
	private:

		PMap< PString, PSPtr< Entity >> entities_;

	private:

		Skybox skybox;

	private:

		Window& window_;
	};

} // !namespace prz

#endif // !OPENGL_SCENE_SCENE_H_
