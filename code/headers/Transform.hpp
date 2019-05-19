/**
 * @file Transform.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 09-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_TRANSFORM_H_
#define OPENGL_SCENE_TRANSFORM_H_

#include <Declarations.hpp>
#include <Utilities.hpp>

namespace prz
{
	class Renderer;
	class Entity;

	class Transform
	{
	public:

		Transform() = delete;
		Transform(Entity& owner, Transform* parent = nullptr, bool isWorldMatrixInversed_ = false, bool updateModelMatrixAlways = false);
		Transform(Entity& owner, Transform& other);

	public:

		void translate(const PVec3& translation);
		void translate(float pitch, float yaw, float roll);

	public:

		void translate_in_x(float translationX);
		void translate_in_y(float translationY);
		void translate_in_z(float translationZ);

	public:

		void rotate(const PQuat& rotation);
		void rotate(const PVec3& rotation, bool inRadians = false);
		void rotate(float eulerAngleX, float eulerAngleY, float eulerAngleZ, bool inRadians = false);

	public:

		void rotate_around_x(float eulerAngle, bool inRadians = false);
		void rotate_around_y(float eulerAngle, bool inRadians = false);
		void rotate_around_z(float eulerAngle, bool inRadians = false);

	public:

		void scale(const PVec3& scale);
		void scale(float scaleX, float scaleY, float scaleZ);

	public:

		void scale_x(float scaleX);
		void scale_y(float scaleY);
		void scale_z(float scaleZ);

	public:

		void set_parent(Transform* parent);

	public:

		void set_renderer(Renderer* renderer);

	public:

		void set_translation(const PVec3& newTranslation);
		void set_orientation(const PQuat& newOrientation);
		void set_orientation(const PVec3& newOrientation, bool inRadians = false);
		void set_scale(const PVec3& newScale);

	public:

		void set_visible(bool visibility);
		
	public:

		PMat4 modelMatrix();
		PMat4 inverse_modelMatrix();
		
		PMat4 worldMatrix();
		PMat4 inverse_worldMatrix();

		PMat4 viewMatrix();

	public:

		Transform* parent();
		Entity& owner();

	public:

		Renderer* renderer();

	public:

		const PVec3& translation() const;
		PMat4 translation_matrix() const;

		const PQuat& orientation() const;
		PVec3 euler_rotation(bool inDegrees = true) const;
		PMat4 rotation_matrix() const;

		const PVec3& scale() const; 
		PMat4 scale_matrix()const;

	public:

		bool isVisible();

	protected:

		void update_model_matrix(bool necessaryUpdate = false);
		void update_world_matrix();

	protected:

		PMat4 modelMatrix_;
		PMat4 worldMatrix_;

	protected:

		Transform* parent_;
		Entity& owner_;

	protected:

		Renderer* renderer_;

	protected:

		PVec3 translation_;
		PQuat orientation_;
		PVec3 scale_;

	protected:

		bool isVisible_;

	protected:

		bool isModelMatrixUpdated_;
		bool isWorldMatrixUpdated_;
		bool isWorldMatrixInversed_;
		bool updateModelMatrixAlways_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TRANSFORM_H_
