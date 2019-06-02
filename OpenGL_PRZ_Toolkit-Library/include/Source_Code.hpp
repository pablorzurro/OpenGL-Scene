/**
 * @file Source_Code.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Class that store a text that represents code of any kind
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
	/**
	 * @brief Class that store a text that represents code of any kind
	 * 
	 */
	class Source_Code
	{
	public:

		/**
		 * @brief Construct a new Source_Code
		 * 
		 * @param path 
		 */
		Source_Code(const PString& path)
			:
			sourceCodeStr_(load_file_as_string(path)),
			path_(path)
		{}

	public:

		/**
		 * @brief Return the size of the string
		 * 
		 * @return size_t 
		 */
		size_t size() const { return (sourceCodeStr_.size()); }

		/**
		 * @brief Return if the string is empty
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_empty() const { return (sourceCodeStr_.empty()); }

		/**
		 * @brief Return if the string is not empty
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_not_empty() const { return (!sourceCodeStr_.empty()); } 

		/**
		 * @brief Return the origin path
		 * 
		 * @return const PString& 
		 */
		const PString& path() const { return path_; }; 

	public:
		
		/**
		 * @brief Operator to return the string
		 * 
		 * @return const PString& 
		 */
		operator const PString& () const
		{
			return (sourceCodeStr_);
		}

		/**
		 * @brief Operator to return the string as a char array
		 * 
		 * @return const char* 
		 */
		operator const char* () const
		{
			return (sourceCodeStr_.c_str());
		}

	public:

		/**
		 * @brief Return the string
		 * 
		 * @return const PString& 
		 */
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
