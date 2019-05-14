/**
 * @file Source_Code.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_SOURCE_CODE_H_
#define OPENGL_SCENE_SOURCE_CODE_H_

#include <Declarations.hpp>

namespace prz
{
	class Source_Code
	{
	public:

		Source_Code(const PString& sourceCodeStr)
			:
			sourceCodeStr_(sourceCodeStr)
		{}

	public:

		size_t size() const { return (sourceCodeStr_.size()); }
		bool is_empty() const { return (sourceCodeStr_.empty()); }
		bool is_not_empty() const { return (!sourceCodeStr_.empty()); }

	public:

		operator const PString& () const
		{
			return (sourceCodeStr_);
		}

		operator const char* () const
		{
			return (sourceCodeStr_.c_str());
		}

	private:

		PString sourceCodeStr_;
	};
}
#endif // !OPENGL_SCENE_SOURCE_CODE_H_



