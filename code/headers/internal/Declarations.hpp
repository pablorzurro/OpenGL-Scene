/**
 * @file Declarations.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Class to define custom names and typedefs of different libraries and include some interesting library headers to avoid repetition.
 * @version 0.1
 * @date 01-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DECLARATIONS_H_
#define OPENGL_SCENE_DECLARATIONS_H_

#include "Declarations_STD.hpp"
#include "Declarations_SFML.hpp"
#include "Declarations_OpenGL.hpp"
#include "Declarations_GLM.hpp"

namespace prz
{
	class Vertex_Buffer_Object;
	class Vertex_Array_Object;

	using PVBO = Vertex_Buffer_Object;
	using PVAO = Vertex_Array_Object;

	////////////////////////////////////MATH/////////////////////////////////////

	constexpr float PI			= 3.14159f;
	constexpr float DELTA_TIME	= 0.01667f;          // ~60 fps
	
	constexpr float DEG_TO_RAD	= 0.01745f;
	constexpr float RAD_TO_DEG	= 57.29578f;
} // !namespace prz

#endif // !OPENGL_SCENE_DECLARATIONS_H_
