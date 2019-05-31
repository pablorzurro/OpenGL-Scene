#include <Projected_Plane.hpp>

namespace prz
{
	const PBuffer< GLfloat > Projected_Plane::coordinates_ =
	{
		-1.f, -1.f,	 0.f,		// 0
		-1.f,  1.f,	 0.f,		// 1
		 +1.f, 1.f,	 0.f,		// 2
		 1.f, -1.f,	 0.f,		// 3
	};

	const PBuffer< GLfloat > Projected_Plane::normals_ =
	{
		1.f,  0.f,  0.f,		// 0
		1.f,  0.f,  0.f,		// 1
		1.f,  0.f,  0.f,		// 2
		1.f,  0.f,  0.f,		// 3
	};

	const PBuffer< GLfloat > Projected_Plane::textureUVs_ =
	{
		0.f,  0.f,              // 0
		0.f,  1.f,              // 1
		1.f,  1.f,              // 2
		1.f,  0.f,              // 3
	};

	const PBuffer< GLuint > Projected_Plane::indices_ =
	{
		0,  1 , 2,				// Left
		2,  3 , 0,				// Right
	};

	Projected_Plane::Projected_Plane(const PString& name) : 
		Mesh(name, coordinates_, normals_, indices_, TRIANGLES, textureUVs_)
	{}
}