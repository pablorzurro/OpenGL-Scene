#include <Texture_Loader.hpp>

namespace prz
{
	PSPtr< Texture > Texture_Loader::load_texture2D(const PString& texturePath, const PString& textureName)
	{
		// If is already loaded return the loaded one and don't create another
		if (is_texture_loaded(texturePath))
		{
			return textures_[texturePath];
		}

		PString finalName = textureName;

		if (textureName == "no_input_name")
		{
			finalName = split_string_by_separator(texturePath, "/");
		}

		PBuffer<PString> texturePathToBuffer{ texturePath };

		PSPtr<Texture> texture2D(allocate_texture(make_shared<Texture_2D>(texturePathToBuffer, finalName), texturePath, textureName));
		textures2DByName_[finalName] = static_cast<Texture_2D*>(texture2D.get());

		return texture2D;
	}

	PSPtr< Texture > Texture_Loader::load_cube_map(const PString& textureRootPath, const PString& textureName)
	{
		// If is already loaded return the loaded one and don't create another
		if (is_texture_loaded(textureRootPath))
		{
			return textures_[textureRootPath];
		}

		PString rootName = split_string_by_separator(textureRootPath, "/");
		PString path = textureRootPath;
		path.replace(path.find(rootName), rootName.length(), "");
		PString fileExtension = "." + split_string_by_separator(rootName, ".");

		PString finalName = textureName;
		if (textureName == "no_input_name")
		{
			finalName = rootName;
		}

		int cubeSides = 6;
		
		rootName.replace(rootName.find(fileExtension), fileExtension.length(), "");

		PBuffer<PString> texturePathToBuffer(cubeSides);

		for (size_t i = 0, cubeMapNumeration = 1; i < cubeSides; ++i, ++cubeMapNumeration)
		{
			texturePathToBuffer[i] = path + rootName + to_string(cubeMapNumeration) + fileExtension;
		}

		PSPtr<Texture> textureCube(allocate_texture(make_shared<Texture_Cube>(texturePathToBuffer, finalName), textureRootPath, finalName));
		texturesCubeByName_[finalName] = static_cast<Texture_Cube*>(textures_[textureRootPath].get());

		return textureCube;
	}
}
