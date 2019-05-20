#include <Camera.hpp>

namespace prz
{
	Camera::Camera(Scene& scene, const PString& name, float fov, float zNear, float zFar, float aspectRatio) :
		Entity(scene, name, nullptr, true),
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

		float yawRotation = mouseSensitivityX * ((float)inputManager.curMouseX() - (float)inputManager.prevMouseX());
		float pitchRotation = mouseSensitivityY * ((float)inputManager.curMouseY() - (float)inputManager.prevMouseY());

		transform_.rotate(yawRotation, pitchRotation, 0.f);

		//cout << glm::to_string(inputManager.current_mouse_position()) + "         " + glm::to_string(inputManager.previous_mouse_position()) << endl;
		//cout << to_string(yawRotation)  + "      "+ to_string(pitchRotation) << endl;

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