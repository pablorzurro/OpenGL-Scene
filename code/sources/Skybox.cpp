#include "Skybox.hpp"
#include "Texture_Cube.hpp"
#include "Texture_Loader.hpp"

namespace prz
{
	Skybox::Skybox(const PString& textureRootPath, const PString& textureName) :
		Skybox(Texture_Loader::instance().load_cube_map(textureRootPath, textureName))
	{}

	Skybox::Skybox(PSPtr< Texture > cubeMap):
		Skybox(Texture_Loader::instance().get_texture_cube(cubeMap->name()))
	{}
}