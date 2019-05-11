/**
 * @file Declarations_OpenGL.h
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DECLARATIONS_OPENGL_H_
#define OPENGL_SCENE_DECLARATIONS_OPENGL_H_

#include "OpenGL.hpp"

namespace prz
{

	enum Primitive_Mode
	{
		POINTS = GL_POINTS,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP,
		LINES = GL_LINES,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY = GL_LINES_ADJACENCY,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		NO_PRIMITIVE_MODE = GL_NONE
	};

	enum Indices_Type
	{
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		NO_INDICES_TYPE = GL_NONE
	};

	struct Var
	{
		enum class Type
		{
			BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, FLOAT, VECTOR2, VECTOR3, VECTOR4
		};

		union Data
		{
			GLint   intGL;
			GLuint  uintGL;
			GLfloat floatGL;
			GLfloat fVector2GL[2];
			GLfloat fVector3GL[3];
			GLfloat fVector4GL[4];
		};

		Type type;
		Data data;

	};

	struct Uniform
	{
		GLint index;
		Var   value;
	};

} // !namespace prz

#endif // !OPENGL_SCENE_DECLARATIONS_OPENGL_H_
