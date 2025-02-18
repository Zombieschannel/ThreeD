#pragma once
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>
#include "Vertex.hpp"
#include "Error.hpp"
#include "DrawType.hpp"

namespace DDD
{
    template<typename T>
    class VertexBuffer3D
    {
    private:
        std::vector<T> vertices;
        DrawType drawType = DrawType::Dynamic;
        std::uint32_t ID;
    public:
        VertexBuffer3D();
        VertexBuffer3D(sf::PrimitiveType type, std::uint32_t vertexCount = 0);
        ~VertexBuffer3D();

        std::uint32_t getHandle() const;
        const void* getFirstVertex() const;
        std::uint32_t getVertexCount() const;
        std::uint32_t getVertexSize() const;
        T& operator[] (std::uint32_t index);
        void clear();
        void resize(const std::uint32_t vertexCount);
        void append(const T& vertex);
        void setDrawType(DrawType type);
        const T& at(std::uint32_t index) const;
        const DrawType getDrawType() const;
        void setLayout(const std::vector<std::uint32_t>& attribLocation) const;
        void Update();
    };
    template <typename T>
    void BindVertexBuffer(const VertexBuffer3D<T>* buffer);
}

#include "VertexBuffer.inl"