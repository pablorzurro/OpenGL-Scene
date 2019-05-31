/**
 * @file Demo_Scene_01.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Scene example 1
 * @version 0.1
 * @date 30-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DEMO_SCENE_01_H_ 
#define OPENGL_SCENE_DEMO_SCENE_01_H_

#include <Scene.hpp>

namespace prz
{

	/**
	 * @brief Scene example 1
	 * 
	 */
	class Demo_Scene_01 : public Scene
	{
	public:

		/**
		 * @brief Construct a new Demo_Scene_01
		 * 
		 * @param window 
		 */
		Demo_Scene_01(Window& window);

	public:

		void initialize() override;

		virtual void update(float deltaTime);
		
	};
}

#endif // !OPENGL_SCENE_DEMO_SCENE_01_H_