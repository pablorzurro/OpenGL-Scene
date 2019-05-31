/**
 * @file Renderer.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class to render all subscribed entities
 * @version 0.1
 * @date 09-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_RENDERER_H_
#define OPENGL_SCENE_RENDERER_H_

#include <Declarations.hpp>

namespace prz
{
	class Entity;
	class Scene;
	class Transform;
	class Material;
	class Mesh;
	class Shader_Program;
	class Camera;

	/**
	 * @brief Class to render all subscribed entities
	 * 
	 */
	class Renderer
	{
	public:
		
		using Meshes_By_Transform = PMap< Transform*, PList< PSPtr< Mesh > >* >; // Saves the meshes by transform. Will NOT save all meshes from a transform, only the ones that use a certain material.
		using Material_Batches = PMap< PSPtr< Material >, Meshes_By_Transform >; // Saves the meshes by transform that uses a material
		using Shader_Program_Batches =  PMap< PSPtr< Shader_Program >, Material_Batches>; // Saves the material batches that use a shader program

	public:

		/**
		 * @brief Construct a new Renderer
		 * 
		 * @param sceneOwner 
		 */
		Renderer(Scene& sceneOwner) :
			owner_(sceneOwner)
		{}

		/**
		 * @brief Destroy the Renderer
		 * 
		 */
		~Renderer()
		{}

	public:

		/**
		 * @brief Update the render queues
		 * 
		 */
		void update() 
		{
			update_render_queues(); 
		}

		/**
		 * @brief Render the batches queues
		 * 
		 * @param activeCamera 
		 */
		void render(const PSPtr< Camera > activeCamera);
	
	public:

		/**
		 * @brief subscribe a new entity
		 * 
		 * @param entity 
		 * @return true 
		 * @return false 
		 */
		bool subscribe_entity(PSPtr< Entity > entity);

		/**
		 * @brief unsubscribe an entity
		 * 
		 * @param entity 
		 * @return true 
		 * @return false 
		 */
		bool unsubscribe_entity(PSPtr< Entity > entity);

	public:
		/**
		 * @brief return if an entity with name is subscribed
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool is_entity_subscribed(const PString& name) const 
		{
			return subscribedEntities_.find(name) != subscribedEntities_.end();
		}

		/**
		 * @brief return if the input entity is subscribed
		 * 
		 * @param entity 
		 * @return true 
		 * @return false 
		 */
		bool is_entity_subscribed(PSPtr< Entity > entity) const;
		
	private:

		/**
		 * @brief render a batches map
		 * 
		 * @param queueMap 
		 * @param activeCamera 
		 */
		void render_queue(Shader_Program_Batches& queueMap, const PSPtr< Camera > activeCamera);

	private:

		/**
		 * @brief update all batches maps
		 * 
		 */
		void update_render_queues();

	private:

		/**
		 * @brief Set the material shared uniforms
		 * 
		 * @param material 
		 * @param activeCamera 
		 */
		void set_material_shared_uniforms(PSPtr< Material > material, const PSPtr< Camera > activeCamera /*PBuffer< PSPtr< Light > > lights*/);

		/**
		 * @brief Set the material local uniforms
		 * 
		 * @param material 
		 * @param transform 
		 */
		void set_material_local_uniforms(PSPtr< Material> material, Transform* transform);

	private:

		Shader_Program_Batches renderQueue_; // This map contains the active shader program batches that are ready to be rendered. To be active, it needs to be used by at least one material and the material used by at least one mesh.
		Shader_Program_Batches transparencyRenderQueue_;
		PMap< PString, PSPtr< Entity > > subscribedEntities_;

	private:

		Scene& owner_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_RENDERER_H_
