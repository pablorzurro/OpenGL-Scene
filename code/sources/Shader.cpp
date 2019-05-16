#include <Shader.hpp>
#include <Source_Code.hpp>

namespace prz
{
	Shader::Shader(const Source_Code& sourceCode, const PString& name, Type type) :
		shaderObjID_(0),
		name_(name),
		type_(type)
	{
		if (sourceCode.is_not_empty())
		{
			// Create the shader object
			shaderObjID_ = glCreateShader(type);

			// Load the source code of the shader
			const char* shaderCodes[] = { sourceCode };
			const GLint shaderCodeSizes[] = { (GLint)sourceCode.size() };

			glShaderSource(shaderObjID_, 1, shaderCodes, shaderCodeSizes);

			// Compile the shader
			glCompileShader(shaderObjID_);

			// Check if the compilation has succeeded
			GLint succeeded = 0;

			glGetShaderiv(shaderObjID_, GL_COMPILE_STATUS, &succeeded);

			if (!succeeded)
			{
				// Save an state log of what happens
				GLint logLength;

				glGetShaderiv(shaderObjID_, GL_INFO_LOG_LENGTH, &logLength);

				if (logLength > 0)
				{
					logStr_.resize(logLength);

					glGetShaderInfoLog(shaderObjID_, logLength, NULL, &logStr_.front());
				}

				// Free the shader object that has been not compiled
				glDeleteShader(shaderObjID_);
				shaderObjID_ = 0;
				cout << "Shader loading failed, source code path: \"" + sourceCode.path() + "\"   Error: " + logStr_ ;
				assert(false);
			}
		}
		else
		{
			cout << "Shader loading failed, source code from path: \"" + sourceCode.path() + "\" was empty";
		}	
	}

	Shader::~Shader()
	{
		// Deleting a shader after add it to a shader program has no bad effects
		glDeleteShader(shaderObjID_);

		shaderObjID_ = 0;
	}

}
