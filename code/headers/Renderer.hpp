/**
 * @file Renderer.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
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

	class Renderer
	{
	public:

		using Meshes_By_Transform = PMap< Transform*, PList< PSPtr< Mesh > >* >; // Saves the meshes by transform. Will NOT save all meshes from a transform, only the ones that use a certain material.
		using Material_Batches = PMap< PSPtr< Material >, Meshes_By_Transform >; // Saves the meshes by transform that uses a material
		using Shader_Program_Batches =  PMap< PSPtr< Shader_Program >, Material_Batches>; // Saves the material batches that use a shader program

	public:

		Renderer(Scene& sceneOwner) :
			owner_(sceneOwner)
		{}

		~Renderer()
		{}

	public:

		void update() 
		{
			update_render_queue();
		}

		void render(const PSPtr< Camera > activeCamera);
	
	public:

		bool subscribe_entity(PSPtr< Entity > entity);
		bool unsubscribe_entity(PSPtr< Entity > entity);

	public:

		bool is_entity_subscribed(const PString& name) const 
		{
			return subscribedEntities_.find(name) != subscribedEntities_.end();
		}

		bool is_entity_subscribed(PSPtr< Entity > entity) const;
		
	private:

		void update_render_queue();

	private:

		void set_material_shared_uniforms(PSPtr< Material > material, const PSPtr< Camera > activeCamera /*PBuffer< PSPtr< Light > > lights*/);
		void set_material_local_uniforms(PSPtr< Material> material, Transform* transform);

	private:

		Shader_Program_Batches renderQueue_; // This map contains the active shader program batches that are ready to be rendered. To be active, it needs to be used by at least one material and the material used by at least one mesh.
		PMap< PString, PSPtr< Entity > > subscribedEntities_;

	private:

		Scene& owner_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_RENDERER_H_
