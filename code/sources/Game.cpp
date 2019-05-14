#include "Game.hpp"
#include "Input_Manager.hpp"
#include <glad/glad.h>
namespace prz
{
	void Game::run()
	{
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

	PString Game::assetsFolderPath_ = "";
}
