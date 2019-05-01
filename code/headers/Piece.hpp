/**
 * @file Piece.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_PIECE_H_
#define OPENGL_SCENE_PIECE_H_

#include "Mesh.hpp"
#include "Material.hpp"

namespace prz
{
	struct Piece
	{
	public:

		Piece(/*????*/):
			mesh_(),
			material_()
		{}

	public:

		Mesh& mesh()
		{
			return mesh_;
		}

		Material& material()
		{
			return material_;
		}

	private:
		
		Mesh mesh_;
		Material material_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_PIECE_H_
