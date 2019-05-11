/**
 * @file Cube.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_CUBE_MESH_H_
#define OPENGL_SCENE_CUBE_MESH_H_

#include "Mesh.hpp"

namespace prz
{
	
	class Cube : public Mesh
	{
	public:
		

	private:

		enum VBO_ORDER
		{
			COORDINATES,
			NORMALS,
			COLORS,
			INDICES,
			SIZE
		};

	private:

		static const GLfloat coordinates_[];
		static const GLfloat normals_[];
		static const GLfloat textureUVs_[];
		static const GLubyte indices_[];
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_CUBE_MESH_H_
