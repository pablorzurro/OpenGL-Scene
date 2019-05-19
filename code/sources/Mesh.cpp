#include <Mesh.hpp>
#include <Vertex_Array_Object.hpp>
#include <Vertex_Buffer_Object.hpp>

namespace prz
{
	Mesh::Mesh() :
		primitiveMode_(GL_NONE),
		indicesType_(GL_NONE),
		nVertices_(0),
		name_("undefined")
	{}
	Mesh::Mesh(Primitive_Mode primitiveMode, const PString& name) :
		primitiveMode_(primitiveMode),
		indicesType_(GL_NONE),
		nVertices_(0),
		name_(name)
	{}

	Mesh::Mesh(Primitive_Mode primitiveMode, GLsizei nVertices, Indices_Type indicesType, const PString& name) :
		primitiveMode_(primitiveMode),
		indicesType_(indicesType),
		nVertices_(nVertices),
		name_(name)
	{
		assert(nVertices > 0);
	}

	void Mesh::draw()
	{
		if (vao_.get())
		{
			assert(primitiveMode_ != GL_NONE);
			assert(nVertices_ > 0);

			vao_->bind();

			if (indicesType_ == GL_NONE)
			{
				glDrawArrays(primitiveMode_, 0, nVertices_);
			}
			else
			{
				glDrawElements(primitiveMode_, nVertices_, indicesType_, 0);
			}

			vao_->unbind();
		}
	}
}