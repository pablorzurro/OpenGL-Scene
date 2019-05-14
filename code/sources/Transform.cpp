#include <Transform.hpp>
#include <gtx/quaternion.hpp>

namespace prz
{
	Transform::Transform(Entity& owner) :
		owner_(owner),
		localMatrix_(PMatIdentity), 
		globalMatrix_(PMatIdentity),
		isVisible_(true),
		parent_(nullptr),
		renderer_(nullptr),
		translation_(extract_translation(localMatrix_)),
		rotation_(extract_rotation(localMatrix_)),
		scale_(extract_scale(localMatrix_))
	{}

	Transform::Transform(Entity& owner, Transform& other):
		owner_(owner),
		localMatrix_(other.localMatrix_),
		globalMatrix_(other.globalMatrix_),
		isVisible_(other.isVisible_),
		parent_(other.parent_),
		renderer_(other.renderer_),
		translation_(other.translation_),
		rotation_(other.rotation_),
		scale_(other.scale_)
	{}

	void Transform::update_local_matrix()
	{
		localMatrix_ = translation_matrix() * rotation_matrix() * scale_matrix();

		isGlobalMatUpdated = false;
	}

	void Transform::translate(PVec3 translation)
	{
		localMatrix_ = glm::translate(localMatrix_, translation);
		translation_ = extract_translation(localMatrix_);
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

	void Transform::rotate(PQuat rotation)
	{
		rotation_ += rotation;
		update_local_matrix();
	}

	void Transform::rotate(PVec3 rotation)
	{
		rotate(PQuat(rotation));
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
		scale_ += scale;
		update_local_matrix();
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

	void Transform::set_translation(PVec3 newTranslation)
	{
		translation_ = newTranslation;
		update_local_matrix();
	}

	void Transform::set_rotation(PQuat newRotation)
	{
		rotation_ = newRotation;
		update_local_matrix();
	}

	void Transform::set_rotation(PVec3 newRotation)
	{
		set_rotation(PQuat(newRotation));
	}

	void Transform::set_scale(PVec3 newScale)
	{
		scale_ = newScale;
		update_local_matrix();
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
		if (!isGlobalMatUpdated)
		{
			globalMatrix_ = localMatrix_;

			if (parent_)
			{
				globalMatrix_ = parent_->globalMatrix_ * globalMatrix_;
			}

			isGlobalMatUpdated = true;
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

	const PVec3& Transform::translation() const
	{
		return translation_;
	}

	PMat4 Transform::translation_matrix() const
	{
		return glm::translate(PMatIdentity, translation_);
	}

	const PQuat& Transform::rotation() const
	{
		return rotation_;
	}

	PMat4 Transform::rotation_matrix() const
	{
		return glm::toMat4(rotation_);
	}

	const PVec3& Transform::scale() const
	{
		return scale_;
	}

	PMat4 Transform::scale_matrix() const
	{
		return glm::scale(PMatIdentity, scale_);
	}

	bool Transform::isVisible()
	{
		return isVisible_;
	}
}
