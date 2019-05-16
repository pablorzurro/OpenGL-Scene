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

#include <Shader_Program.hpp>

#include <Declarations.hpp>

#include <cassert>

namespace prz
{
	
	class Vertex_Array_Object
	{
	public:

		Vertex_Array_Object
		(
			const PList< PVAI >& vertexAttribInfoList,
			const PSPtr< PVBO >& vboIndices = PSPtr< PVBO >()
		);

		~Vertex_Array_Object()
		{
			glDeleteVertexArrays(1, &vaoID_);
		}

	public:

		void bind() const
		{
			glBindVertexArray(vaoID_);
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

		GLuint vaoID()
		{
			return vaoID_;
		}

	private:

		Vertex_Array_Object(const Vertex_Array_Object&);

	private:

		GLuint vaoID_;
		PList< PSPtr< PVBO > > vbos_;
		GLenum error_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_VERTEX_ARRAY_OBJECT_H_
