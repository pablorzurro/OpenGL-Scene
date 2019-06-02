/**
 * @file Scene.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Core class to save the state and items of the application
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

	/**
	 * @brief Core class to save the state and items of the application
	 * 
	 */
	class Scene
	{
	public:

		/**
		 * @brief Construct a new Scene
		 * 
		 * @param window 
		 */
		Scene(Window& window);

		/**
		 * @brief Construct a new Scene
		 * 
		 * @param window 
		 * @param activeCamera 
		 * @param framebuffer 
		 * @param skybox 
		 */
		Scene
		(
			Window& window,
			PSPtr< Camera > activeCamera,
			PSPtr< Framebuffer > framebuffer,
			PSPtr< Skybox > skybox
		);

	public:

		/**
		 * @brief Initialize the scene
		 * 
		 */
		virtual void initialize() {}

	public:

		/**
		 * @brief Update the scnee
		 * 
		 * @param deltaTime 
		 */
		virtual void update(float deltaTime);

		/**
		 * @brief Render the scene
		 * 
		 * @param deltaTime 
		 */
		void render(float deltaTime);


		/**
		 * @brief Auxiliar method to render the scene (before the draw of the framebuffer)
		 *
		 * @param deltaTime
		 */
		virtual void custom_render(float deltaTime){}

	public:

		/**
		 * @brief Swap the buffers of the window
		 * 
		 */
		void display()
		{
			window_.display();
		}

	public:

		/**
		 * @brief Method called when the window is resized externaly
		 * 
		 */
		void on_window_resized();

	public:

		/**
		 * @brief Add a entity to the scene
		 * 
		 * @param entity 
		 * @param parent 
		 * @param subscribeToRenderer 
		 * @return PSPtr< Entity > 
		 */
		PSPtr< Entity > add_entity(PSPtr< Entity > entity, PSPtr< Entity > parent = PSPtr < Entity >(), bool subscribeToRenderer = true);

		/**
		 * @brief Create a base entity to fill it with whatever is wanted
		 * 
		 * @param name 
		 * @param parent 
		 * @return PSPtr< Entity > 
		 */
		PSPtr< Entity > create_entity(const PString& name, PSPtr< Entity > parent = PSPtr < Entity >());
		
	public:

		/**
		 * @brief Return if exists a entity
		 * 
		 * @param entity 
		 * @return true 
		 * @return false 
		 */
		bool exists_entity(PSPtr< Entity > entity) const;

		/**
		 * @brief Return if exists a entity by name
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool exists_entity(const PString& name) const { return entities_.find(name) != entities_.end(); }

	public:

		/**
		 * @brief Return the entity by name
		 * 
		 * @param name 
		 * @return PSPtr< Entity > 
		 */
		PSPtr< Entity > get_entity(const PString& name) { return exists_entity(name) ? entities_[name] : PSPtr< Entity >(); }

		/**
		 * @brief Return the window size
		 * 
		 * @return PVec2 
		 */
		PVec2 get_window_size() { return PVec2(window_.getSize().x, window_.getSize().y); }

	public:

		/**
		 * @brief Return the renderer
		 * 
		 * @return const Renderer& 
		 */
		const Renderer& renderer() const { return renderer_; }

		/**
		 * @brief Return the active camera
		 * 
		 * @return const PSPtr< Camera > 
		 */
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
		bool applyFramebufferEffect_
			
			;

	protected:

		float inputTimer_;

	};

} // !namespace prz

#endif // !OPENGL_SCENE_SCENE_H_
