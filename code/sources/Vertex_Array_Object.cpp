#include <Vertex_Array_Object.hpp>
#include <Vertex_Buffer_Object.hpp>
#include <Vertex_Attribute_Information.hpp>

namespace prz
{
	Vertex_Array_Object::Vertex_Array_Object(const PList< PVAI >& vertexAttribInfoList, const PSPtr< PVBO >& vboIndices)
	{
		glGenVertexArrays(1, &vaoID_);

		bind();
		{
			for (const auto& vai : vertexAttribInfoList)
			{
				vai.vbo->bind();
				{
					glEnableVertexAttribArray(vai.index);
					{
						glVertexAttribPointer
						(
							vai.index,
							vai.nComponents,
							vai.componentType,
							GL_FALSE, /*Elements should be previously normalized*/
							0,
							0
						);

					}/* glDisableVertexAttribArray(vai.index);*/

				} /*vai.vbo->unbind();*/
				
				vbos_.push_back(vai.vbo);
			}

			if (vboIndices.get())
			{
				vboIndices->bind();
				{
				} /*vboIndices->unbind();*/
			}

			vbos_.push_back(vboIndices);

		} unbind();

		error_ = glGetError();
		assert(error_ == GL_NO_ERROR);
	}
}
