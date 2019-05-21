#include <Camera.hpp>

namespace prz
{
	Camera::Camera(Scene& scene, const PString& name, float fov, float zNear, float zFar, float aspectRatio) :
		Entity(scene, name, nullptr),
		fov_(fov),
		zNear_(zNear),
		zFar_(zFar),
		aspectRatio_(aspectRatio),
		matrix_(PMatIdentity),
		projectionMatrix_(PMatIdentity),
		modelMatrix_(PMatIdentity),
		viewMatrix_(PMatIdentity)
	{
		calculate_projection_matrix();
	}

	void Camera::entity_update(float deltaTime)
	{
		Input_Manager& inputManager = Input_Manager::instance();

		float speed = 10.f * deltaTime;

		if (inputManager.is_key_pressed(PKey::LShift))
		{
			speed *= 5.f;
		}

		if (inputManager.is_key_pressed(PKey::W))
		{
			transform_.forward_translate(-speed);
		}
		if (inputManager.is_key_pressed(PKey::S))
		{
			transform_.forward_translate(speed);
		}
		if (inputManager.is_key_pressed(PKey::D))
		{
			transform_.left_translate(-speed);
		}
		if (inputManager.is_key_pressed(PKey::A))
		{
			transform_.left_translate(speed);
		}
		if (inputManager.is_key_pressed(PKey::Space))
		{
			if (inputManager.is_key_pressed(PKey::LControl))
			{
				transform_.up_translate(-speed);
			}
			else
			{
				transform_.up_translate(speed);
			}
		}

		if (inputManager.is_key_pressed(PKey::R))
		{
			transform_.set_translation(PVec3(0.f, 0.f, 0.f));
		}
		
		if (inputManager.is_mouse_pressed())
		{
			transform_.pitch(mouseSensitivityX * ((float)inputManager.curMouseX() - (float)inputManager.prevMouseX()));
			transform_.yaw(mouseSensitivityX * ((float)inputManager.curMouseY() - (float)inputManager.prevMouseY()));
		}

		calculate_matrix();
	}

	void Camera::reset(float fov, float zNear, float zFar, float aspectRatio)
	{
		fov_ = fov;
		zNear_ = zNear;
		zFar_ = zFar;
		aspectRatio_ = aspectRatio;

		calculate_projection_matrix();
	}
}