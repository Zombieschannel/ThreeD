#pragma once
#include "OGL.h"
#include <SFML/System/Err.hpp>
#include <iostream>
#ifdef __ANDROID__
#define ASSERT(x) x;
#else
#define ASSERT(x) x;
//#define ASSERT(x) if (!(x)) __debugbreak();
#endif

#ifndef NDEBUG
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall())
#else
#define GLCall(x) x;
#endif



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