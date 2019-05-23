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

#include <Entity.hpp>
#include <Input_Manager.hpp>

#include <Declarations.hpp>
#include <Utilities.hpp>

namespace prz
{
	class Scene;

	class Camera : public Entity
	{
	public:

		Camera(Scene& scene, const PString& name, float fov, float zNear, float zFar, float aspectRatio);
		Camera(Scene& scene, const PString& name, float ratio = 1.f): Camera(scene, name, 20.f, 0.1f, 100.f, ratio){}
		Camera(Scene& scene, const PString& name, float zNear, float zFar, float aspectRatio = 1.f): Camera(scene, name, 60.f, zNear, zFar, aspectRatio){}
		
	public:

		void entity_update(float deltaTime) override;
		
	public:

		void set_fov(float fov) {fov_ = fov; calculate_projection_matrix();}
		void set_near_z(float zNear) {zNear_ = zNear; calculate_projection_matrix();}
		void set_far_z(float zFar) {zFar_ = zFar; calculate_projection_matrix();}
		void set_ratio(float aspectRatio) {aspectRatio_ = aspectRatio; calculate_projection_matrix();}

	public:

		void reset(float fov, float zNear, float zFar, float aspectRatio);
		
	public:

		const PMat4& matrix() const { return matrix_; }
		const PMat4& viewMatrix() const { return viewMatrix_; }
		const PMat4& modelMatrix() const { return modelMatrix_; }
		const PMat4& projectionMatrix() const { return projectionMatrix_; }

	public:

		float fov() const { return fov_; }
		float nearZ() const { return zNear_; }
		float farZ() const { return zFar_; }
		float ratio() const { return aspectRatio_; }

	private:

		void calculate_matrix()
		{
			modelMatrix_ = transform_.scale_matrix();
			viewMatrix_ = transform_.viewMatrix();
			matrix_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
		}

		void calculate_projection_matrix()
		{
			projectionMatrix_ = glm::perspective(fov_, aspectRatio_, zNear_, zFar_);
			calculate_matrix();
		}

	private:

		float  fov_;
		float  zNear_;
		float  zFar_;
		float  aspectRatio_;

	private:

		PMat4 projectionMatrix_;
		PMat4 modelMatrix_;
		PMat4 viewMatrix_;
		PMat4 matrix_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_CAMERA_H_
