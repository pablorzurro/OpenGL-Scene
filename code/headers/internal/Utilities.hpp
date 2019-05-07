#ifndef OPENGL_SCENE_INTERNAL_UTILITIES_H_
#define OPENGL_SCENE_INTERNAL_UTILITIES_H_

#include "Declarations.hpp"

#include <time.h>
#include <random>

#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>         // std::size_t

namespace prz
{
	template
	<
		typename T, //real type
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
	>
	static T random(T min, T max, bool seed = false) //range : [min, max)
	{
		static bool first = true;

		if (first || seed)
		{
			srand(time(NULL));
		}

		return min + T(rand()) / T(RAND_MAX) * (max - min);
	}

	static float to_radians(float degrees)
	{
		return degrees * DEG_TO_RAD;
	}

	static float to_degrees(float radians)
	{
		return radians * RAD_TO_DEG;
	}

	static PString split_file_name(const PString& str, const char * separator)
	{
		return str.substr(str.find_last_of(separator) + 1);
	}
}

#endif // !OPENGL_SCENE_INTERNAL_UTILITIES_H_
