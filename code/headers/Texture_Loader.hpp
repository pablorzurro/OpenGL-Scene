/**
 * @file Texture_Loader.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Singleton class to load, store and manage textures of any type
 * @version 0.1
 * @date 09-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_TEXTURE_LOADER_H_
#define OPENGL_SCENE_TEXTURE_LOADER_H_

#include "Texture_2D.hpp"
#include "Texture_Cube.hpp"

#include "Declarations.hpp"

namespace prz
{

	class Texture;

	class Texture_Loader
	{
	public:

		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return InputManager&
		 */
		static Texture_Loader& instance()
		{
			static Texture_Loader instance;
			return instance;
		}

	private:

		/**
		 * @brief Construct a new Input Manager object, private to avoid undesired instantiation
		 *
		 */
		Texture_Loader()
		{}

		bool is_texture_loaded()
		{

		}

		void load_texture2D()
		{

		}

		void load_cube_map()
		{

		}

	private:

		PMap< PString, PSPtr< Texture > > textures_;
		PMap< PString, Texture* > texturesByName_;

	private:

		PMap< PString, Texture_2D* > textures2DByName_;
		PMap< PString, Texture_Cube* > texturesCubeByName_;
	};


} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_LOADER_H_
