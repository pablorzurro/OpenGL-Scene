#include <Mesh.hpp>

#include <Vertex_Array_Object.hpp>
#include <Vertex_Buffer_Object.hpp>
#include <Vertex_Attribute_Information.hpp>

namespace prz
{
	Mesh::Mesh() :
		primitiveMode_(GL_NONE),
		indicesType_(GL_NONE),
		nVertices_(0),
		name_("undefined")
	{}

	Mesh::Mesh(const PString& name, Primitive_Mode primitiveMode) :
		primitiveMode_(primitiveMode),
		indicesType_(Indices_Type::NO_INDICES_TYPE),
		nVertices_(0),
		name_(name)
	{}

	Mesh::Mesh(const PString& name, GLsizei nVertices, Primitive_Mode primitiveMode, Indices_Type indicesType) :
		primitiveMode_(primitiveMode),
		indicesType_(indicesType),
		nVertices_(nVertices),
		name_(name)
	{
		assert(nVertices > 0);
	}

	Mesh::Mesh(const PString& name, const PBuffer< GLfloat >& coordinates, const PBuffer< GLfloat >& normals, const PBuffer< GLuint  >& indices, Primitive_Mode primitiveMode, const PBuffer< GLfloat >& textureUVs, const PBuffer< GLfloat >& colors) :
		Mesh(name, (GLsizei)byte_sizeof(indices), primitiveMode, UNSIGNED_INT)
	{
		size_t nCoordinates = byte_sizeof(coordinates);
		size_t nNormals = byte_sizeof(normals);
		size_t nUVs = byte_sizeof(textureUVs);
		size_t nColors = byte_sizeof(colors);

		PList< PVAI > vertexAttributes =
		{
			PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(coordinates.data(), (GLsizei)nCoordinates, 3)), VBO_ORDER::COORDINATES)
		};

		if (nNormals > 0)
		{
			vertexAttributes.push_back
			(
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(normals.data(), (GLsizei)nNormals, 3)), VBO_ORDER::NORMALS)
			);
		}
		if (nUVs > 0)
		{
			vertexAttributes.push_back
			(
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(textureUVs.data(), (GLsizei)nUVs, 2)), VBO_ORDER::TEXTURE_COORD)
			);
		}
		if (nColors > 0)
		{
			vertexAttributes.push_back
			(
				PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(colors.data(), (GLsizei)nColors, 4)), VBO_ORDER::COLORS)
			);
		}

		vao_ = std::make_shared< PVAO >
		(
			vertexAttributes,
			PSPtr< PVBO >(std::make_shared< PVBO >(indices.data(), nVertices_, 1, Vertex_Buffer_Object::Target::ELEMENT_ARRAY_BUFFER))
		);
	}

	void Mesh::draw()
	{
		if (vao_)
		{
			if (!nVertices_ == 0)
			{
				vao_->bind();

				if (indicesType_ == NO_INDICES_TYPE)
				{
					glDrawArrays(primitiveMode_, 0, nVertices_);
				}
				else
				{
					glDrawElements(primitiveMode_, vao_->nIndices(), indicesType_, 0);
				}

				vao_->unbind();
			}
			else
			{
				cout << "Trying to render an empty mesh";
			}
		}
	}
}