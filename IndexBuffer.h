#pragma once
#include <vector>
namespace DDD
{
	class IndexBuffer3D
	{
    public:
        enum DrawType
        {
            Static = GL_STATIC_DRAW,
            Dynamic = GL_DYNAMIC_DRAW,
            Stream = GL_STREAM_DRAW,
        };
    private:
		std::vector<unsigned int> indices;
        DrawType drawType = DrawType::Dynamic;
        unsigned int ibo = 0;
        void CreateBuffer()
        {
            GLCall(glGenBuffers(1, &ibo));
        }
    public:
        IndexBuffer3D()
        {
            CreateBuffer();
        }
        IndexBuffer3D(int vertexCount)
        {
            CreateBuffer();
            indices.resize(vertexCount);
        }
        ~IndexBuffer3D()
        {
            GLCall(glDeleteBuffers(1, &ibo));
        }
        int getIndexCount() const
        {
            return indices.size();
        }
        unsigned int& operator [](int index)
        {
            return indices[index];
        }
        const unsigned int& operator [](int index) const
        {
            return indices[index];
        }
        void DeleteArray()
        {
            std::vector<unsigned int>().swap(indices);
        }
        void clear()
        {
            indices.clear();
        }
        void resize(int indexCount)
        {
            indices.resize(indexCount);
        }
        void append(unsigned int index)
        {
            indices.push_back(index);
        }
        void replace(const std::vector<unsigned int>& vec)
        {
            indices = vec;
        }
        void setDrawType(DrawType type)
        {
            drawType = type;
        }
        DrawType getDrawType() const
        {
            return drawType;
        }
        static void BufferData(const IndexBuffer3D& buffer)
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.ibo));
            GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.indices.size() * sizeof(unsigned int), buffer.indices.data(), buffer.drawType));
        }
        static void Bind(const IndexBuffer3D& buffer)
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.ibo));
        }
	};
}