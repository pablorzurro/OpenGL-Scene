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
			SPtr< VBO > vbo;
			GLuint attribute_location;
			GLint  number_of_components;
			GLenum component_type;
		};

	public:

		Vertex_Array_Object
		(
			const std::initializer_list< Vertex_Attribute_Information >& vertex_attribute_information_list,
			const SPtr< VBO >& indices_vbo = SPtr< VBO >()
		);

		~Vertex_Array_Object()
		{
			glDeleteVertexArrays(1, &vao_id);
		}

	public:

		void bind() const
		{
			glBindVertexArray(vao_id);
		}

		void unbind() const
		{
			glBindVertexArray(0);
		}

	public: 

		bool is_ok() const
		{
			return error == GL_NO_ERROR;
		}

	private:

		Vertex_Array_Object(const VAO&);

	private:

		GLuint   vao_id;
		PList< SPtr< VBO > > vbo_list;
		GLenum   error;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_VERTEX_ARRAY_OBJECT_H_
