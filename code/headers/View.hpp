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

#include "internal/Declarations.hpp"

#include <glad/glad.h>

namespace prz
{
	class Camera;
	class Skybox;

	class View
	{
	private:

		Camera camera;
		Skybox skybox;

		int    width;
		int    height;

		float  angle_around_x;
		float  angle_around_y;
		float  angle_delta_x;
		float  angle_delta_y;

		bool   pointer_pressed;
		int    last_pointer_x;
		int    last_pointer_y;

	public:

		View(int width, int height);

		void update();
		void render();
		void resize(int width, int height);
		void on_key(int key_code);
		void on_drag(int pointer_x, int pointer_y);
		void on_click(int pointer_x, int pointer_y, bool down);

	};

} // !namespace prz

#endif // !OPENGL_SCENE_VIEW_H_
