#include "View.hpp"

#include "Declarations.hpp"

#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace prz;
using namespace sf;

int main()
{
	Window window(VideoMode(800, 600), "OpenGL Examples: Skybox", Style::Default, ContextSettings(32));

	if (!gladLoadGL()) {
		printf("Something went wrong!\n");
		exit(-1);
	}
	printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	prz::View view(800, 600);

	window.setVerticalSyncEnabled(true);

	bool running = true;

	do
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				running = false;
				break;
			}

			case Event::Resized:
			{
				Vector2u window_size = window.getSize();

				view.resize(window_size.x, window_size.y);

				break;
			}

			case Event::KeyPressed:
			{
				view.on_key(event.key.code);
				break;
			}

			case Event::MouseButtonPressed:
			{
				view.on_click(event.mouseButton.x, event.mouseButton.y, true);
				break;
			}

			case Event::MouseButtonReleased:
			{
				view.on_click(event.mouseButton.x, event.mouseButton.y, false);
				break;
			}

			case Event::MouseMoved:
			{
				view.on_drag(event.mouseMove.x, event.mouseMove.y);
				break;
			}
			}
		}

		view.update();
		view.render();

		window.display();
	} while (running);

	return (EXIT_SUCCESS);
}