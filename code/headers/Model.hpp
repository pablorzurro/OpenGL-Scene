/**
 * @file Model.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to store and manage meshes and materials
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
#include <Material_Loader.hpp>

#include <Declarations.hpp>

namespace prz
{
	class Entity;

	/**
	 * @brief Class to store and manage meshes and materials
	 * 
	 */
	class Model
	{
	public:

		/**
		 * @brief Combination of a mesh and a material
		 * 
		 */
		struct Piece
		{
			PSPtr< Mesh > mesh;
			PSPtr< Material> material;
		};

		using Meshes_By_Material = PMap < PSPtr< Material >, PList < PSPtr< Mesh > > >;

	public:

		/**
		 * @brief Construct a new Model
		 * 
		 * @param owner 
		 * @param numPieces 
		 * @param name 
		 */
		Model(Entity* owner = nullptr, unsigned int numPieces = 100, const PString& name = "undefined") :
			owner_(owner),
			numPieces_(numPieces),
			name_(name)
		{}

		/**
		 * @brief Construct a new Model
		 * 
		 * @param numPieces 
		 * @param name 
		 */
		Model(unsigned int numPieces = 100, const PString& name = "undefined") :
			Model(nullptr, numPieces, name)
		{}

		/**
		 * @brief Destroy the Model
		 * 
		 */
		~Model()
		{}

	public:

		/**
		 * @brief Initialize this model. Only can initialize if the previously specified number of vertices is the same as the current number. 
		 * 
		 * @param owner 
		 */
		void initialize(Entity* owner = nullptr)
		{
			if (owner_ != owner && owner && !owner_)
			{
				owner_ = owner;
			}
		}

	public:

		/**
		 * @brief Add a piece by:
		 * 
		 * @param mesh 
		 * @param material 
		 * @return true 
		 * @return false 
		 */
		bool add_piece(PSPtr< Mesh > mesh, PSPtr< Material > material = Material_Loader::instance().get_default_material())
		{
			if (!exists_mesh(mesh))
			{
				pieces_[mesh->name()] = { mesh, material };
				meshesByMaterial_[material].push_back(mesh);
				return true;
			}

			return false;
		}

	public:

		/**
		 * @brief Set the material to a mesh
		 * 
		 * @param mesh 
		 * @param material 
		 * @return true 
		 * @return false 
		 */
		bool set_material_to_mesh(PSPtr< Mesh> mesh, PSPtr< Material > material)
		{
			return set_material_to_mesh(mesh->name(), material);
		}

		/**
		 * @brief Set the material to a mesh
		 * 
		 * @param meshName 
		 * @param material 
		 * @return true 
		 * @return false 
		 */
		bool set_material_to_mesh(const PString& meshName, PSPtr< Material > material)
		{
			if (exists_mesh_with_name(meshName) && material)
			{
				Piece& piece = pieces_[meshName];

				assert(piece.material && piece.mesh && exists_material(piece.material)); // if the material and mesh are nullptr or the material doesn't exist in this object there is a problem

				if (piece.material != material)
				{
					// Delete the mesh from the list of the material
					meshesByMaterial_[piece.material].remove(piece.mesh);

					// Check if the list is empty now
					if (meshesByMaterial_[piece.material].size() == 0)
					{
						// And if is empty delete the entry of the map
						meshesByMaterial_.erase(material);
					}
				}

				piece.material = material;
				meshesByMaterial_[material].push_back(piece.mesh);

				return true;
			}

			return false;
		}

		/**
		 * @brief Set a material to all the pieces
		 * 
		 * @param material 
		 */
		void set_material_to_all_pieces(PSPtr< Material > material)
		{
			for (auto& pair : pieces_)
			{
				Piece& piece = pair.second;

				piece.material = material;

				set_material_to_mesh(piece.mesh, material);
			}
		}

		/**
		 * @brief Set the name
		 * 
		 * @param name 
		 */
		void set_name(const PString& name)
		{
			name_ = name;
		}

	public:

		/**
		 * @brief Return if exists a mesh with the input name
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool exists_mesh_with_name(const PString& name)
		{
			return pieces_.find(name) != pieces_.end();
		}

		/**
		 * @brief Return if exists the input mesh
		 * 
		 * @param mesh 
		 * @return true 
		 * @return false 
		 */
		bool exists_mesh(PSPtr< Mesh > mesh)
		{
			return exists_mesh_with_name(mesh->name());
		}

		/**
		 * @brief Return if exists the input material 
		 * 
		 * @param material 
		 * @return true 
		 * @return false 
		 */
		bool exists_material(PSPtr< Material > material)
		{
			return meshesByMaterial_.find(material) != meshesByMaterial_.end();
		}

	public:

		/**
		 * @brief Return if the model is ok
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_ok()
		{
			return numPieces_ == pieces_.size() && owner_;
		}

	public:

		/**
		 * @brief Return the name
		 * 
		 * @return const PString& 
		 */
		const PString& name() const { return name_; }

	public:

		/**
		 * @brief Get the pieces map
		 * 
		 * @return PMap< PString, Piece >& 
		 */
		PMap< PString, Piece >& pieces() { return pieces_; }

		/**
		 * @brief Return the meshes by material map
		 * 
		 * @return Meshes_By_Material& 
		 */
		Meshes_By_Material& meshesByMaterial() { return meshesByMaterial_; }

	private:

		PMap< PString, Piece > pieces_;
		Meshes_By_Material  meshesByMaterial_;

	private:

		Entity* owner_;

	private:

		unsigned int numPieces_;

	private:

		PString name_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_MODEL_H_
