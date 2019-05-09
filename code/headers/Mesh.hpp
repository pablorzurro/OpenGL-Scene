/**
 * @file Mesh.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_MESH_H_
#define OPENGL_SCENE_MESH_H_

#include "Declarations.hpp"

namespace prz
{
	class Mesh
	{
	public:

		Mesh()
		{}

		~Mesh();
		{
		}

	protected:


	private:

		PVBO vbo_;
		PVAO vao_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_MESH_H_
