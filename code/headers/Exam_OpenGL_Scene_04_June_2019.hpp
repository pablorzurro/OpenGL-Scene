/**
 * @file Exam_OpenGL_Scene_04_June_2019.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-06-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_EXAM_OPENGL_04_JUNE_2019_SCENE_H_
#define OPENGL_SCENE_EXAM_OPENGL_04_JUNE_2019_SCENE_H_

#include <Scene.hpp>

namespace prz
{

	class Exam_OpenGL_Scene_04_June_2019 : public Scene
	{
	public:

		Exam_OpenGL_Scene_04_June_2019(Window& window);

	public:

		void initialize() override;
		void update(float deltaTime) override;

	private:

	};

} // !namespace prz

#endif //! OPENGL_SCENE_EXAM_OPENGL_04_JUNE_2019_SCENE_H_
