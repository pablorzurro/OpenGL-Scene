/**
 * @file Mesh.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to store and manage vertex array objects
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_MESH_H_
#define OPENGL_SCENE_MESH_H_

#include <Drawable.hpp>
#include <Vertex_Array_Object.hpp>
#include <Vertex_Buffer_Object.hpp>

#include <Declarations.hpp>
#include <Utilities.hpp>

namespace prz
{

	/**
	 * @brief Class to store and manage vertex array objects
	 * 
	 */
	class Mesh : Drawable
	{
	public:

		enum VBO_ORDER : GLuint
		{
			COORDINATES,
			NORMALS,
			TEXTURE_COORD,
			COLORS,
			INDICES,
			SIZE
		};

	public:

		/**
		 * @brief Construct a new Mesh
		 * 
		 */
		Mesh();

		/**
		 * @brief Construct a new Mesh
		 * 
		 * @param name 
		 * @param primitiveMode 
		 */
		Mesh
		(
			const PString& name,
			Primitive_Mode primitiveMode
		);

		/**
		 * @brief Construct a new Mesh
		 * 
		 * @param name 
		 * @param nVertices 
		 * @param primitiveMode 
		 * @param indicesType 
		 */
		Mesh
		(
			const PString& name,
			GLsizei nVertices,
			Primitive_Mode primitiveMode = TRIANGLES,
			Indices_Type indicesType = UNSIGNED_INT
		);

		/**
		 * @brief Construct a new Mesh
		 * 
		 * @param name 
		 * @param coordinates 
		 * @param normals 
		 * @param indices 
		 * @param primitiveMode 
		 * @param textureUVs 
		 * @param colors 
		 */
		Mesh
		(
			const PString& name,
			const PBuffer< GLfloat >& coordinates,
			const PBuffer< GLfloat >& normals,
			const PBuffer< GLuint  >& indices,
			Primitive_Mode primitiveMode = TRIANGLES,
			const PBuffer< GLfloat > & textureUVs = PBuffer< GLfloat >(),
			const PBuffer< GLfloat > & colors = PBuffer< GLfloat >()
		);

		/**
		 * @brief Destroy the Mesh
		 * 
		 */
		~Mesh()
		{}

	public: 

		/**
		 * @brief draw the mesh
		 * 
		 */
		virtual void draw() override;

	public:

		/**
		 * @brief Set the primitive mode
		 * 
		 * @param primitiveMode 
		 */
		void set_primitive_mode(Primitive_Mode primitiveMode)
		{
			primitiveMode_ = primitiveMode;
		}

		/**
		 * @brief Set the indices type
		 * 
		 * @param indicesType 
		 */
		void set_indices_type(Indices_Type indicesType)
		{
			indicesType_ = indicesType;
		}

		/**
		 * @brief Set the vertices count
		 * 
		 * @param nVertices 
		 */
		void set_vertices_count(GLsizei nVertices)
		{
			nVertices_ = nVertices;
		}

		/**
		 * @brief Set the Vertex Array Object
		 * 
		 * @param vao 
		 */
		void set_vao(PSPtr< Vertex_Array_Object > vao)
		{
			vao_ = vao;
		}

	public:

		/**
		 * @brief Return the name
		 * 
		 * @return const PString& 
		 */
		const PString& name() const { return name_; }

	protected:

		PSPtr<PVAO> vao_; 

	protected:

		GLenum primitiveMode_;
		GLenum indicesType_;
		GLsizei nVertices_;

	protected:

		PString name_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_MESH_H_
