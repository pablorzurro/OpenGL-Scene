#include <Transform.hpp>
#include <Camera.hpp>
#include "Entity.hpp"

#include <gtx/quaternion.hpp>

namespace prz
{
	Transform::Transform(Entity& owner, Transform* parent, bool modelIsViewMatrix):
		owner_(owner),
		modelMatrix_(PMatIdentity),
		worldMatrix_(modelMatrix_),
		translation_(PVec3(0.f, 0.f, 0.f)),
		orientation_(PQuatIdentity),
		scale_(PVec3(1.f, 1.f, 1.f)),
		isVisible_(true),
		parent_(parent),
		renderer_(nullptr),
		isModelMatrixUpdated_(false),
		isWorldMatrixUpdated_(false),
		modelIsViewMatrix_(modelIsViewMatrix)
	{
		update_model_matrix();
	}

	Transform::Transform(Entity& owner, Transform& other):
		owner_(owner),
		modelMatrix_(other.modelMatrix_),
		worldMatrix_(other.worldMatrix_),
		isVisible_(other.isVisible_),
		parent_(other.parent_),
		renderer_(other.renderer_),
		translation_(other.translation_),
		orientation_(other.orientation_),
		scale_(other.scale_),
		isModelMatrixUpdated_(other.isModelMatrixUpdated_),
		isWorldMatrixUpdated_(other.isWorldMatrixUpdated_),
		modelIsViewMatrix_(other.modelIsViewMatrix_)
	{}

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
		orientation_ *= glm::normalize(rotation);
		isModelMatrixUpdated_ = false; 
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
		assert(renderer);
		renderer_ = renderer;
	}

	void Transform::set_translation(const PVec3& newTranslation)
	{
		translation_ = newTranslation;
		isModelMatrixUpdated_ = false; 
	}

	void Transform::set_orientation(const PQuat& newOrientation)
	{
		orientation_ = newOrientation;
		isModelMatrixUpdated_ = false; 
	}

	void Transform::set_orientation(const PVec3& newOrientation, bool inRadians)
	{
		set_orientation(get_quaternion_from(newOrientation, inRadians));
	}

	void Transform::set_scale(const PVec3& newScale)
	{
		scale_ = newScale;
		isModelMatrixUpdated_ = false; 
	}

	void Transform::set_visible(bool visibility)
	{
		isVisible_ = visibility;
	}

	PMat4 Transform::modelMatrix() 
	{
		update_model_matrix();
		return modelMatrix_;
	}

	PMat4 Transform::inverse_modelMatrix()
	{
		return glm::inverse(modelMatrix_);
	}

	PMat4 Transform::worldMatrix()
	{
		update_world_matrix();

		if (modelIsViewMatrix_)
		{
			return viewMatrix();
		}

		return worldMatrix_;
	}

	PMat4 Transform::inverse_worldMatrix()
	{
		update_world_matrix();
		return glm::inverse(worldMatrix_);
	}

	PMat4 Transform::viewMatrix()
	{
		update_world_matrix();
		return translation_matrix() * rotation_matrix();
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

	const PQuat& Transform::orientation() const
	{
		return orientation_;
	}

	PVec3 Transform::euler_rotation(bool inDegrees) const
	{
		PVec3 vec = glm::eulerAngles(orientation_);

		if (inDegrees)
		{
			vec = glm::degrees(vec);
		}

		return vec;
	}
		
	PMat4 Transform::rotation_matrix() const
	{
		return glm::toMat4(orientation_);
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

	void Transform::update_model_matrix()
	{
		if (!isModelMatrixUpdated_)
		{
			modelMatrix_ = translation_matrix() * rotation_matrix() * scale_matrix();
			
			isModelMatrixUpdated_ = true;
			isWorldMatrixUpdated_ = false;
		}
	}

	void Transform::update_world_matrix()
	{	
		update_model_matrix();

		if(!isWorldMatrixUpdated_)
		{
			worldMatrix_ = modelMatrix();

			if (parent_)
			{
				worldMatrix_ = parent_->worldMatrix() * modelMatrix_; // Calling the parent hierarchy to obtain the total transformation
				isWorldMatrixUpdated_ = true;
			}
		}
	}
}
