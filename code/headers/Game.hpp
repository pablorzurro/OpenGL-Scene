/**
 * @file Game.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 09-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_GAME_H_
#define OPENGL_SCENE_GAME_H_

#include "Declarations.hpp"

#include <glad/glad.h>
#include <SFML/System.hpp>

using namespace sf;

namespace prz
{
	class Scene;
	class Input_Manager;

	class Game
	{
	public:

		Game(unsigned int windowWidth, unsigned int windowHeight, const PString& windowTitle = "PRZuro OpenGL Scene", const WindowStyle& windowStyle = DEFAULT, unsigned int depth = 32):
			window_(VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, ContextSettings(depth)),
			scene_(window_),
			event_(),
			deltaTime_(0.f),
			isRunning_(false)
		{
			curTime = prevTime = HighClock::now();
		}

		~Game()
		{}

	public:

		void run();
		
		void stop()
		{
			isRunning_ = false;
		}

	public:

		bool isRunning()
		{
			return isRunning_;
		}

	private:

		void poll_events(Input_Manager& inputManager);
		
		void calculate_delta_time() 
		{
			curTime = HighClock::now();
			deltaTime_ = Elapsed(curTime - prevTime).count();
			prevTime = curTime;
		}

	private:

		Window window_;
		Scene scene_;

	private:

		Event event_;

	private:

		float deltaTime_;
		PTimePoint curTime;
		PTimePoint prevTime;

	private:

		bool isRunning_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_GAME_H_
