/**
 * @file Drawable.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 10-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_DRAWABLE_H_
#define OPENGL_SCENE_DRAWABLE_H_

namespace prz
{
	class Drawable
	{
	public:

		virtual ~Drawable() = default;
		virtual void draw() = 0;

	};
}

#endif
