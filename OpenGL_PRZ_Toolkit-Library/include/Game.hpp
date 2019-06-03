/**
 * @file Game.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Core class to manage the logic of the application
 * @version 0.1
 * @date 09-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_GAME_H_
#define OPENGL_SCENE_GAME_H_

#include <Scene.hpp>

#include <Utilities.hpp>

#include <Declarations.hpp>
#include <SFML/Window.hpp>

#include <cassert>

using namespace sf;

namespace prz
{

	class Input_Manager;

	/**
	 * @brief Core class to manage the logic of the application
	 * 
	 */
	class Game
	{
	public:

		/**
		 * @brief Construct a new Game
		 * 
		 * @param windowWidth 
		 * @param windowHeight 
		 * @param windowTitle 
		 * @param vSync 
		 * @param windowStyle 
		 * @param depth 
		 */
		Game
		(
			unsigned int windowWidth,
			unsigned int windowHeight,
			const PString& windowTitle = "PRZuro OpenGL Scene",
			bool vSync = true,
			const WindowStyle& windowStyle = DEFAULT,
			unsigned int depth = 32
		);

		/**
		 * @brief Destroy the Game
		 * 
		 */
		~Game()
		{}

	public:

		/**
		 * @brief Run the game
		 * 
		 */
		void run();
		
		/**
		 * @brief Stop the game
		 * 
		 */
		void stop()
		{
			isRunning_ = false;
		}

	public:

		/**
		 * @brief Return the running state
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isRunning()
		{
			return isRunning_;
		}

	public:

		/**
		 * @brief Return the assets folder path
		 * 
		 * @return const PString& 
		 */
		static const PString& assetsFolderPath()
		{
			return assetsFolderPath_;
		}

	private:

		/**
		 * @brief Check SFML events
		 * 
		 * @param inputManager 
		 */
		void poll_events(Input_Manager& inputManager);
		
		/**
		 * @brief Calculate the time between frames 
		 * 
		 */
		void calculate_delta_time() 
		{
			curTime = HighClock::now();

			deltaTime_ = static_cast<float>(Elapsed(curTime - prevTime).count());

			prevTime = curTime;
		}

	public:

		void set_scene(PSPtr< Scene > scene)
		{
			scene_ = scene;
		}

	public:

		Window& window()
		{
			return window_;
		}

	private:

		Window window_;
		PSPtr<Scene> scene_;

	private:

		Event event_;
		
	private:

		float deltaTime_;
		PTimePoint curTime;
		PTimePoint prevTime;

	private:

		bool isRunning_;

	private:

		static PString assetsFolderPath_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_GAME_H_
