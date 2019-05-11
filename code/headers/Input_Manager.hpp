/**
 * @file Input_Manager.hpp
 * @author Pablo Rodr�guez Zurro (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 08-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_INPUT_MANAGER_H_
#define OPENGL_SCENE_INPUT_MANAGER_H_

#include "Declarations.hpp"

#include <SFML/System.hpp>

using namespace sf;

namespace prz
{

	class Input_Manager
	{
	public:

		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return InputManager&
		 */
		static Input_Manager& instance()
		{
			static Input_Manager instance;
			return instance;
		}

	public:

		/**
		 * @brief Update the keyboard state with the input event
		 *
		 * @param event
		 */
		void update(Event& event)
		{
			switch (event.type)
			{
			case Event::KeyPressed:

				keysPressed_[event.key.code] = true;

				break;

			case Event::KeyReleased:

				keysPressed_[event.key.code] = false;

				break;

			case Event::MouseButtonPressed:

				isMousePressed_ = true;

				break;

			case Event::MouseButtonReleased:

				isMousePressed_ = false;
				break;

			case Event::MouseMoved:

				last_pointer_x = curMouseX;
				last_pointer_y = curMouseY;

				curMouseX = event.mouseMove.x;
				curMouseY = event.mouseMove.y;

				break;
			}
		}

	public:

		/**
		 * @brief Get the state of a key
		 *
		 * @param key
		 * @return true
		 * @return false
		 */
		bool is_key_pressed(const PKey& key) const
		{
			return keysPressed_.count(key) == 1 && keysPressed_.at(key) == true;
		}

		bool is_mouse_pressed()
		{
			return isMousePressed_;
		}

	private:

		/**
		 * @brief Construct a new Input Manager object, private to avoid undesired instantiation
		 *
		 */
		Input_Manager():
			isMousePressed_(false)
		{
			curMouseX = last_pointer_x = curMouseY = last_pointer_y = 0;
		}

	private:

		PMap< PKey, bool > keysPressed_;

		unsigned int  curMouseX, last_pointer_x;
		unsigned int  curMouseY, last_pointer_y;

	private: 

		bool isMousePressed_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_INPUT_MANAGER_H_
