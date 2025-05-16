#pragma once
#include <SFML/Config.hpp>
#if defined(SFML_SYSTEM_ANDROID) || defined(SFML_SYSTEM_IOS) || defined(SFML_SYSTEM_EMSCRIPTEN)

#if defined(GLES30)
#include <GLES3/gl3.h>
#elif defined(GLES31)
#include <GLES3/gl31.h>
#elif defined(GLES32)
#include <GLES3/gl32.h>
#else
#define GLES20
#include <GLES2/gl2.h>
#endif
#else
#include <glad/glad.h>
#endif
