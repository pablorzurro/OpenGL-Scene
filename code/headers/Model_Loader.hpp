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

				PBuffer< PVec3 > vertCoords(numVertices), vertNormals(numVertices), texCoords(numVertices);
				PBuffer< PVec4 > vertColors(numVertices);

				for (size_t i = 0; i < numVertices; i++)
				{	
					aiVector3D& vertexCoordinates = assimpMesh->mVertices[i];
					vertCoords[i] = PVec3(vertexCoordinates.x, vertexCoordinates.y, vertexCoordinates.z);

					aiVector3D& vertexNormals = assimpMesh->mNormals[i];
					vertNormals[i] = PVec3(vertexNormals.x, vertexNormals.y, vertexNormals.z);

					aiVector3D& vertexTextureCoordinates = assimpMesh->mNormals[i];
					texCoords[i] = PVec3(vertexTextureCoordinates.x, vertexTextureCoordinates.y, vertexTextureCoordinates.z);

					aiColor4D* vertexColor = assimpMesh->mColors[i];
					vertColors[i] = PVec4(vertexColor->r, vertexColor->g, vertexColor->b, vertexColor->a);
				}

				unsigned int numFaces = assimpMesh->mNumFaces;

				PBuffer< PUVec3 > triangleIndices(numFaces);

				for (size_t i = 0; i < numFaces; i++)
				{
					aiFace& face = assimpMesh->mFaces[i];
					assert(face.mNumIndices == 3);

					triangleIndices[i] = PUVec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
				}

				PSPtr< Mesh > mesh(std::make_shared< Mesh>(TRIANGLES, numVertices, UNSIGNED_INT));

				PInitList<PVAI> vertexAttributes = 
				{ 
					PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertCoords.data(), numVertices)), 0, 3, GL_FLOAT),
					PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertNormals.data(), numVertices)), 1, 3, GL_FLOAT),
					PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(texCoords.data(), numVertices)), 2, 3, GL_FLOAT),
					PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertColors.data(), numVertices)), 3, 4, GL_FLOAT),
				};

				mesh->set_vao(std::make_shared<PVAO>
				(
					vertexAttributes,
					PSPtr< PVBO >(std::make_shared< PVBO >(triangleIndices.data(), numFaces))
				));

				model->add_piece(mesh);
			}

			cout << "Model with path: " + meshPath + " loaded. " + to_string(assimpScene->mNumMeshes) + " meshes detected" << endl;

			return model;
		}

		bool load_model(const PString& meshPath, PSPtr<Entity> entityToSave, PSPtr< Material > material = Material::default_material())
		{
			if (entityToSave.get())
			{
				PSPtr< Model > model = load_model(meshPath, material);
				model->initialize(entityToSave.get());
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
