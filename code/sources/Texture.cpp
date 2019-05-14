#include "Texture.hpp"

namespace prz
{
	void Texture::initialize()
	{
		if (is_ok()) // Check if the images have been loaded succesfully 
		{
			/*glEnable(textureType_);*/

			glGenTextures(1, &textureID_);
			glActiveTexture(GL_TEXTURE0);

			bind();
			{
				apply_wrap_mode();
				apply_filter_mode();
				on_initialize(); // Never call a pure virtual function in constructor, it calls the base method instead of the children's

			} unbind();

			error_ = glGetError();

			assert(is_ok()); //Check if has been an error loading the texture in OpenGL
		}
	}
}
