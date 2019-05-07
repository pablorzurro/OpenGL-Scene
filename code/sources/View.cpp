#include "View.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"

#include <SFML/OpenGL.hpp>

namespace prz
{

	View::View(int width, int height)
		:
		skybox("../../assets/sky-cube-map-")
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		resize(width, height);

		angle_around_x = angle_delta_x = 0.0;
		angle_around_y = angle_delta_y = 0.0;
		pointer_pressed = false;
	}

	void View::update()
	{
		angle_around_x += angle_delta_x;
		angle_around_y += angle_delta_y;

		if (angle_around_x < -1.5)
		{
			angle_around_x = -1.5;
		}
		else
			if (angle_around_x > +1.5)
			{
				angle_around_x = +1.5;
			}

		glm::mat4 camera_rotation;

		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_y), glm::vec3(0.f, 1.f, 0.f));
		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_x), glm::vec3(1.f, 0.f, 0.f));

		camera.set_target(0, 0, -1);
		camera.rotate(camera_rotation);
	}

	void View::render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		skybox.render(camera);
	}

	void View::resize(int new_width, int new_height)
	{
		width = new_width;
		height = new_height;

		camera.set_ratio(float(width) / height);

		glViewport(0, 0, width, height);
	}

	void View::on_key(int key_code)
	{
	}

	void View::on_drag(int pointer_x, int pointer_y)
	{
		if (pointer_pressed)
		{
			angle_delta_x = 0.025f * float(last_pointer_y - pointer_y) / float(height);
			angle_delta_y = 0.025f * float(last_pointer_x - pointer_x) / float(width);
		}
	}

	void View::on_click(int pointer_x, int pointer_y, bool down)
	{
		if ((pointer_pressed = down) == true)
		{
			last_pointer_x = pointer_x;
			last_pointer_y = pointer_y;
		}
		else
		{
			angle_delta_x = angle_delta_y = 0.0;
		}
	}

}
