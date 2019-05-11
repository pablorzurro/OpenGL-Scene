#include "Vertex_Array_Object.hpp"

namespace prz
{
	Vertex_Array_Object::Vertex_Array_Object(const std::initializer_list< PVAI >& vertexAttribInfoList, const PSPtr< PVBO >& vboIndices)
	{
		glGenVertexArrays(1, &vaoID_);

		bind();
		{
			for (const auto& vertex_attribute_information : vertexAttribInfoList)
			{
				vertex_attribute_information.vbo->bind();

				glEnableVertexAttribArray(vertex_attribute_information.index);

				glVertexAttribPointer
				(
					vertex_attribute_information.index,
					vertex_attribute_information.nComponents,
					vertex_attribute_information.componentType,
					GL_FALSE, /*Elements previously normalized*/
					0,
					0
				);

				vbos_.push_back(vertex_attribute_information.vbo);
			}

			if (vboIndices.get())
			{
				vboIndices->bind();
			}

			vbos_.push_back(vboIndices);

		} unbind();

		error_ = glGetError();
		assert(error_ == GL_NO_ERROR);
	}
}
