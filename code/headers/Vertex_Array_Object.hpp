/**
 * @file VertexArrayObject.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to manage and store vertex array information
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
	
	/**
	 * @brief Class to manage and store vertex array information
	 * 
	 */
	class Vertex_Array_Object
	{
	public:

		/**
		 * @brief Construct a new Vertex_Array_Object
		 * 
		 * @param vertexAttribInfoList 
		 * @param vboIndices 
		 */
		Vertex_Array_Object
		(
			const PList< PVAI >& vertexAttribInfoList,
			const PSPtr< PVBO >& vboIndices = PSPtr< PVBO >()
		);

		/**
		 * @brief Destroy the Vertex_Array_Object
		 * 
		 */
		~Vertex_Array_Object()
		{
			glDeleteVertexArrays(1, &vaoID_);
		}

	public:

		/**
		 * @brief Bind the VAO
		 * 
		 */
		void bind() const
		{
			glBindVertexArray(vaoID_);
		}

		/**
		 * @brief Unbind the VAO
		 * 
		 */
		void unbind() const
		{
			glBindVertexArray(0);
		}

	public: 

		/**
		 * @brief Return if is ok
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_ok() const
		{
			return error_ == GL_NO_ERROR;
		}

	public:

		/**
		 * @brief Return the error
		 * 
		 * @return GLenum 
		 */
		GLenum get_error() const
		{
			return error_;
		}

		/**
		 * @brief Return the VAO identification
		 * 
		 * @return GLuint 
		 */
		GLuint vaoID()
		{
			return vaoID_;
		}

		// Returns the number of indices
		GLuint nIndices()
		{
			return nIndices_;
		}

	private:

		/**
		 * @brief Construct a new Vertex_Array_Object (private)
		 * 
		 */
		Vertex_Array_Object(const Vertex_Array_Object&);

	private:

		GLuint vaoID_;
		PList< PSPtr< PVBO > > vbos_;

	private:

		GLuint nIndices_;
		
	private:
		GLenum error_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_VERTEX_ARRAY_OBJECT_H_
