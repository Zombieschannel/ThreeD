#pragma once
#include <SFML/Config.hpp>
#include <SFML/System/Err.hpp>
#include <iostream>
#include "OpenGL.hpp"

#ifndef NDEBUG
#define GLCall(x) DDD::GLClearError();\
	x;\
	DDD::GLLogCall()
#else
#define GLCall(x) x;
#endif

namespace DDD
{
	static void GLClearError()
	{
		for (short i = 0; i < INT16_MAX - 1 && (glGetError() != GL_NO_ERROR); i++);
	}
	static bool GLLogCall()
	{
		while (GLenum error = glGetError())
		{
			sf::err() << "Error: " << error << std::endl;
			sf::err() << "Hex: " << std::hex << error << std::endl;
			sf::err() << "Common errors: " << std::endl;
			sf::err() << "GL_INVALID_ENUM 0x0500" << std::endl;
			sf::err() << "GL_INVALID_VALUE 0x0501" << std::endl;
			sf::err() << "GL_INVALID_OPERATION 0x0502" << std::endl;
			sf::err() << "GL_STACK_OVERFLOW 0x0503" << std::endl;
			sf::err() << "GL_STACK_UNDERFLOW 0x0504" << std::endl;
			sf::err() << "GL_OUT_OF_MEMORY 0x0505" << std::endl;
			return false;
		}
		return true;
	}
}