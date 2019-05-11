#pragma warning(disable: 4251)                  // https://github.com/cginternals/glbinding/issues/141

#include <glad/glad.h>

namespace prz
{

    bool initialize_opengl_extensions ()
    {
		return gladLoadGL () != 0;
    }

}
