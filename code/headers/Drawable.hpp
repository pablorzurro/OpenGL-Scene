/**
 * @file Drawable.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Abstract class that will be the base of all drawable objects
 * @version 0.1
 * @date 10-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_DRAWABLE_H_
#define OPENGL_SCENE_DRAWABLE_H_

#include <Declarations.hpp>

namespace prz
{
	class Camera;

	/**
	 * @brief Abstract class that will be the base of all drawable objects
	 * 
	 */
	class Drawable
	{
	public:

		/**
		 * @brief Destroy the Drawable
		 * 
		 */
		virtual ~Drawable() = default;

 	public:

		/**
		 * @brief Draw this object
		 * 
		 */
		virtual void draw() = 0;

		/**
		 * @brief Draw this object
		 * 
		 * @param camera 
		 */
		virtual void draw(PSPtr< Camera > camera){}

	};
}

#endif
