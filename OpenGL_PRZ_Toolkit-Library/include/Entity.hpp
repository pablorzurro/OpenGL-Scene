/**
 * @file Entity.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Core class that store models and a transform 
 * @version 0.1
 * @date 09-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_ENTITY_H_
#define OPENGL_SCENE_ENTITY_H_

#include <Transform.hpp>
#include <Model.hpp>
#include <Material.hpp>
#include <Material_Loader.hpp>
#include <Model_Loader.hpp>

namespace prz
{

	class Scene;
	
	/**
	 * @brief Core class that store models and a transform 
	 * 
	 */
	class Entity
	{
	public:

		/**
		 * @brief Construct a new Entity
		 * 
		 * @param scene 
		 * @param name 
		 * @param parent 
		 */
		Entity(Scene& scene, const PString& name, Transform* parent = nullptr) :
			transform_(*this, parent),
			sceneParent_(scene),
			name_(name)
		{}

		/**
		 * @brief Construct a new Entity
		 * 
		 * @param scene 
		 * @param name 
		 * @param parent 
		 */
		Entity(Scene& scene, const PString& name, PSPtr< Entity > parent = PSPtr< Entity >()) :
			Entity(scene, name, parent ? &parent->transform() : nullptr)
		{}

		/**
		 * @brief Destroy the Entity
		 * 
		 */
		~Entity(){}

	public:
		
		/**
		 * @brief Update the entity
		 * 
		 * @param deltaTime 
		 */
		void update(float deltaTime) 
		{
			transform_.update();

			entity_update(deltaTime);
		}

		/**
		 * @brief render the entity (deprecated)
		 * 
		 */
		virtual void render(){}

	public:

		/**
		 * @brief Add a model by loading it with the path and a material
		 * 
		 * @param path 
		 * @param material 
		 */
		void add_model(const PString& path, PSPtr< Material > material = Material_Loader::instance().get_default_material())
		{
			add_model(Model_Loader::instance().load_model(path, material));
		}


		/**
		 * @brief add a model
		 * 
		 * @param model 
		 */
		void add_model(PSPtr< Model > model)
		{
			if (!exists_model(model))
			{
				model->initialize(this);

				if (model->is_ok())
				{
					models_[model->name()] = model;
				}
			}
		}

	public:

		/**
		 * @brief Set the transform parent
		 * 
		 * @param parent 
		 */
		void set_parent(Transform* parent)
		{
			transform_.set_parent(parent); 
		}

		/**
		 * @brief Set the transform parent 
		 * 
		 * @param parent 
		 */
		void set_parent(PSPtr< Entity > parent)
		{
			transform_.set_parent(&parent->transform_);
		}

	public:

		/**
		 * @brief return if exists a model with a name
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool exists_model_with_name(const PString& name)
		{
			return models_.find(name) != models_.end();
		}

		/**
		 * @brief return if exists the same model 
		 * 
		 * @param model 
		 * @return true 
		 * @return false 
		 */
		bool exists_model(PSPtr< Model > model)
		{
			if (model)
			{
				return exists_model_with_name(model->name());
			}

			return false;
		}

	public:

		/**
		 * @brief returns a model by name
		 * 
		 * @param name 
		 * @return PSPtr< Model > 
		 */
		PSPtr< Model > get_model(const PString& name)
		{
			if (exists_model_with_name(name))
			{
				return models_[name];
			}

			return PSPtr< Model>();
		}

	public:

		/**
		 * @brief return the transform
		 * 
		 * @return Transform& 
		 */
		Transform& transform() { return transform_; }

		/**
		 * @brief return the scene
		 * 
		 * @return Scene& 
		 */
		Scene& scene() { return sceneParent_; }

		/**
		 * @brief return the models map
		 * 
		 * @return PMap< PString, PSPtr< Model > >& 
		 */
		PMap< PString, PSPtr< Model > >& models() { return models_; }

		/**
		 * @brief return the name
		 * 
		 * @return const PString& 
		 */
		const PString& name() const { return name_; }
		
	protected:

		/**
		 * @brief protected method to update the hierarchy
		 * 
		 * @param deltaTime 
		 */
		virtual void entity_update(float deltaTime) {}

	protected:

		Transform transform_;
	
	protected:

		PMap< PString,  PSPtr< Model > > models_;

	protected:

		Scene& sceneParent_;

	protected:

		PString name_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_ENTITY_H_
