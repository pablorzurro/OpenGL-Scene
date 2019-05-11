#include "Shader.hpp"
#include "Source_Code.hpp"

namespace prz
{
	Shader::Shader(const Source_Code& sourceCode, GLenum shaderType)
		:
		shaderObjID_(0)
	{
		if (sourceCode.is_not_empty())
		{
			// Se crea el shader object:

			shaderObjID_ = glCreateShader(shaderType);

			// Se carga el código del shader:

			const char* shaderCodes[] = { sourceCode };
			const GLint  shaderCodeSizes[] = { (GLint)sourceCode.size() };

			glShaderSource(shaderObjID_, 1, shaderCodes, shaderCodeSizes);

			// Se compila el shader:

			glCompileShader(shaderObjID_);

			// Se comprueba si la compilación ha tenido éxito:

			GLint succeeded = 0;

			glGetShaderiv(shaderObjID_, GL_COMPILE_STATUS, &succeeded);

			if (!succeeded)
			{
				// Se guarda el log del error que ha ocurrido:

				GLint logLength;

				glGetShaderiv(shaderObjID_, GL_INFO_LOG_LENGTH, &logLength);

				if (logLength > 0)
				{
					logStr_.resize(logLength);

					glGetShaderInfoLog(shaderObjID_, logLength, NULL, &logStr_.front());
				}

				// Se libera el shader object, ya que ahora es un recurso encapsulado no usable:

				glDeleteShader(shaderObjID_);

				shaderObjID_ = 0;

				assert(false);
			}
		}
		else
			assert(false);
	}

	Shader::~Shader()
	{
		// Borrar un shader cuando se ha añadido a un shader program no tiene efectos adversos:

		glDeleteShader(shaderObjID_);

		shaderObjID_ = 0;
	}

}