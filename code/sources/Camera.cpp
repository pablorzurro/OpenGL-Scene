#include <Camera.hpp>

namespace prz
{
	Camera::Camera(Scene& scene, float fov, float zNear, float zFar, float aspectRatio)
		:
		Entity(scene, nullptr, true),
		fov_(fov),
		zNear_(zNear),
		zFar_(zFar),
		aspectRatio_(aspectRatio),
		matrix_(PMatIdentity),
		projectionMatrix_(PMatIdentity),
		viewMatrix_(PMatIdentity)
	{
		calculate_projection_matrix();
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
		viewMatrix_ = transform_.viewMatrix();
		calculate_matrix();
	}
}