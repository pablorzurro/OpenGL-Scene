#ifndef OPENGL_SCENE_INTERNAL_UTILITIES_H_
#define OPENGL_SCENE_INTERNAL_UTILITIES_H_

#include "Declarations.hpp"

#include <time.h>
#include <random>

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
			srand((unsigned int)time(NULL));
		}

		return min + T(rand()) / T(RAND_MAX) * (max - min);
	}

	static float degrees_to_radians(float degrees)
	{
		return degrees * DEG_TO_RAD;
	}

	static float radians_to_degrees(float radians)
	{
		return radians * RAD_TO_DEG;
	}

	static PString split_file_name(const PString& str, const char * separator)
	{
		return str.substr(str.find_last_of(separator) + 1);
	}

	static PString load_file_as_string(const PString& filePath)
	{
		PString str;

		// Open the file

		fstream fileReader(filePath, fstream::in | fstream::binary);

		if (fileReader.is_open())
		{
			// Get the file size

			fileReader.seekg(0, fstream::end);

			size_t fileSize = size_t(fileReader.tellg());

			if (fileReader.good() && fileSize > 0)
			{
				// Read the content of the file and save it in a string
				// Se espera que el archivo contenga un byte por cada carácter con código menor que 128 (UTF-8, etc.).

				str.resize(fileSize);

				fileReader.seekg(0, fstream::beg);

				fileReader.read(&str.front(), fileSize);

				assert(fileReader.good());
			}
		}
		else
			assert(false);

		return str;
	}
}

#endif // !OPENGL_SCENE_INTERNAL_UTILITIES_H_
