/**
 * @file Scene.hpp
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

#include <Declarations.hpp>

#include <SFML/Window.hpp>

using namespace sf;

namespace prz
{

	class Entity;
	class Camera;
	class Skybox;
	class Framebuffer;

	class Scene
	{
	public:

		Scene(Window& window);

		Scene
		(
			Window& window,
			PSPtr< Camera > activeCamera,
			PSPtr< Skybox > skybox

		);

	public:

		virtual void initialize() {}

	public:

		virtual void update(float deltaTime);
		void render(float deltaTime);

	public:

		void display()
		{
			window_.display();
		}

	public:

		void on_window_resized();

	public:

		PSPtr< Entity > add_entity(PSPtr< Entity > entity, PSPtr< Entity > parent = PSPtr < Entity >(), bool subscribeToRenderer = true);
		PSPtr< Entity > create_entity(const PString& name, PSPtr< Entity > parent = PSPtr < Entity >());
		
	public:

		bool exists_entity(PSPtr< Entity > entity) const;
		bool exists_entity(const PString& name) const { return entities_.find(name) != entities_.end(); }

	public:

		PSPtr< Entity > get_entity(const PString& name) { return exists_entity(name) ? entities_[name] : PSPtr< Entity >(); }
		PVec2 get_window_size() { return PVec2(window_.getSize().x, window_.getSize().y); }

	public:

		const Renderer& renderer() const { return renderer_; }
		const PSPtr< Camera > activeCamera() const { return activeCamera_; }

	protected:

		Renderer renderer_;
		PSPtr< Camera > activeCamera_;
		
	protected:

		PMap< PString, PSPtr< Entity >> entities_;

	protected:

		PSPtr< Skybox > skybox_;

	protected:

		Window& window_;
		PSPtr< Framebuffer > framebuffer_;

	protected:

		bool isWireframeModeActive_;
		bool applyFrameBufferEffect_;

	protected:

		float inputTimer_;

	};

} // !namespace prz

#endif // !OPENGL_SCENE_SCENE_H_
