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

#include <Mesh.hpp>
#include <Material.hpp>

#include <Declarations.hpp>

namespace prz
{
	class Entity;

	class Model
	{
	public:

		struct Piece
		{
			PSPtr< Mesh > mesh;
			PSPtr< Material > material;
		};

	public: 

		Model(Entity* owner = nullptr, unsigned int numPieces = 100):
			owner_(owner),
			numPieces_(numPieces)
		{}

		Model(unsigned int numPieces = 100):
			Model(nullptr, numPieces)
		{}

		~Model()
		{}

	public:

		void initialize(Entity* owner = nullptr)
		{
			if (owner_ != owner && owner && !owner_)
			{
				owner_ = owner;
			}
		}

	public:

		void add_piece(PSPtr< Mesh > mesh, PSPtr< Material > material = Material::default_material())
		{
			pieces_.push_back({ mesh, material });
		}

	public:

		void set_material_to(PSPtr< Material > material, unsigned int pieceIndex)
		{
			pieces_[pieceIndex].material = material;
		}

		void set_material_to_all_pieces(PSPtr< Material > material)
		{
			for (unsigned int i = 0; i < pieces_.size(); i++)
			{
				set_material_to(material, i);
			}	
		}

	public:

		bool is_ok()
		{
			return numPieces_ == pieces_.size() && owner_;
		}

	public:

		PBuffer< Piece >& pieces(){ return pieces_; }

	private:

		PBuffer< Piece > pieces_;

	private:

		Entity* owner_;

	private:

		unsigned int numPieces_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_MODEL_H_
