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

#include <Model.hpp>
#include <Mesh.hpp>
#include <Vertex_Array_Object.hpp>

#include <Declarations.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace Assimp;

namespace prz
{
	class Model_Loader
	{
	public:

		static Model_Loader& instance()
		{
			static Model_Loader instance;
			return instance;
		}

	public:

		PSPtr< Model > load_model(const PString& meshPath, PSPtr< Material > material = Material::default_material())
		{
			importer_.FreeScene();

			const aiScene* assimpScene = importer_.ReadFile(meshPath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

			if (!assimpScene)
			{
				cout << "Error parsing " + meshPath + ": " + importer_.GetErrorString() << endl;
				return PSPtr< Model >();
			}

			unsigned int numMeshes = assimpScene->mNumMeshes;

			PSPtr< Model > model(new Model(numMeshes));
 
			for (size_t i = 0; i < numMeshes; i++)
			{
				const aiMesh* assimpMesh = assimpScene->mMeshes[i];
				unsigned int numVertices = assimpMesh->mNumVertices;

				PSPtr< Mesh > mesh(new Mesh(TRIANGLES, numVertices, UNSIGNED_INT));

				/*PSPtr< PVAO > vao(new PVAO
				(


				));*/
			}

			cout << "Model with path: " + meshPath + " loaded. " + to_string(assimpScene->mNumMeshes) + " meshes detected" << endl;

			return model;
		}

		bool load_model(const PString& meshPath, PSPtr<Entity> entityToSave, PSPtr< Material > material = Material::default_material())
		{
			if (entityToSave.get())
			{
				PSPtr< Model > model = load_model(meshPath, material);
				return model.get();
			}

			return false;
		}

	private:

		Model_Loader() {}

	private:

		Importer importer_;
	};
}

#endif // !OPENGL_SCENE_MESH_LOADER_H_
