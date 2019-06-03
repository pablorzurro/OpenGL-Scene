/**
 * @file Transform.hpp
 * @author Pablo Rodriguez Zurro (przuro@gmail.com)
 * @brief Class that represents the transformation of an object in a scene
 * @version 0.1
 * @date 09-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_TRANSFORM_H_
#define OPENGL_SCENE_TRANSFORM_H_

#include <Declarations.hpp>
#include <Utilities.hpp>

namespace prz
{
	class Renderer;
	class Entity;

	/**
	 * @brief Class that represents the transformation of an object in a scene
	 * 
	 */
	class Transform
	{
	public:
		
		Transform() = delete;

		/**
		 * @brief Construct a new Transform
		 * 
		 * @param owner 
		 * @param parent 
		 */
		Transform(Entity& owner, Transform* parent = nullptr);

		/**
		 * @brief Construct a new Transform
		 * 
		 * @param owner 
		 * @param other 
		 */
		Transform(Entity& owner, Transform& other);

	public:

		/**
		 * @brief Update the members
		 * 
		 */
		void update()
		{
			update_world_matrix();
		}

	public:

		/**
		 * @brief Translate by: 
		 * 
		 * @param translation 
		 */
		void translate(const PVec3& translation);

		/**
		 * @brief Translate by:
		 * 
		 * @param translationX 
		 * @param translationY 
		 * @param translationZ 
		 */
		void translate(float translationX, float translationY, float translationZ);

	public:

		/**
		 * @brief Translate in x
		 * 
		 * @param translationX 
		 */
		void translate_in_x(float translationX);

		/**
		 * @brief Translate in y
		 * 
		 * @param translationY 
		 */
		void translate_in_y(float translationY);

		/**
		 * @brief Translate in z
		 * 
		 * @param translationZ 
		 */
		void translate_in_z(float translationZ);

		/**
		 * @brief Translate in forward vector
		 * 
		 * @param translation 
		 */
		void forward_translate(float translation);		

		/**
		 * @brief Translate in left vector
		 * 
		 * @param translation 
		 */
		void left_translate(float translation);

		/**
		 * @brief Translate in up vector
		 * 
		 * @param translation 
		 */
		void up_translate(float translation);

	public:

		/**
		 * @brief Rotate by:
		 * 
		 * @param rotation 
		 */
		void rotate(const PQuat& rotation);

		/**
		 * @brief Rotate by:
		 * 
		 * @param rotation 
		 * @param inRadians 
		 */
		void rotate(const PVec3& rotation, bool inRadians = false);

		/**
		 * @brief Rotate by:
		 * 
		 * @param eulerAngleX 
		 * @param eulerAngleY 
		 * @param eulerAngleZ 
		 * @param inRadians 
		 */
		void rotate(float eulerAngleX, float eulerAngleY, float eulerAngleZ, bool inRadians = false);

	public:

		/**
		 * @brief Rotate pitch
		 * 
		 * @param eulerAngle 
		 * @param inRadians 
		 */
		void pitch(float eulerAngle, bool inRadians = false);

		/**
		 * @brief Rotate yaw
		 * 
		 * @param eulerAngle 
		 * @param inRadians 
		 */
		void yaw(float eulerAngle, bool inRadians = false);

		/**
		 * @brief Rotate roll
		 * 
		 * @param eulerAngle 
		 * @param inRadians 
		 */
		void roll(float eulerAngle, bool inRadians = false);

	public:

		/**
		 * @brief Scale by: 
		 * 
		 * @param scale 
		 */
		void scale(const PVec3& scale);

		/**
		 * @brief Scale by: 
		 * 
		 * @param scaleX 
		 * @param scaleY 
		 * @param scaleZ 
		 */
		void scale(float scaleX, float scaleY, float scaleZ);

	public:

		/**
		 * @brief Scale in x
		 * 
		 * @param scaleX 
		 */
		void scale_x(float scaleX);

		/**
		 * @brief Scale in y
		 * 
		 * @param scaleY 
		 */
		void scale_y(float scaleY);

		/**
		 * @brief Scale in z
		 * 
		 * @param scaleZ 
		 */
		void scale_z(float scaleZ);

	public:

		/**
		 * @brief Set the parent
		 * 
		 * @param parent 
		 */
		void set_parent(Transform* parent);

	public:

		/**
		 * @brief Set the renderer
		 * 
		 * @param renderer 
		 */
		void set_renderer(Renderer* renderer);

	public:

		void set_model_matrix(const PMat4& newModelMatrix)
		{
			modelMatrix_ = newModelMatrix;
			isModelMatrixUpdated_ = true;
		}

	public:

		/**
		 * @brief Set the translation
		 * 
		 * @param newTranslation 
		 */
		void set_translation(const PVec3& newTranslation);

		/**
		 * @brief Set the orientation by:
		 * 
		 * @param newOrientation 
		 */
		void set_orientation(const PQuat& newOrientation);

		/**
		 * @brief Set the orientation by:
		 * 
		 * @param newOrientation 
		 * @param inRadians 
		 */
		void set_orientation(const PVec3& newOrientation, bool inRadians = false);

		/**
		 * @brief Set the scale
		 * 
		 * @param newScale 
		 */
		void set_scale(const PVec3& newScale);

	public:

		/**
		 * @brief Set the visibility
		 * 
		 * @param visibility 
		 */
		void set_visible(bool visibility);
		
	public:

		/**
		 * @brief Return the model matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 modelMatrix();

		/**
		 * @brief Return the inverse model matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 inverse_modelMatrix();
		
		/**
		 * @brief Return the world matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 worldMatrix();

		/**
		 * @brief Return the inverse world matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 inverse_worldMatrix();

		/**
		 * @brief Return the view matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 viewMatrix();

	public:

		/**
		 * @brief Return the parent
		 * 
		 * @return Transform* 
		 */
		Transform* parent();

		/**
		 * @brief Return the owner
		 * 
		 * @return Entity& 
		 */
		Entity& owner();

	public:

		/**
		 * @brief Return the renderer
		 * 
		 * @return Renderer* 
		 */
		Renderer* renderer();

	public:

		/**
		 * @brief Return the translation
		 * 
		 * @return const PVec3& 
		 */
		const PVec3& translation() const;

		/**
		 * @brief Return the translation matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 translation_matrix() const;

		/**
		 * @brief Return the orientation 
		 * 
		 * @return const PQuat& 
		 */
		const PQuat& orientation() const;

		/**
		 * @brief Return the euler rotation (deprecated)
		 * 
		 * @param inDegrees 
		 * @return PVec3 
		 */
		PVec3 euler_rotation(bool inDegrees = true) const;

		/**
		 * @brief Return the rotation matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 rotation_matrix() const;

		/**
		 * @brief Return the scale
		 * 
		 * @return const PVec3& 
		 */
		const PVec3& scale() const; 

		/**
		 * @brief Return the scale matrix
		 * 
		 * @return PMat4 
		 */
		PMat4 scale_matrix()const;


	public:

		/**
		 * @brief Return the forward vector
		 * 
		 * @return PVec3 
		 */
		PVec3 get_forward() const;

		/**
		 * @brief Return the left vector 
		 * 
		 * @return PVec3 
		 */
		PVec3 get_left() const;

		/**
		 * @brief Return the up vector
		 * 
		 * @return PVec3 
		 */
		PVec3 get_up() const;

	public:

		/**
		 * @brief Return if is visible
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isVisible();

	protected:

		/**
		 * @brief Update the model matrix
		 * 
		 */
		void update_model_matrix();

		/**
		 * @brief Update the world matrix
		 * 
		 */
		void update_world_matrix();

	protected:

		PMat4 modelMatrix_;
		PMat4 worldMatrix_;

	protected:

		Transform* parent_;
		Entity& owner_;

	protected:

		Renderer* renderer_;

	protected:

		PVec3 translation_;
		PQuat orientation_;
		PVec3 scale_;

	protected:

		bool isVisible_;

	protected:

		bool isModelMatrixUpdated_;
		bool isWorldMatrixUpdated_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TRANSFORM_H_
