/**
 * @file VertexArrayObject.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 29-04-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_VERTEX_ARRAY_OBJECT_H_
#define OPENGL_SCENE_VERTEX_ARRAY_OBJECT_H_

#include "Shader_Program.hpp"
#include "Vertex_Buffer_Object.hpp"

#include "Declarations.hpp"

#include <SFML/OpenGL.hpp>
#include <cassert>

namespace prz
{
	
	class Vertex_Array_Object
	{
	public:

		struct Vertex_Attribute_Information
		{
			PSPtr< PVBO > vbo;
			GLuint attribLocation;
			GLint  nComponents;
			GLenum componentType;
		};

		using PVAI = Vertex_Attribute_Information;

	public:

		Vertex_Array_Object
		(
			const std::initializer_list< PVAI >& vertexAttribInfoList,
			const PSPtr< PVBO >& vboIndices = PSPtr< PVBO >()
		);

		~Vertex_Array_Object()
		{
			glDeleteVertexArrays(1, &id_);
		}

	public:

		void bind() const
		{
			glBindVertexArray(id_);
		}

		void unbind() const
		{
			glBindVertexArray(0);
		}

	public: 

		bool is_ok() const
		{
			return error_ == GL_NO_ERROR;
		}

	public:

		GLenum get_error() const
		{
			return error_;
		}

	private:

		Vertex_Array_Object(const PVAO&);

	private:

		GLuint id_;
		PList< PSPtr< PVBO > > vboList_;
		GLenum error_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_VERTEX_ARRAY_OBJECT_H_
