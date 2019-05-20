#ifndef OPENGL_SCENE_INTERNAL_UTILITIES_H_
#define OPENGL_SCENE_INTERNAL_UTILITIES_H_

#include <Declarations.hpp>

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

	static PString split_string_by_separator(const PString& str, const char * separator)
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

	///////////////////////////////////GLM///////////////////////////////////////

	inline PVec3 extract_translation(PMat4 & matrix)
	{
		return PVec3(matrix[3].x, matrix[3].y, matrix[3].z);
	}

	inline PVec3 extract_rotation_vector(PMat4& matrix)
	{
		return PVec3(matrix[0].x, matrix[1].y, matrix[2].z);
	}

	inline PQuat extract_rotation(PMat4& matrix)
	{
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(matrix, scale, rotation, translation, skew, perspective);

		return rotation;
	}

	inline PMat4 perspective(float fov, float near, float far, float aspect_ratio)
	{
		return glm::perspective(fov, aspect_ratio, near, far);
	}

	inline PVec3 extract_scale(PMat4& matrix)
	{
		return PVec3(matrix[0].x, matrix[1].y, matrix[2].z);
	}

	inline PMat4 rotate_matrix_around_axis(PMat4& matrix, float angle, const PVec3& axis)
	{
		PMat4 returnMatrix = glm::rotate(matrix, glm::radians(angle), axis);
		return returnMatrix;
	}

	inline PQuat get_quaternion_from(const PVec3& vector3f, bool inRadians = false, bool normalize = true)
	{
		PVec3 v = vector3f;
		PQuat pitch = PQuatIdentity;
		PQuat yaw = PQuatIdentity;
		PQuat roll = PQuatIdentity;

		bool isModuleZero = (v.x + v.y + v.z) == 0.f;

		if (!isModuleZero)
		{
			if (!inRadians)
			{
				v = glm::radians(v);
			}

			if (normalize)
			{
				v = glm::normalize(v);
			}

			/*	if()*/
			pitch = glm::angleAxis(v.x, PVec3(1.f, 0.f, 0.f));
			yaw = glm::angleAxis(v.y, PVec3(0.f, 1.f, 0.f));
			roll = glm::angleAxis(v.z, PVec3(0.f, 0.f, 1.f));
		}

		return pitch * yaw* roll;
	}
}

#endif // !OPENGL_SCENE_INTERNAL_UTILITIES_H_
