/**
 * @file Camera.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_CAMERA_H_
#define OPENGL_SCENE_CAMERA_H_

#include "Declarations.hpp"

namespace prz
{
    
	class Camera
	{
	public:

		Camera(float ratio = 1.f)
		{
			reset(60.f, 0.1f, 100.f, ratio);
		}

		Camera(float near_z, float far_z, float ratio = 1.f)
		{
			reset(60.f, near_z, far_z, ratio);
		}

		Camera(float fov, float near_z, float far_z, float ratio)
		{
			reset(fov, near_z, far_z, ratio);
		}

	public:

		float          get_fov() const { return fov_; }
		float          get_near_z() const { return nearZ_; }
		float          get_far_z() const { return farZ_; }
		float          get_ratio() const { return ratio_; }

		const Point& get_location() const { return location_; }
		const Point& get_target() const { return target_; }

	public:

		void set_fov(float new_fov) { fov_ = new_fov; }
		void set_near_z(float new_near_z) { nearZ_ = new_near_z; }
		void set_far_z(float new_far_z) { farZ_ = new_far_z; }
		void set_ratio(float new_ratio) { ratio_ = new_ratio; }

		void set_location(float x, float y, float z) { location_[0] = x; location_[1] = y; location_[2] = z; }
		void set_target(float x, float y, float z) { target_[0] = x; target_[1] = y; target_[2] = z; }

		void reset(float new_fov, float new_near_z, float new_far_z, float new_ratio)
		{
			set_fov(new_fov);
			set_near_z(new_near_z);
			set_far_z(new_far_z);
			set_ratio(new_ratio);
			set_location(0.f, 0.f, 0.f);
			set_target(0.f, 0.f, -1.f);
		}

	public:

		void move(const glm::vec3 & translation)
		{
			location_ += glm::vec4(translation, 1.f);
			target_ += glm::vec4(translation, 1.f);
		}

		void rotate(const glm::mat4 & rotation)
		{
			target_ = location_ + rotation * (target_ - location_);
		}

	public:

		glm::mat4 get_projection() const
		{
			return glm::perspective(fov_, ratio_, nearZ_, farZ_);
		}

		glm::mat4 get_model_view() const
		{
			return glm::lookAt
			(
				glm::vec3(location_[0], location_[1], location_[2]),
				glm::vec3(target_[0], target_[1], target_[2]),
				glm::vec3(0.0f, 1.0f, 0.0f)
			);
		}

	private:

		float  fov_;
		float  nearZ_;
		float  farZ_;
		float  ratio_;

		Point  location_;
		Point  target_;
	};


}

} // !namespace prz 

#endif // !OPENGL_SCENE_CAMERA_H_
