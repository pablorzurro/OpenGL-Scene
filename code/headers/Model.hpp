/**
 * @file Model.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_MODEL_H_
#define OPENGL_SCENE_MODEL_H_

#include "Mesh.hpp"
#include "Material.hpp"

#include "Declarations.hpp"

namespace prz
{
	
	class Model
	{
	public:

		struct Piece
		{
			Mesh mesh_;
			Material material_;
		};

	public:

		Model()
		{}

		~Model()
		{}

	private:

		PBuffer< Piece > pieces_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_MODEL_H_
