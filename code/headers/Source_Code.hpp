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
#include <Utilities.hpp>

namespace prz
{
	class Source_Code
	{
	public:

		Source_Code(const PString& path)
			:
			sourceCodeStr_(load_file_as_string(path)),
			path_(path)
		{}

	public:

		size_t size() const { return (sourceCodeStr_.size()); }
		bool is_empty() const { return (sourceCodeStr_.empty()); }
		bool is_not_empty() const { return (!sourceCodeStr_.empty()); } 

		const PString& path() const { return path_; }; 

	public:

		operator const PString& () const
		{
			return (sourceCodeStr_);
		}

		operator const char* () const
		{
			return (sourceCodeStr_.c_str());
		}

	public:

		const PString& to_string()
		{
			return sourceCodeStr_;
		}

	private:

		PString sourceCodeStr_;
		PString path_;
	};

} // !namespace prz

#endif // !OPENGL_SCENE_SOURCE_CODE_H_
