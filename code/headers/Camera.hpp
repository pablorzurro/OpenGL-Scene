/**
 * @file Camera.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Class to handle the view of the scene.
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

	/**
	 * @brief 
	 * 
	 */
	class Camera : public Entity
	{
	public:

		/**
		 * @brief Construct a new Camera
		 * 
		 * @param scene 
		 * @param name 
		 * @param fov 
		 * @param zNear 
		 * @param zFar 
		 * @param aspectRatio 
		 */
		Camera(Scene& scene, const PString& name, float fov, float zNear, float zFar, float aspectRatio);

		/**
		 * @brief Construct a new Camera
		 * 
		 * @param scene 
		 * @param name 
		 * @param ratio 
		 */
		Camera(Scene& scene, const PString& name, float ratio = 1.f): Camera(scene, name, 20.f, 0.1f, 400.f, ratio){}

		/**
		 * @brief Construct a new Camera
		 * 
		 * @param scene 
		 * @param name 
		 * @param zNear 
		 * @param zFar 
		 * @param aspectRatio 
		 */
		Camera(Scene& scene, const PString& name, float zNear, float zFar, float aspectRatio = 1.f): Camera(scene, name, 60.f, zNear, zFar, aspectRatio){}
		
	public:

		/**
		 * @brief Update the camera matrices
		 * 
		 * @param deltaTime 
		 */
		void entity_update(float deltaTime) override;
		
	public:

		/**
		 * @brief Set the fov object
		 * 
		 * @param fov 
		 */
		void set_fov(float fov) {fov_ = fov; calculate_projection_matrix();}

		/**
		 * @brief Set the near z object
		 * 
		 * @param zNear 
		 */
		void set_near_z(float zNear) {zNear_ = zNear; calculate_projection_matrix();}
		/**
		 * @brief Set the far z object
		 * 
		 * @param zFar 
		 */
		void set_far_z(float zFar) {zFar_ = zFar; calculate_projection_matrix();}

		/**
		 * @brief Set the ratio object
		 * 
		 * @param aspectRatio 
		 */
		void set_ratio(float aspectRatio) {aspectRatio_ = aspectRatio; calculate_projection_matrix();}

	public:

		/**
		 * @brief 
		 * 
		 * @param fov 
		 * @param zNear 
		 * @param zFar 
		 * @param aspectRatio 
		 */
		void reset(float fov, float zNear, float zFar, float aspectRatio);
		
	public:

		/**
		 * @brief 
		 * 
		 * @return const PMat4& 
		 */
		const PMat4& matrix() const { return matrix_; }

		/**
		 * @brief 
		 * 
		 * @return const PMat4& 
		 */
		const PMat4& viewMatrix() const { return viewMatrix_; }

		/**
		 * @brief 
		 * 
		 * @return const PMat4& 
		 */
		const PMat4& modelMatrix() const { return modelMatrix_; }

		/**
		 * @brief 
		 * 
		 * @return const PMat4& 
		 */
		const PMat4& projectionMatrix() const { return projectionMatrix_; }

	public:

		/**
		 * @brief 
		 * 
		 * @return float 
		 */
		float fov() const { return fov_; }

		/**
		 * @brief 
		 * 
		 * @return float 
		 */
		float nearZ() const { return zNear_; }

		/**
		 * @brief 
		 * 
		 * @return float 
		 */
		float farZ() const { return zFar_; }

		/**
		 * @brief 
		 * 
		 * @return float 
		 */
		float ratio() const { return aspectRatio_; }

	private:

		/**
		 * @brief 
		 * 
		 */
		void calculate_matrix()
		{
			modelMatrix_ = transform_.scale_matrix();
			viewMatrix_ = transform_.viewMatrix();
			matrix_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
		}

		/**
		 * @brief 
		 * 
		 */
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
