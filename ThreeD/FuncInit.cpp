#include "FuncInit.hpp"
#include <SFML/Window/Context.hpp>
#include "VertexArray.hpp"

#define THREED_GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"

namespace DDD
{
    void ThreeD::Init()
    {
        const TransientContextLock lock;

        ThreeD_gladLoadGL(sf::Context::getFunction);
    }
}
