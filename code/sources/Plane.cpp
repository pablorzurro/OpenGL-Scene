#include <Plane.hpp>

namespace prz
{
	const GLfloat Plane::coordinates_[] =
	{
		-1.f, -1.f,	 0.f,		// 0
		-1.f,  1.f,	 0.f,		// 1
		 1.f,  1.f,	 0.f,		// 2
		 1.f, -1.f,	 0.f,		// 3
	};

	const GLfloat Plane::normals_[] =
	{
		0.f,  1.f,  0.f,		// 0
		0.f,  1.f,  0.f,		// 1
		0.f,  1.f,  0.f,		// 2
		0.f,  1.f,  0.f,		// 3
	};

	const GLfloat Plane::textureUVs_[] =
	{
		0.f,  0.f,              // 0
		0.f,  1.f,              // 1
		1.f,  1.f,              // 2
		1.f,  0.f,              // 3
	};

	const GLubyte Plane::indices_[] =
	{
		0,  1 , 2,				// Left
		2,  3 , 0,				// Right
	};
}
