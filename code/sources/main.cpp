#include <Game.hpp>
#include <Demo_Scene_01.hpp>

using namespace prz;

int main()
{

	Game game(1280, 720);

	game.set_scene(make_shared<Demo_Scene_01>(game.window()));

	game.run();

	return (EXIT_SUCCESS);
}	