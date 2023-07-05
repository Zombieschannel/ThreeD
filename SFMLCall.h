#pragma once
#include "OGL.h"
#include "Error.h"
#define SFMLCall(x) resetGLstates();\
x
void resetGLstates()
{
#ifndef GLES20
	GLCall(glBindVertexArray(0));
#endif
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glUseProgram(0));
}