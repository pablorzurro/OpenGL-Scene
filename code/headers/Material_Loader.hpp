/**
 * @file Input_Manager.hpp
 * @author Pablo Rodriguez Zurro (przuro@gmail.com)
 * @brief
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

		PSPtr< Material > load_material
		(
			const PString& name,
			PSPtr< Shader_Program > shaderProgram,
			bool usesTransparency = false
		);

		PSPtr< Material > load_material
		(
			const PString& name,
			const PString& pathVertexShader,
			const PString& pathFragmentShader,
			bool usesTransparency = false
		);

		PSPtr< Material > load_material(PSPtr< Material > material);

	public:

		PSPtr< Material > get_default_material()
		{
			return loadedMaterials_["default_material"];
		}

		PSPtr< Material > get_material(const PString& name);

	public:

		bool exists_material_with_name(const PString& name);
		bool exists_material(PSPtr< Material > material);

	private:

		Material_Loader();
		
	private:

		PMap< PString, PSPtr< Material > > loadedMaterials_;

	};

} // !namespace prz

#endif //! OPENGL_SCENE_MATERIAL_LOADER_H_
