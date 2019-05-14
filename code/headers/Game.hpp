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

#include "Scene.hpp"

#include "Utilities.hpp"
#include "Source_Code.hpp"

#include "Declarations.hpp"
#include <SFML/Window.hpp>

#include <cassert>

using namespace sf;

namespace prz
{

	class Input_Manager;

	class Game
	{
	public:

		Game(unsigned int windowWidth, unsigned int windowHeight, const PString& windowTitle = "PRZuro OpenGL Scene", bool vSync = true, const WindowStyle& windowStyle = DEFAULT, unsigned int depth = 32):
			window_(VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, ContextSettings(24, 0,0, 4, 5, ContextSettings::Core)),
			event_(),
			deltaTime_(0.f),
			isRunning_(false)
		{
			cout << "Introduce assets folder relative path: ";
			cin >> assetsFolderPath_;
			cout << endl;
			assetsFolderPath_ += "/";

			cout << assetsFolderPath_ << endl;

			window_.setVerticalSyncEnabled(vSync);

			if (!initialize_opengl_extensions())
			{
				exit(-1);
			}

			scene_.reset(new Scene(window_));
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

	public:

		static const PString& assetsFolderPath()
		{
			return assetsFolderPath_;
		}

	private:

		void poll_events(Input_Manager& inputManager);
		
		void calculate_delta_time() 
		{
			curTime = HighClock::now();

			deltaTime_ = static_cast<float>(Elapsed(curTime - prevTime).count());
			prevTime = curTime;
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
