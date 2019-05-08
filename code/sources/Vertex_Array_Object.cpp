#include "Vertex_Array_Object.hpp"

namespace prz
{
	Vertex_Array_Object::Vertex_Array_Object(const std::initializer_list< PVAI >& vertexAttribInfoList, const PSPtr< PVBO >& vboIndices = PSPtr< PVBO >())
	{
		glGenVertexArrays(1, &id_);

		bind();
		{
			for (const auto& vertex_attribute_information : vertexAttribInfoList)
			{
				vertex_attribute_information.vbo->bind();

				glEnableVertexAttribArray(vertex_attribute_information.attribLocation);

				glVertexAttribPointer
				(
					vertex_attribute_information.attribLocation,
					vertex_attribute_information.nComponents,
					vertex_attribute_information.componentType,
					GL_FALSE,
					0,
					0
				);

				vboList_.push_back(vertex_attribute_information.vbo);
			}

			if (vboIndices.get())
			{
				vboIndices->bind();
			}

			vboList_.push_back(vboIndices);

		} unbind();

		error_ = glGetError();
		assert(error_ == GL_NO_ERROR);
	}
}