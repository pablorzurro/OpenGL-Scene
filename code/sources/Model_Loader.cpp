#include <Model_Loader.hpp>

#include <Entity.hpp>
#include <Model.hpp>
#include <Mesh.hpp>
#include <Vertex_Array_Object.hpp>
#include <Vertex_Attribute_Information.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace Assimp;

namespace prz
{
	PSPtr<Model> Model_Loader::load_model(const PString& meshPath, PSPtr<Material> material)
	{
		static Importer importer;
		importer.FreeScene();

		const aiScene* assimpScene = importer.ReadFile(meshPath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

		if (!assimpScene)
		{
			cout << "Error parsing model in path: \"" + meshPath + "\" " + ": " + importer.GetErrorString() << endl;
			return PSPtr< Model >();
		}

		unsigned int numMeshes = assimpScene->mNumMeshes;

		PSPtr< Model > model(new Model(numMeshes, split_string_by_separator(meshPath, "/")));

		for (size_t i = 0; i < numMeshes; i++)
		{
			const aiMesh* assimpMesh = assimpScene->mMeshes[i];

			unsigned int numVertices = assimpMesh->mNumVertices;
			unsigned int numFaces = assimpMesh->mNumFaces;

			bool hasPositions = assimpMesh->HasPositions();

			//cout << assimpMesh->mName.C_Str() << endl;

			bool hasNormals = assimpMesh->HasNormals();
			bool hasTextureCoords = assimpMesh->HasTextureCoords(0); // There are up to 8 vertex texture coordinates slots, only will be used the first here
			bool hasColors = assimpMesh->HasVertexColors(0);	// There are up to 8 vertex colors slots, only will be used the first here

			assert(hasPositions && hasNormals && numFaces > 0); // Check if there is any positions, normals and triangles in the mesh

			PBuffer< PVec3 > verPositions(numVertices), vertNormals(numVertices), texCoords(numVertices);
			PBuffer< PVec4 > vertColors(numVertices);

			PBuffer< PUVec3 > triangleIndices(numFaces);

			// Fill the positions, normals, texture coordinates and colors
			for (size_t i = 0; i < numVertices; i++)
			{
				if (hasPositions)
				{
					aiVector3D& vertexPositions = assimpMesh->mVertices[i];
					verPositions[i] = PVec3(vertexPositions.x, vertexPositions.y, vertexPositions.z);
				}

				if (hasNormals)
				{
					aiVector3D& vertexNormals = assimpMesh->mNormals[i];
					vertNormals[i] = PVec3(vertexNormals.x, vertexNormals.y, vertexNormals.z);
				}

				if (hasTextureCoords)
				{
					aiVector3D* vertexTextureCoordinates = assimpMesh->mTextureCoords[0];
					texCoords[i] = PVec3(vertexTextureCoordinates[0].x, vertexTextureCoordinates[0].y, vertexTextureCoordinates[0].z);
				}

				if (hasColors)
				{
					aiColor4D* vertexColor = assimpMesh->mColors[0];
					vertColors[i] = PVec4(vertexColor[0].r, vertexColor[0].g, vertexColor[0].b, vertexColor[0].a);
				}
			}

			// Fill the indices
			for (size_t i = 0; i < numFaces; i++)
			{
				aiFace& face = assimpMesh->mFaces[i];
				assert(face.mNumIndices == 3);

				triangleIndices[i] = PUVec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
			}

			// Create the vertex attributes

			PList< PVAI > vertexAttributes =
			{
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(verPositions.data(), numVertices)), 0),
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertNormals.data(), numVertices)), 1)
			};

			if (hasTextureCoords)
			{
				vertexAttributes.push_back(PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(texCoords.data(), numVertices)), 2));
			}

			if (hasColors)
			{
				vertexAttributes.push_back(PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertColors.data(), numVertices)), 3));
			}

			PSPtr< Mesh > mesh(std::make_shared< Mesh>(TRIANGLES, numVertices, UNSIGNED_INT, assimpMesh->mName.C_Str()));

			mesh->set_vao(std::make_shared< PVAO >
			(
				vertexAttributes,
				PSPtr< PVBO >(std::make_shared< PVBO >(triangleIndices.data(), numFaces, Vertex_Buffer_Object::Target::ELEMENT_ARRAY_BUFFER))
			));

			model->add_piece(mesh, material);
		}

		cout << "Model with path: \"" + meshPath + "\" loaded. " + to_string(assimpScene->mNumMeshes) + " meshes detected" << endl;

		return model;
	}

	bool Model_Loader::load_model(const PString& meshPath, PSPtr<Entity> entityToSave, PSPtr<Material> material)
	{
		if (entityToSave.get())
		{
			PSPtr< Model > model = load_model(meshPath, material);
			entityToSave->add_model(model);

			return model.get();
		}

		return false;
	}

}