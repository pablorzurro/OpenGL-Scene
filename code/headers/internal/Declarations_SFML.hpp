/**
 * @file Declarations_SFML.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_DECLARATIONS_SFML_H_
#define OPENGL_SCENE_DECLARATIONS_SFML_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace prz
{
	using PKey = sf::Keyboard::Key;

	enum WindowStyle : sf::Uint32
	{
		NO_STYLE = sf::Style::None,
		TITLEBAR = sf::Style::Titlebar,
		RESIZE = sf::Style::Resize,
		CLOSE = sf::Style::Close,
		FULLSCREEN = sf::Style::Fullscreen,
		DEFAULT = sf::Style::Default
	};

	using PImage = sf::Image;

} // !namespace prz

#endif // !OPENGL_SCENE_DECLARATIONS_SFML_H_
