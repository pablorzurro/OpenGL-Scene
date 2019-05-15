#include <Transform.hpp>
#include <Camera.hpp>
#include "Entity.hpp"

#include <gtx/quaternion.hpp>

namespace prz
{
	Transform::Transform(Entity& owner, Transform* parent):
		owner_(owner),
		modelMatrix_(PMatIdentity),
		worldMatrix_(modelMatrix_),
		translation_(PVec3(0.f, 0.f, 0.f)),
		scale_(PVec3(1.f, 1.f, 1.f)),
		isVisible_(true),
		parent_(parent),
		renderer_(nullptr),
		isWorldMatrixUpdated_(false),
		isOwnerACamera_(static_cast<Camera*>(&owner_))
	{
		set_translation(PVec3(0.f, 0.f, 0.f));
		set_rotation(PVec3(0.f, 0.f, 0.f));
		set_scale(PVec3(1.f, 1.f, 1.f));
		worldMatrix(); // initialize the world matrix
	}

	Transform::Transform(Entity& owner, Transform& other):
		owner_(owner),
		modelMatrix_(other.modelMatrix_),
		worldMatrix_(other.worldMatrix_),
		isVisible_(other.isVisible_),
		parent_(other.parent_),
		renderer_(other.renderer_),
		translation_(other.translation_),
		rotation_(other.rotation_),
		scale_(other.scale_),
		isWorldMatrixUpdated_(other.isWorldMatrixUpdated_),
		isOwnerACamera_(other.isOwnerACamera_)
	{}

	void Transform::update_model_matrix()
	{
		if (!isOwnerACamera_)
		{
			modelMatrix_ = translation_matrix() * rotation_matrix() * scale_matrix(); // Original model matrix
		}	
		else
		{
			modelMatrix_ = scale_matrix();
		}

		owner_.on_local_matrix_update();
		isWorldMatrixUpdated_ = false;
	}

	void Transform::translate(const PVec3& translation)
	{
		set_translation(translation_ + translation);
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

	void Transform::rotate(const PQuat& rotation)
	{
		rotation_ *= rotation;
		update_model_matrix();
	}

	void Transform::rotate(const PVec3& eulerRotation, bool inRadians)
	{
		rotate(get_quaternion_from(eulerRotation, inRadians)); 
	}

	void Transform::rotate(float eulerAngleX, float eulerAngleY, float eulerAngleZ, bool inRadians)
	{
		rotate(PVec3(eulerAngleX, eulerAngleY, eulerAngleZ), inRadians);
	}

	void Transform::rotate_around_x(float eulerAngle, bool inRadians)
	{
		rotate(PVec3(eulerAngle, 0, 0), inRadians);
	}
	void Transform::rotate_around_y(float eulerAngle, bool inRadians)
	{
		rotate(PVec3(0, eulerAngle, 0), inRadians);
	}

	void Transform::rotate_around_z(float eulerAngle, bool inRadians)
	{
		rotate(PVec3(0, 0, eulerAngle), inRadians);
	}

	void Transform::scale(const PVec3& scale)
	{
		set_scale(scale_ + scale);
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

	void Transform::set_translation(const PVec3& newTranslation)
	{
		translation_ = newTranslation;
		update_model_matrix();
	}

	void Transform::set_rotation(const PQuat& newRotation)
	{
		rotation_ = newRotation;
		update_model_matrix();
	}

	void Transform::set_rotation(const PVec3& newRotation, bool inRadians)
	{
		set_rotation(get_quaternion_from(newRotation, inRadians));
	}

	void Transform::set_scale(const PVec3& newScale)
	{
		scale_ = newScale;
		update_model_matrix();
	}

	void Transform::set_visible(bool visibility)
	{
		isVisible_ = visibility;
	}

	const PMat4& Transform::modelMatrix()
	{
		return modelMatrix_;
	}

	PMat4 Transform::inverse_modelMatrix()
	{
		return inverse(modelMatrix_);
	}

	const PMat4& Transform::worldMatrix()
	{
		if (!isWorldMatrixUpdated_)
		{
			worldMatrix_ = modelMatrix_; // In camera case this will be the view matrix and will be applied to all children

			if (parent_)
			{
				worldMatrix_ = parent_->worldMatrix() * worldMatrix_; // Calling the parent hierarchy to obtain the total transformation
			}

			isWorldMatrixUpdated_ = true;
		}
		
		return worldMatrix_;
	}

	PMat4 Transform::inverse_worldMatrix()
	{
		return inverse(worldMatrix());
	}

	PMat4 Transform::viewMatrix()
	{
		return translation_matrix() * glm::transpose(rotation_matrix());
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

	PVec3 Transform::euler_rotation(bool inDegrees) const
	{
		PVec3 vec = glm::eulerAngles(rotation_);

		if (inDegrees)
		{
			vec = glm::degrees(vec);
		}

		return vec;
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
