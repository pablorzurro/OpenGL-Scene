/**
 * @file Declarations_STD.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DECLARATIONS_STD_H_
#define OPENGL_SCENE_DECLARATIONS_STD_H_

#include <chrono>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#include <iostream>
#include <fstream>

#include <cassert>
#include <cstddef>         // std::size_t

using namespace std;

namespace prz
{
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
} // !namespace prz

#endif // !OPENGL_SCENE_DECLARATIONS_STD_H_
