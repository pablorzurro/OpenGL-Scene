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
#include "Utilities.hpp"

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

	public:

		PSPtr< Texture > load_texture2D(const PString& texturePath, const PString& textureName = "no_input_name");
		PSPtr< Texture > load_cube_map(const PString& textureRootPath, const PString& textureName = "no_input_name");

	public:

		/**
		 * @brief return if is loaded a texture by path
		 * 
		 * @param texturePath 
		 * @return true 
		 * @return false 
		 */
		bool is_texture_loaded(const PString& texturePath) const // Remember that a texture with multiple images is stored with the first path received
		{
			return textures_.find(texturePath) != textures_.end();
		}

		/**
		 * @brief return if is loaded a texture by name
		 * 
		 * @param textureName 
		 * @return true 
		 * @return false 
		 */
		bool is_texture_loaded_by_name(const PString& textureName) const
		{
			return texturesByName_.find(textureName) != texturesByName_.end();
		}

		/**
		 * @brief return if is loaded a 2D texture by name
		 * 
		 * @param texture2DName 
		 * @return true 
		 * @return false 
		 */
		bool is_texture_2D_loaded(const PString& texture2DName) const
		{
			return textures2DByName_.find(texture2DName) != textures2DByName_.end();
		}


		bool is_texture_cube_loaded(const PString& textureCubeName) const
		{
			return texturesCubeByName_.find(textureCubeName) != texturesCubeByName_.end();
		}

	public:

		PSPtr< Texture > get_texture(const PString& texturePath)
		{
			return is_texture_loaded(texturePath) ? textures_[texturePath] : nullptr;
		}

		Texture* get_texture_by_name(const PString& textureName)
		{
			return is_texture_loaded_by_name(textureName) ? texturesByName_[textureName] : nullptr;
		}

		Texture_2D* get_texture_2d(const PString& texture2DName)
		{
			return is_texture_2D_loaded(texture2DName) ? textures2DByName_[texture2DName] : nullptr;
		}

		Texture_Cube* get_texture_cube(const PString& textureCubeName)
		{
			return is_texture_cube_loaded(textureCubeName) ? texturesCubeByName_[textureCubeName] : nullptr;
		}

	private:

		/**
		 * @brief Construct a new Input Manager object, private to avoid undesired instantiation
		 *
		 */
		Texture_Loader(){}

	private:


		PSPtr< Texture > allocate_texture(PSPtr< Texture > texture, const PString& texturePath, const PString& textureName)
		{
			textures_[texturePath] = texture;
			texturesByName_[textureName] = textures_[texturePath].get();

			return textures_[texturePath];
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
