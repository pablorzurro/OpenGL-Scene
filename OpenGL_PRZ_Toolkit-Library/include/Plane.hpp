/**
 * @file Plane.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Plane mesh
 * @version 0.1
 * @date 08-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_PLANE_MESH_H_
#define OPENGL_SCENE_PLANE_MESH_H_

#include <Mesh.hpp>

#include <Declarations.hpp>

namespace prz
{

	/**
	 * @brief Mesh that represents a quad with 2 triangles
	 * 
	 */
	class Plane : public Mesh
	{

	public:

		/**
		 * @brief Construct a new Plane
		 * 
		 * @param name 
		 */
		Plane(const PString& name = "undefined");

	private:

		static const PBuffer< GLfloat > coordinates_;
		static const PBuffer< GLfloat > normals_;
		static const PBuffer< GLfloat > textureUVs_;
		static const PBuffer< GLuint > indices_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_PLANE_MESH_H_
