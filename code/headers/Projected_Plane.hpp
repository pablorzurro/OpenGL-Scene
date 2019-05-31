/**
 * @file Projected_Plane.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 31-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_PROJECTED_PLANE
#define OPENGL_SCENE_PROJECTED_PLANE

#include <Mesh.hpp>

#include <Declarations.hpp>

namespace prz
{

	class Projected_Plane : public Mesh
	{
	public:

		Projected_Plane(const PString& name);

	private:

		static const PBuffer< GLfloat > coordinates_;
		static const PBuffer< GLfloat > normals_;
		static const PBuffer< GLfloat > textureUVs_;
		static const PBuffer< GLuint > indices_;

	};

} // !namespace prz

#endif // !OPENGL_SCENE_PROJECTED_PLANE
