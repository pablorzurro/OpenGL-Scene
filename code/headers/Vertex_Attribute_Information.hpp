/**
 * @file Vertex_Attribute_Information.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to store vertex attributes 
 * @version 0.1
 * @date 16-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_VERTEX_ATTRIBUTE_INFORMATION_H_
#define OPENGL_SCENE_VERTEX_ATTRIBUTE_INFORMATION_H_

#include <Vertex_Buffer_Object.hpp>

#include <Declarations.hpp>

namespace prz
{
	/**
	 * @brief Class to store vertex attributes 
	 * 
	 */
	struct Vertex_Attribute_Information
	{
		/**
		 * @brief Construct a new Vertex_Attribute_Information
		 * 
		 * @param iVBO 
		 * @param iIndex 
		 */
		Vertex_Attribute_Information(PSPtr< PVBO > iVBO, GLuint iIndex)
		{
			if (iVBO.get())
			{
				vbo = iVBO;
				index = iIndex;
				nComponents = vbo->nComponentsPerElement();
				componentType = vbo->elementType();
			}
			else
			{
				index = 4294967295;
				nComponents = 4294967295;
				componentType = GL_INVALID_VALUE;
			}
		}

		PSPtr< PVBO > vbo;
		GLuint index;
		GLuint nComponents;
		GLenum componentType;
	};

} // !namespace prz

#endif // !OPENGL_SCENE_VERTEX_ATTRIBUTE_INFORMATION_H_
