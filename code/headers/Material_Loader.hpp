/**
 * @file Input_Manager.hpp
 * @author Pablo Rodriguez Zurro (przuro@gmail.com)
 * @brief Class to load and store materials
 * @version 0.1
 * @date 30-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_MATERIAL_LOADER_H_
#define OPENGL_SCENE_MATERIAL_LOADER_H_

#include <Declarations.hpp>

namespace prz
{
	class Shader_Program;
	class Material;

	/**
	 * @brief Class to load and store materials
	 * 
	 */
	class Material_Loader
	{
	public:

		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return Material_Loader&
		 */
		static Material_Loader& instance()
		{
			static Material_Loader instance;
			return instance;
		}

	public:

		/**
		 * @brief Return the loaded material
		 * 
		 * @param name 
		 * @param shaderProgram 
		 * @param usesTransparency 
		 * @return PSPtr< Material > 
		 */
		PSPtr< Material > load_material
		(
			const PString& name,
			PSPtr< Shader_Program > shaderProgram,
			bool usesTransparency = false
		);

		/**
		 * @brief Return the loaded material
		 * 
		 * @param name 
		 * @param pathVertexShader 
		 * @param pathFragmentShader 
		 * @param usesTransparency 
		 * @return PSPtr< Material > 
		 */
		PSPtr< Material > load_material
		(
			const PString& name,
			const PString& pathVertexShader,
			const PString& pathFragmentShader,
			bool usesTransparency = false
		);

		/**
		 * @brief Return the loaded material
		 * 
		 * @param material 
		 * @return PSPtr< Material > 
		 */
		PSPtr< Material > load_material(PSPtr< Material > material);

	public:

		/**
		 * @brief returns the default material object
		 * 
		 * @return PSPtr< Material > 
		 */
		PSPtr< Material > get_default_material()
		{
			return loadedMaterials_["default_material"];
		}

		/**
		 * @brief returns a material by name
		 * 
		 * @param name 
		 * @return PSPtr< Material > 
		 */
		PSPtr< Material > get_material(const PString& name);

	public:

		/**
		 * @brief return if exists the material with the input name
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool exists_material_with_name(const PString& name);

		/**
		 * @brief return if is saved the input material in this loader
		 * 
		 * @param material 
		 * @return true 
		 * @return false 
		 */
		bool exists_material(PSPtr< Material > material);

	private:

		/**
		 * @brief Construct a new Material_Loader (private)
		 * 
		 */
		Material_Loader();
		
	private:

		PMap< PString, PSPtr< Material > > loadedMaterials_;

	};

} // !namespace prz

#endif //! OPENGL_SCENE_MATERIAL_LOADER_H_
