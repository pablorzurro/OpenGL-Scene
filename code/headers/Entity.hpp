/**
 * @file GameObject.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 09-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_CUBE_MESH_H_
#define OPENGL_SCENE_CUBE_MESH_H_

#include "Transform.hpp"
#include "Model.hpp"

namespace prz
{

	class Scene;
	
	class Entity
	{
	public:

		Entity(Scene& scene, Transform* parent = nullptr):
			transform_(*this),
			sceneParent_(scene)
		{
			set_parent(parent);
		}

		Entity(PBuffer<PString> paths)
		{
		}

		~Entity()
		{}

	public:

		virtual void update() = 0;

	public:

		void set_parent(Transform* parent)
		{
			transform_.set_parent(parent); 
		}

	public:

		Transform& transform()
		{
			return transform_;
		}

		Scene& scene()
		{
			return sceneParent_; 
		}

	private:

		Transform transform_;
	
	private:

		PBuffer< PSPtr< Model > > models_;

	private:

		Scene& sceneParent_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_CUBE_MESH_H_
