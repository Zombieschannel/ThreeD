#pragma once
#ifdef __ANDROID__

#define GLES31

#ifdef GLES20
#include <GLES2/gl2.h>
#endif

#ifdef GLES30
#include <GLES3/gl3.h>
#endif

#ifdef GLES31
#include <GLES3/gl31.h>
#endif

#ifdef GLES32
#include <GLES3/gl32.h>
#endif

#else

//#include <GL/glew.h>
#include <glad/glad.h>

#endif