/**
 * @file Plane.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 08-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_PLANE_MESH_H_
#define OPENGL_SCENE_PLANE_MESH_H_

#include <Mesh.hpp>

namespace prz
{

	class Plane : public Mesh
	{
	public:

		enum VBO_ORDER
		{
			COORDINATES,
			NORMALS,
			TEXTURE_UVS,
			INDICES,
			SIZE
		};

	public:

		Plane()
			: Mesh(Primitive_Mode::TRIANGLES, 12, UNSIGNED_BYTE)
		{
			//set_vao()
		}

	private:

		static const GLfloat coordinates_[];
		static const GLfloat normals_[];
		static const GLfloat textureUVs_[];
		static const GLubyte indices_[];
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_PLANE_MESH_H_
