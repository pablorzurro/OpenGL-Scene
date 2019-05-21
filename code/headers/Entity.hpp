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

#ifndef OPENGL_SCENE_ENTITY_H_
#define OPENGL_SCENE_ENTITY_H_

#include <Transform.hpp>
#include <Model.hpp>
#include <Material.hpp>
#include <Model_Loader.hpp>

namespace prz
{

	class Scene;
	
	class Entity
	{
	public:

		Entity(Scene& scene, const PString& name, Transform* parent = nullptr) :
			transform_(*this, parent),
			sceneParent_(scene),
			name_(name)
		{}

		Entity(Scene& scene, const PString& name, PSPtr< Entity > parent = PSPtr< Entity >()) :
			Entity(scene, name, parent ? &parent->transform() : nullptr)
		{}

		~Entity(){}

	public:

		void update(float deltaTime) 
		{
			transform_.update();

			entity_update(deltaTime);
		}

		virtual void render(){}

	public:

		void add_model(const PString& path, PSPtr< Material > material = Material::default_material())
		{
			add_model(Model_Loader::instance().load_model(path, material));
		}

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

		void set_parent(Transform* parent)
		{
			transform_.set_parent(parent); 
		}

		void set_parent(PSPtr< Entity > parent)
		{
			transform_.set_parent(&parent->transform_);
		}

	public:

		bool exists_model_with_name(const PString& name)
		{
			return models_.find(name) != models_.end();
		}

		bool exists_model(PSPtr< Model > model)
		{
			if (model)
			{
				return exists_model_with_name(model->name());
			}

			return false;
		}

	public:

		PSPtr< Model > get_model(const PString& name)
		{
			if (exists_model_with_name(name))
			{
				return models_[name];
			}

			return PSPtr< Model>();
		}

	public:

		Transform& transform() { return transform_; }
		Scene& scene() { return sceneParent_; }
		PMap< PString, PSPtr< Model > >& models() { return models_; }
		const PString& name() const { return name_; }
		
	protected:

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
