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

		static aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		static aiColor4D ZeroColor(0.0f, 0.0f, 0.0f, 1.f);

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

			unsigned int n2DVertComponents = numVertices * 2;
			unsigned int n3DVertComponents = numVertices * 3;
			unsigned int n4DVertComponents = n2DVertComponents * 2;

			PBuffer< GLfloat > vertCoords(n3DVertComponents);
			PBuffer< GLfloat > vertNormals(n3DVertComponents);
			PBuffer< GLfloat > vertTexCoords(n2DVertComponents);
			PBuffer< GLfloat > vertColors(n4DVertComponents);


			// Fill the positions, normals, texture coordinates and colors
			for (size_t i = 0; i < numVertices; ++i)
			{
				size_t curIndex2D = i * 2, curIndex3D = i * 3, curIndex4D = curIndex2D * 2;

				if (hasPositions)
				{
					aiVector3D& vertexPositions = assimpMesh->mVertices[i];
					vertCoords[curIndex3D] = vertexPositions.x; vertCoords[curIndex3D + 1] = vertexPositions.y; vertCoords[curIndex3D + 2] = vertexPositions.z;
				}

				if (hasNormals)
				{
					aiVector3D& vertexNormals = assimpMesh->mNormals[i];
					vertNormals[curIndex3D] = vertexNormals.x; vertNormals[curIndex3D + 1] = vertexNormals.y; vertNormals[curIndex3D + 2] = vertexNormals.z;
				}

				const aiVector3D* vertexTextureCoordinates = hasTextureCoords ? &(assimpMesh->mTextureCoords[0][i]) : &Zero3D;
				vertTexCoords[curIndex2D] = vertexTextureCoordinates->x; vertTexCoords[curIndex2D + 1] = vertexTextureCoordinates->y;

				const aiColor4D* vertexColor = hasColors ? &(assimpMesh->mColors[0][i]) : &ZeroColor;
				vertColors[curIndex4D] = vertexColor->r; vertColors[curIndex4D + 1] = vertexColor->g; vertColors[curIndex4D + 2] = vertexColor->b; vertColors[curIndex4D + 3] = vertexColor->a;
			}

			unsigned int nIndices = numFaces * 3;
			PBuffer< GLuint > indices(nIndices);

			// Fill the indices
			for (size_t i = 0; i < numFaces; i++)
			{
				size_t curIndex3D = i * 3;

				aiFace& face = assimpMesh->mFaces[i];
				assert(face.mNumIndices == 3);

				indices[curIndex3D] = face.mIndices[0]; indices[curIndex3D + 1] = face.mIndices[1]; indices[curIndex3D + 2] = face.mIndices[2];
			}

			// Create the vertex attributes

			PList< PVAI > vertexAttributes =
			{
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertCoords.data(), sizeof(GLfloat) * n3DVertComponents, 3)), Mesh::VBO_ORDER::COORDINATES),
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertNormals.data(), sizeof(GLfloat) * n3DVertComponents, 3)), Mesh::VBO_ORDER::NORMALS)
			};

			if (hasTextureCoords)
			{
				// Choose if push the texCoords buffer or not, is set to default 0,0
				vertexAttributes.push_back(PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertTexCoords.data(), sizeof(GLfloat) * n2DVertComponents, 2)), Mesh::VBO_ORDER::TEXTURE_COORD));
			}
			if (hasColors)
			{
				// Choose if push the color buffer or not, is set to default 0 0 0 1 color
				vertexAttributes.push_back(PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(vertColors.data(), sizeof(GLfloat)* n4DVertComponents, 4)), Mesh::VBO_ORDER::COLORS));
			}

			PSPtr< Mesh > mesh(std::make_shared< Mesh>(TRIANGLES, numVertices, UNSIGNED_INT, assimpMesh->mName.C_Str()));

			mesh->set_vao(std::make_shared< PVAO >
			(
				vertexAttributes,
				PSPtr< PVBO >(std::make_shared< PVBO >(indices.data(), sizeof(GLuint) * nIndices, 1, Vertex_Buffer_Object::Target::ELEMENT_ARRAY_BUFFER))
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