#pragma once
#if __ANDROID__

#define GLES20

#if defined (GLES20)
#include <GLES2/gl2.h>
#endif

#if defined(GLES30)
#include <GLES3/gl3.h>
#endif

#if defined(GLES31)
#include <GLES3/gl31.h>
#endif

#if defined(GLES32)
#include <GLES3/gl32.h>
#endif

#else
#include <GL/glew.h>
#endif