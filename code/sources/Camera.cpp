#include <Camera.hpp>

namespace prz
{
	Camera::Camera(Scene& scene, const PString& name, float fov, float zNear, float zFar, float aspectRatio) :
		Entity(scene, name, nullptr, true, true),
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

	void Camera::update(float deltaTime)
	{
		Input_Manager& inputManager = Input_Manager::instance();

		if (inputManager.is_key_pressed(PKey::W))
		{
			transform_.translate(0.f, 0.f, 10.f);
		}
		if (inputManager.is_key_pressed(PKey::S))
		{
			transform_.translate(0.f, 0.f, -10.f);
		}
		if (inputManager.is_key_pressed(PKey::D))
		{
			transform_.translate(0.f, 0.f, 10.f);
		}
		if (inputManager.is_key_pressed(PKey::A))
		{
			transform_.translate(0.f, 0.f, -10.f);
		}
		if (inputManager.is_key_pressed(PKey::R))
		{
			transform_.set_translation(PVec3(0.f, 0.f, 0.f));
		}

		/*if (inputManager.is_mouse_pressed() == false)
			return;*/

		PVec2 mouseDelta(inputManager.current_mouse_position() - inputManager.previous_mouse_position());
		PVec2 normalizedMouseDelta = PVec2(mouseSensitivityX, mouseSensitivityY) * mouseDelta;

		transform_.rotate(normalizedMouseDelta.x, normalizedMouseDelta.y, 0.f);
	}

	void Camera::reset(float fov, float zNear, float zFar, float aspectRatio)
	{
		fov_ = fov;
		zNear_ = zNear;
		zFar_ = zFar;
		aspectRatio_ = aspectRatio;

		calculate_projection_matrix();
	}

	void Camera::on_local_matrix_update()
	{
		modelMatrix_ = transform_.scale_matrix();
 		viewMatrix_ = transform_.viewMatrix();
		calculate_matrix();
	}
}