/**
 * @file Declarations_GLM.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DECLARATIONS_GLM_H_
#define OPENGL_SCENE_DECLARATIONS_GLM_H_

#include <glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <gtc/type_ptr.hpp>                 // value_ptr
#include <gtx/matrix_decompose.hpp>
#include <gtx/string_cast.hpp>
#include <gtx/quaternion.hpp>

namespace prz
{
	using PVec2 = glm::vec2;
	using PVec3 = glm::vec3;
	using PVec4 = glm::vec4;

	using PUVec2 = glm::uvec2;
	using PUVec3 = glm::uvec3;
	using PUVec4 = glm::uvec4;

	using PPoint4 = glm::vec4;

	using PMat2 = glm::mat2;
	using PMat3 = glm::mat3;
	using PMat4 = glm::mat4;

	using PQuat = glm::quat;

	static const PMat4 PMatIdentity = PMat4(1.f); //PMat4 deprecated, is an all zeros matrix
	static const PQuat PQuatIdentity = glm::quat_identity<float, glm::qualifier::highp>();

} // !namespace prz

#endif // !OPENGL_SCENE_DECLARATIONS_GLM_H_
