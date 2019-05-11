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

		Camera(float nearZ, float farZ, float ratio = 1.f)
		{
			reset(60.f, nearZ, farZ, ratio);
		}

		Camera(float fov, float nearZ, float farZ, float ratio)
		{
			reset(fov, nearZ, farZ, ratio);
		}

	public:

		void set_fov(float fov) 
		{ 
			fov_ = fov; 
		}
		void set_near_z(float nearZ) { nearZ_ = nearZ; }
		void set_far_z(float farZ) { farZ_ = farZ; }
		void set_ratio(float ratio) { ratio_ = ratio; }

		void set_location(float x, float y, float z)
		{ 
			location_[0] = x; 
			location_[1] = y; 
			location_[2] = z; 
		}

		void set_target(float x, float y, float z) 
		{ 
			target_[0] = x;
			target_[1] = y;
			target_[2] = z; 
		}

		void reset(float fov, float nearZ, float farZ, float ratio)
		{
			set_fov(fov);
			set_near_z(nearZ);
			set_far_z(farZ);
			set_ratio(ratio);
			set_location(0.f, 0.f, 0.f);
			set_target(0.f, 0.f, -1.f);
		}

	public:

		void move(const PVec3 & translation)
		{
			location_ += PVec4(translation, 1.f);
			target_ += PVec4(translation, 1.f);
		}

		void rotate(const PMat4& rotation)
		{
			target_ = location_ + rotation * (target_ - location_);
		}

	public:

		PMat4 get_projection() const
		{
			return glm::perspective(fov_, ratio_, nearZ_, farZ_);
		}

		PMat4 get_model_view() const
		{
			return glm::lookAt
			(
				PVec3(location_[0], location_[1], location_[2]),
				PVec3(target_[0], target_[1], target_[2]),
				PVec3(0.0f, 1.0f, 0.0f)
			);
		}

	public:

		float get_fov() const { return fov_; }
		float get_near_z() const { return nearZ_; }
		float get_far_z() const { return farZ_; }
		float get_ratio() const { return ratio_; }
		const PPoint4& get_location() const { return location_; }
		const PPoint4& get_target() const { return target_; }

	private:

		float  fov_;
		float  nearZ_;
		float  farZ_;
		float  ratio_;

	private:

		PPoint4  location_;
		PPoint4  target_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_CAMERA_H_
