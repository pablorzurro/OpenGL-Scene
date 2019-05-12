#include "Transform.hpp"

namespace prz
{
	Transform::Transform(Entity& owner) :
		owner_(owner),
		localMatrix_(PMatIdentity),
		position_(extract_translation(localMatrix_)),
		rotation_(extract_rotation(localMatrix_)),
		scale_(extract_scale(localMatrix_))
	{}

	Transform::Transform(Entity& owner, Transform& other):
		owner_(owner),
		localMatrix_(other.localMatrix_),
		position_(other.position_),
		rotation_(other.rotation_),
		scale_(other.scale_)
	{}

	void Transform::translate(PVec3 translation)
	{
		localMatrix_ = glm::translate(localMatrix_, translation);
		position_ = extract_translation(localMatrix_);
	}

	void Transform::translate(float translationX, float translationY, float translationZ)
	{
		translate(PVec3(translationX, translationY, translationZ));
	}

	void Transform::translate_in_x(float translationX)
	{
		translate(PVec3(translationX, 0, 0));
	}

	void Transform::translate_in_y(float translationY)
	{
		translate(PVec3(0, translationY, 0));
	}

	void Transform::translate_in_z(float translationZ)
	{
		translate(PVec3(0, 0, translationZ));
	}

	void Transform::rotate(PVec3 rotation)
	{
		localMatrix_ = rotate_matrix_around_axis(localMatrix_, rotation.x, PVec3(1, 0, 0));
		localMatrix_ = rotate_matrix_around_axis(localMatrix_, rotation.y, PVec3(0, 1, 0));
		localMatrix_ = rotate_matrix_around_axis(localMatrix_, rotation.z, PVec3(0, 0, 1));
		
		rotation_ = extract_rotation(localMatrix_);
	}

	void Transform::rotate(float angleX, float angleY, float angleZ)
	{
		rotate(PVec3(angleX, angleY, angleZ));
	}

	void Transform::rotate_around_x(float angle)
	{
		rotate(PVec3(angle, 0, 0));
	}
	void Transform::rotate_around_y(float angle)
	{
		rotate(PVec3(0, angle, 0));
	}

	void Transform::rotate_around_z(float angle)
	{
		rotate(PVec3(0, 0, angle));
	}

	void Transform::scale(PVec3 scale)
	{
		localMatrix_ = glm::scale(localMatrix_, scale_);
		scale_ = extract_scale(localMatrix_);
	}

	void Transform::scale(float scaleX, float scaleY, float scaleZ)
	{
		scale(PVec3(scaleX, scaleY, scaleZ));
	}

	void Transform::scale_x(float scaleX)
	{
		scale(PVec3(scaleX, 0, 0));
	}

	void Transform::scale_y(float scaleY)
	{
		scale(PVec3(0, scaleY, 0));
	}

	void Transform::scale_z(float scaleZ)
	{
		scale(PVec3(0, 0, scaleZ));
	}

	void Transform::set_parent(Transform* parent) 
	{
		parent_ = parent;
	}

	void Transform::set_renderer(Renderer* renderer)
	{
		assert(renderer == nullptr);
		renderer_ = renderer;
	}

	void Transform::set_position(PVec3 newPosition)
	{
		translate(newPosition - position_);
	}

	void Transform::set_rotation(PVec3 newRotation)
	{
		rotate(newRotation - extract_rotation_vector(localMatrix_));
	}

	void Transform::set_scale(PVec3 newScale)
	{
		scale(newScale - scale_);
	}

	void Transform::set_visible(bool visibility)
	{
		isVisible_ = visibility;
	}

	PMat4 Transform::localMatrix()
	{
		return localMatrix_;
	}

	PMat4 Transform::get_inverse_localMatrix()
	{
		return inverse(localMatrix_);
	}

	PMat4 Transform::globalMatrix()
	{
		globalMatrix_ = localMatrix_;

		if (parent_)
		{
			globalMatrix_ = parent_->localMatrix_ * globalMatrix_;
		}

		return globalMatrix_;
	}

	PMat4 Transform::get_inverse_global_matrix()
	{
		return inverse(globalMatrix());
	}

	Transform* Transform::parent()
	{
		return parent_;
	}

	Entity& Transform::owner()
	{
		return owner_;
	}

	Renderer* Transform::renderer()
	{
		return renderer_;
	}

	PVec3 Transform::position()
	{
		return position_;
	}

	PQuat Transform::rotation()
	{
		return rotation_;
	}

	PVec3 Transform::scale()
	{
		return scale_;
	}

	bool Transform::isVisible()
	{
		return isVisible_;
	}
}
