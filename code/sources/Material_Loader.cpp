#include <Material_Loader.hpp>

#include <Material.hpp>
#include <Game.hpp>

namespace prz
{

	Material_Loader::Material_Loader()
	{
		PSPtr< Material > mat =  load_material(make_shared<Material>
		(
			"default_material",
			Game::assetsFolderPath() + "shaders/fragment_shader.frag",
			Game::assetsFolderPath() + "shaders/vertex_shader.vert"
		));

		mat->add_texture_2D(Game::assetsFolderPath() + "textures/2D/wood.png"/*"uv-checker-3.tga"*/, "texture_color");
	}

	PSPtr<Material> Material_Loader::load_material(const PString& name, PSPtr< Shader_Program > shaderProgram, bool usesTransparency)
	{
		if (!exists_material_with_name(name))
		{
			return loadedMaterials_[name] = make_shared< Material >
			(
				name,
				shaderProgram,
				usesTransparency
			);
		}

		return PSPtr< Material >();
	}

	PSPtr<Material> Material_Loader::load_material(const PString& name, const PString& pathVertexShader, const PString& pathFragmentShader, bool usesTransparency)
	{
		if (!exists_material_with_name(name))
		{
			return loadedMaterials_[name] = make_shared< Material >
			(
				name,
				pathVertexShader,
				pathFragmentShader,
				usesTransparency
			);
		}

		return PSPtr< Material >();
	}

	PSPtr<Material> Material_Loader::load_material(PSPtr< Material > material)
	{
		if (!exists_material(material))
		{
			return loadedMaterials_[material->name()] = material;
		}

		return PSPtr< Material >();
	}

	PSPtr<Material> Material_Loader::get_material(const PString& name)
	{
		if (exists_material_with_name(name))
		{
			return loadedMaterials_[name];
		}

		return PSPtr< Material >();
	}

	bool Material_Loader::exists_material_with_name(const PString& name)
	{
		return loadedMaterials_.find(name) != loadedMaterials_.end();
	}

	bool Material_Loader::exists_material(PSPtr< Material > material)
	{
		return exists_material_with_name(material->name());
	}
}
