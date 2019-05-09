/**
 * @file Declarations.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 01-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DECLARATIONS_H_
#define OPENGL_SCENE_DECLARATIONS_H_

#include "SFML/Graphics.hpp"

#include <glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <gtc/type_ptr.hpp>                 // value_ptr

#include <chrono>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#include <iostream>

namespace prz
{
	class Vertex_Buffer_Object;
	class Vertex_Array_Object;

	using PVBO = Vertex_Buffer_Object;
	using PVAO = Vertex_Array_Object;

	////////////////////////////////////STANDARD LIBRARY/////////////////////////////////////

	template<typename T>
	using PSPtr = std::shared_ptr<T>; // Shared pointer

	template<typename Key, typename Val>
	using PMap = std::unordered_map<Key, Val>;

	template<typename T>
	using PBuffer = std::vector<T>; // Same as vector but renamed

	template<typename T> 
	using PList = std::list<T>;

	using PString = std::string;

	typedef std::chrono::high_resolution_clock HighClock;
	typedef std::chrono::time_point<HighClock> HighTimePoint;
	typedef std::chrono::duration<double> Elapsed;

	using PHighClock = std::chrono::high_resolution_clock;
	using PTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using PElapsedTime =std::chrono::duration<double>;

	////////////////////////////////////SFML/////////////////////////////////////

	using PKey = sf::Keyboard::Key;

	enum WindowStyle : sf::Uint32
	{
		NONE = sf::Style::None,
		TITLEBAR = sf::Style::Titlebar,
		RESIZE = sf::Style::Resize,
		CLOSE = sf::Style::Close,
		FULLSCREEN = sf::Style::Fullscreen,
		DEFAULT = sf::Style::Fullscreen
	};

	////////////////////////////////////GLM/////////////////////////////////////

	using PVec2 = glm::vec2;
	using PVec3 = glm::vec3;
	using PVec4 = glm::vec4;

	using PUVec2 = glm::uvec2;
	using PUVec3 = glm::uvec3;
	using PUVec4 = glm::uvec4;

	using PPoint4 = glm::vec4;

	using PMat4 = glm::mat4;

	////////////////////////////////////MATH/////////////////////////////////////

	constexpr float PI			= 3.14159f;
	constexpr float DELTA_TIME	= 0.01667f;          // ~60 fps
	
	constexpr float DEG_TO_RAD	= 0.01745f;
	constexpr float RAD_TO_DEG	= 57.29578f;
} // !namespace prz

#endif // !OPENGL_SCENE_DECLARATIONS_H_
