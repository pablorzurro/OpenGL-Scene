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

#include <Drawable.hpp>
#include <Vertex_Array_Object.hpp>
#include <Vertex_Buffer_Object.hpp>

#include <Declarations.hpp>

namespace prz
{

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

		Mesh();
		Mesh(Primitive_Mode primitiveMode, const PString& name = "undefined");
		Mesh(Primitive_Mode primitiveMode, GLsizei nVertices, Indices_Type indicesType = NO_INDICES_TYPE, const PString& name = "undefined");

		~Mesh()
		{
		}

	public: 

		virtual void draw() override;

	public:

		void set_primitive_mode(Primitive_Mode primitiveMode)
		{
			primitiveMode_ = primitiveMode;
		}

		void set_indices_type(Indices_Type indicesType)
		{
			indicesType_ = indicesType;
		}

		void set_vertices_count(GLsizei nVertices)
		{
			nVertices_ = nVertices;
		}

		void set_vao(PSPtr< Vertex_Array_Object > vao)
		{
			vao_ = vao;
		}

	public:

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
