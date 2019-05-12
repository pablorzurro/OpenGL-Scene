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

#include "Declarations.hpp"
#include "Utilities.hpp"

namespace prz
{
	class Renderer;
	class Entity;

	class Transform
	{

	public:

		Transform() = delete;
		Transform(Entity& owner);
		Transform(Entity& owner, Transform& other);

	public:

		void translate(PVec3 translation);
		void translate(float translationX, float translationY, float translationZ);

	public:

		void translate_in_x(float translationX);
		void translate_in_y(float translationY);
		void translate_in_z(float translationZ);

	public:

		void rotate(PVec3 rotation);
		void rotate(float angleX, float angleY, float angleZ);

	public:

		void rotate_around_x(float angle);
		void rotate_around_y(float angle);
		void rotate_around_z(float angle);

	public:

		void scale(PVec3 scale);
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

		void set_position(PVec3 newPosition);
		void set_rotation(PVec3 newRotation);
		void set_scale(PVec3 newScale);

	public:

		void set_visible(bool visibility);
		
	public:

		PMat4 localMatrix();
		PMat4 get_inverse_localMatrix();
		
		PMat4 globalMatrix();
		PMat4 get_inverse_global_matrix();

	public:

		Transform* parent();
		Entity& owner();

	public:

		Renderer* renderer();

	public:

		PVec3 position();
		PQuat rotation();
		PVec3 scale(); 

	public:

		bool isVisible();

	protected:

		PMat4 localMatrix_;
		PMat4 globalMatrix_;

	protected:

		Transform* parent_;
		Entity& owner_;

	protected:

		Renderer* renderer_;

	protected:

		PVec3 position_;
		PQuat rotation_;
		PVec3 scale_;

	protected:

		bool isVisible_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TRANSFORM_H_
