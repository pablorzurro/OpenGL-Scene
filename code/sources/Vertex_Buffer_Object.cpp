#include <Vertex_Buffer_Object.hpp>

namespace prz
{
	void Vertex_Buffer_Object::create(const void* data, size_t size)
	{
		assert(data && size);

		glGenBuffers(1, &vboID_);

		bind();
		{
			glBufferData(target_, size, data, drawUsage_);

			error_ = glGetError();
			assert(error_ == GL_NO_ERROR);

		} unbind();
	}
}
