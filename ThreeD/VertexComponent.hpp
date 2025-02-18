#pragma once
#include "OpenGL.hpp"

namespace DDD
{
    enum class Component
    {
        Byte = GL_BYTE,
        UByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UShort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        Uint = GL_UNSIGNED_INT,
        Float = GL_FLOAT
    };
}