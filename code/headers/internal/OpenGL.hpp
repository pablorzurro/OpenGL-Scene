/**
 * @file OpenGL.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 09-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_OPENGL_H_
#define OPENGL_SCENE_OPENGL_H_

#include <glad/glad.h>

#undef near
#undef far

    namespace prz
    {

        bool initialize_opengl_extensions ();

    }

#endif OPENGL_SCENE_OPENGL_H_
