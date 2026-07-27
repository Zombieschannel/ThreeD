#include "FuncInit.hpp"
#include <SFML/Window/Context.hpp>
#include <SFML/System/Err.hpp>
#include <iostream>

#define THREED_GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"

namespace DDD
{
    void ThreeD::Init()
    {
        const TransientContextLock lock;

        if (!ThreeD_gladLoadGL(sf::Context::getFunction))
            sf::err() << "Failed to load ThreeD" << std::endl;
    }
}
