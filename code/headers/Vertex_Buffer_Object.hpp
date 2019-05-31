/**
 * @file VertexBufferObject.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to manage a memory buffer of vertices 
 * @version 0.1
 * @date 29-04-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_VERTEX_BUFFER_OBJECT_H_
#define OPENGL_SCENE_VERTEX_BUFFER_OBJECT_H_

#include <Declarations.hpp>

#include <cassert>

namespace prz
{
	
	/**
	 * @brief Class to manage a memory buffer of vertices 
	 * 
	 */
	class Vertex_Buffer_Object
	{
	public:

		enum Target
		{
			ARRAY_BUFFER = GL_ARRAY_BUFFER,
			ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER
		};

		enum DrawUsage // Draw usage sentence for OpenGL optimization
		{
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW,
			STREAM = GL_STREAM_DRAW
		};

	public:

		// Public overrided constructors for each input data type: byte, unsigned byte, short, unsigned short, int, unsigned int, unsigned int vectors (2,3 and 4), float and float vectors(2,3 and 4)
		
		Vertex_Buffer_Object(const GLbyte	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_BYTE, drawUsage, nComponents) {}
		Vertex_Buffer_Object(const GLubyte	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_UNSIGNED_BYTE, drawUsage, nComponents) {}
		Vertex_Buffer_Object(const GLshort	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_SHORT, drawUsage, nComponents) {}
		Vertex_Buffer_Object(const GLushort	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_UNSIGNED_SHORT, drawUsage, nComponents) {}
		Vertex_Buffer_Object(const GLint	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_INT, drawUsage, nComponents) {}
		Vertex_Buffer_Object(const GLuint	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_UNSIGNED_INT, drawUsage, nComponents) {}
		Vertex_Buffer_Object(const GLfloat	* data, size_t size, unsigned int nComponents = 1, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC): Vertex_Buffer_Object(data, size, target, GL_FLOAT, drawUsage, nComponents) {}
		
		Vertex_Buffer_Object(const PVec2* data, size_t size, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC) : Vertex_Buffer_Object(data, size, target, GL_FLOAT, drawUsage, 2) {}
		Vertex_Buffer_Object(const PVec3* data, size_t size, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC) : Vertex_Buffer_Object(data, size, target, GL_FLOAT, drawUsage, 3) {}
		Vertex_Buffer_Object(const PVec4* data, size_t size, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC) : Vertex_Buffer_Object(data, size, target, GL_FLOAT, drawUsage, 4) {}
		Vertex_Buffer_Object(const PUVec2* data, size_t size, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC) : Vertex_Buffer_Object(data, size, target, GL_UNSIGNED_INT, drawUsage, 2) {}
		Vertex_Buffer_Object(const PUVec3* data, size_t size, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC) : Vertex_Buffer_Object(data, size, target, GL_UNSIGNED_INT, drawUsage, 3) {}
		Vertex_Buffer_Object(const PUVec4* data, size_t size, Target target = ARRAY_BUFFER, DrawUsage drawUsage = STATIC) : Vertex_Buffer_Object(data, size, target, GL_UNSIGNED_INT, drawUsage, 4) {}

		/**
		 * @brief Destroy the Vertex_Buffer_Object
		 * 
		 */
		~Vertex_Buffer_Object()
		{
			glDeleteBuffers(1, &vboID_);
		}

	public:

		/**
		 * @brief Create a VBO with void date (used by all constructors)
		 * 
		 * @param data 
		 * @param size 
		 */
		void create(const void* data, size_t size);

	public:

		/**
		 * @brief Bind the vbo
		 * 
		 */
		void bind()
		{
			glBindBuffer(target_, vboID_);
		}

		/**
		 * @brief Unbind the vbo
		 * 
		 */
		void unbind()
		{
			glBindBuffer(target_, 0);
		}

	public:

		/**
		 * @brief Return if is ok
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_ok() const { return error_ == GL_NO_ERROR; }

	public:

		/**
		 * @brief Return the VBO identification
		 * 
		 * @return GLuint 
		 */
		GLuint vboID() const { return vboID_; }

		/**
		 * @brief Return the target
		 * 
		 * @return GLenum 
		 */
		GLenum target() const { return target_; }

		/**
		 * @brief Return the element type
		 * 
		 * @return GLenum 
		 */
		GLenum elementType() const { return elementType_; }

		/**
		 * @brief Return the components per element
		 * 
		 * @return unsigned int 
		 */
		unsigned int nComponentsPerElement() { return nComponentsPerElement_; }

		/**
		 * @brief Return the size 
		 * 
		 * @return unsigned int 
		 */
		unsigned int size() { return size_; }

	public:

		/**
		 * @brief Return the error
		 * 
		 * @return GLenum 
		 */
		GLenum get_error() const { return error_; }

	private: 

		/**
		 * @brief Core and private constructor that receives the parameters of the different public constructor overloads and create the buffer object
		 * 
		 * @param data 
		 * @param size 
		 * @param target 
		 * @param elementType 
		 * @param drawUsage 
		 */
		Vertex_Buffer_Object(const void* data, size_t size, Target target, GLenum elementType, DrawUsage drawUsage, unsigned int nComponents = 1) :
			vboID_(8000),
			target_(GLenum(target)),
			elementType_(GLenum(elementType)),
			drawUsage_(GLenum(drawUsage)),
			nComponentsPerElement_(nComponents),
			error_(GL_NO_ERROR),
			size_((unsigned int)size)
		{
			create(data, size);
		}

	private:

		GLuint vboID_;
		GLenum target_;
		GLenum elementType_;
		GLenum drawUsage_;

	private:

		unsigned int nComponentsPerElement_;
		unsigned int size_;

	private:

		GLenum error_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_VERTEX_BUFFER_OBJECT_H_
