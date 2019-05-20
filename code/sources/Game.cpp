#include <Game.hpp>
#include <Input_Manager.hpp>
#include <glad/glad.h>

namespace prz
{
	Game::Game(unsigned int windowWidth, unsigned int windowHeight, const PString& windowTitle, bool vSync, const WindowStyle& windowStyle, unsigned int depth):
		window_(VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, ContextSettings(24, 0, 0, 4, 5, ContextSettings::Core)),
		event_(),
		deltaTime_(0.f),
		isRunning_(false)
	{
		window_.setVerticalSyncEnabled(vSync);

		if (!initialize_opengl_extensions())
		{
			exit(-1);
		}

		//cout << "Introduce assets folder relative path: ";
		//cin >> assetsFolderPath_;
		//cout << endl;
		//assetsFolderPath_ += "/";

		scene_.reset(new Scene(window_));
		curTime = prevTime = HighClock::now();
	}

	void Game::run()
	{
		isRunning_ = true;

		Input_Manager& inputManager = Input_Manager::instance();

		do
		{
			calculate_delta_time();

			poll_events(inputManager);

			scene_->update(deltaTime_);
			scene_->render(deltaTime_);

			scene_->display();

		} while (isRunning_);
	}

	void Game::poll_events(Input_Manager& inputManager)
	{
		while (window_.pollEvent(event_))
		{
			switch (event_.type)
			{
			case Event::Closed:

				stop();

				break;

			case Event::Resized:

				scene_->on_window_resized();

				break;
			}

			inputManager.update(event_); // Send the event to the input manager and update it
		}
	}

	PString Game::assetsFolderPath_ = "../../assets/";
}
