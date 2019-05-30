/**
 * @file Model_Loader.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 14-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_MESH_LOADER_H_
#define OPENGL_SCENE_MESH_LOADER_H_

#include <Material.hpp>
#include <Material_Loader.hpp>

#include <Declarations.hpp>

namespace prz
{
	class Entity;
	class Model;

	class Model_Loader
	{
	public:
		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return Model_Loader&
		 */
		static Model_Loader& instance()
		{
			static Model_Loader instance;
			return instance;
		}

	public:

		PSPtr< Model > load_model(const PString& meshPath, PSPtr< Material > material = Material_Loader::instance().get_default_material());
		bool load_model(const PString& meshPath, PSPtr<Entity> entityToSave, PSPtr< Material > material =  Material_Loader::instance().get_default_material());
	
	private:

		Model_Loader() {}
	};
}

#endif // !OPENGL_SCENE_MESH_LOADER_H_
