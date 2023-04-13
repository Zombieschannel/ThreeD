#pragma once
#include "Vertex.h"
#include <vector>
#include "Error.h"
#include "LayoutBuffer.h"
namespace DDD
{
    class VBO
    {
    public:
        enum DrawType
        {
            Static = GL_STATIC_DRAW,
            Dynamic = GL_DYNAMIC_DRAW,
            Stream = GL_STREAM_DRAW,
        };
    protected:
        DrawType drawType = DrawType::Dynamic;
        unsigned int ID = 0;
        void setBuffer()
        {
            if (ID)
            {
                GLCall(glDeleteBuffers(1, &ID));
            }
            GLCall(glGenBuffers(1, &ID));
        }
        VBO()
        {
        }
        VBO(sf::PrimitiveType type)
        {
        }
        virtual const void* getFirstVertex() const = 0;
    public:
        

        virtual ~VBO()
        {
            
        }
        virtual unsigned int getVertexCount() const = 0;
        virtual unsigned int getVertexSize() const = 0;
        virtual void clear() = 0;
        virtual void resize(unsigned int vertexCount) = 0;
        virtual void setLayout() const = 0;
        void setDrawType(DrawType type)
        {
            drawType = type;
        }
        DrawType getDrawType() const
        {
            return drawType;
        }
        static void BufferData(const VBO& buffer)
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer.ID));
            GLCall(glBufferData(GL_ARRAY_BUFFER, buffer.getVertexCount() * buffer.getVertexSize(), buffer.getFirstVertex(), buffer.drawType));
        }
        static void Bind(const VBO& buffer)
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer.ID));
        }
    };
    class VertexBuffer3D : public VBO
    {
        std::vector<Vertex3D> vertices;
    public:
        VertexBuffer3D()
        {
            setBuffer();
        }
        VertexBuffer3D(sf::PrimitiveType type, int vertexCount = 0)
        {
            setBuffer();
            vertices.resize(vertexCount);
        }
        ~VertexBuffer3D()
        {
            if (ID)
            {
                GLCall(glDeleteBuffers(1, &ID));
            }
        }
        virtual const void* getFirstVertex() const
        {
            return &vertices[0];
        }
        virtual unsigned int getVertexCount() const
        {
            return vertices.size();
        }
        virtual unsigned int getVertexSize() const
        {
            return sizeof(Vertex3D);
        }
        virtual Vertex3D& operator[] (int index)
        {
            return vertices[index];
        }
        virtual const Vertex3D& operator[] (int index) const
        {
            return vertices[index];
        }
        virtual void clear()
        {
            vertices.clear();
        }
        virtual void resize(unsigned int vertexCount)
        {
            vertices.resize(vertexCount);
        }
        void append(const Vertex3D& vertex)
        {
            vertices.push_back(vertex);
        }
        virtual void setLayout() const
        {
            LayoutBuffer3D::Bind(0, 3, getVertexSize(), 0);
            LayoutBuffer3D::Bind(1, 4, getVertexSize(), sizeof(float) * 3);
            LayoutBuffer3D::Bind(2, 2, getVertexSize(), sizeof(float) * 4 + sizeof(float) * 3);
            LayoutBuffer3D::Bind(3, 3, getVertexSize(), sizeof(float) * 4 + sizeof(float) * 3 + sizeof(float) * 2);
        }

    };
    class CustomVertexBuffer3D : public VBO
    {
    public:
        enum Layout
        {
            Position = 1 << 0,
            Color = 1 << 1,
            TexCoord = 1 << 2,
            Normals = 1 << 3,
            Custom1 = 1 << 4,
            Custom2 = 1 << 5,
            Custom3 = 1 << 6,
            Custom4 = 1 << 7,
        };
    private:
        std::vector<float> vertices;
        unsigned int vertexCount;
        unsigned char vertexSize;
        unsigned char layoutFlags;
    public:
        CustomVertexBuffer3D()
            : layoutFlags(Position), vertexCount(0), vertexSize(getComponentSize(Position))
        {
            setBuffer();
        }
        CustomVertexBuffer3D(sf::PrimitiveType type)
            : layoutFlags(Position), vertexCount(0), vertexSize(getComponentSize(Position))
        {
            setBuffer();
        }
        ~CustomVertexBuffer3D()
        {
            if (ID)
            {
                GLCall(glDeleteBuffers(1, &ID));
            }
        }

        virtual const void* getFirstVertex() const
        {
            return &vertices[0];
        }
        virtual unsigned int getVertexCount() const
        {
            return vertices.size() / getVertexSize();
        }
        virtual unsigned int getVertexSize() const
        {
            return vertexSize;
        }
        virtual float& operator[] (int index)
        {
            return vertices[index * getVertexSize()];
        }
        virtual const float& operator[] (int index) const
        {
            return vertices[index * getVertexSize()];
        }
        virtual void clear()
        {
            vertices.clear();
        }
        virtual void resize(unsigned int vertexCount)
        {
            this->vertexCount = vertexCount;
            vertices.resize(vertexCount * getVertexSize());
        }
        unsigned char getComponentSize(Layout layout) const
        {
            switch (layout)
            {
            case DDD::CustomVertexBuffer3D::Position:
                return 3;
            case DDD::CustomVertexBuffer3D::Color:
                return 4;
            case DDD::CustomVertexBuffer3D::TexCoord:
                return 2;
            case DDD::CustomVertexBuffer3D::Normals:
                return 3;
            case DDD::CustomVertexBuffer3D::Custom1:
                return 1;
            case DDD::CustomVertexBuffer3D::Custom2:
                return 2;
            case DDD::CustomVertexBuffer3D::Custom3:
                return 3;
            case DDD::CustomVertexBuffer3D::Custom4:
                return 4;
            default:
                break;
            }
        }
        unsigned char getComponentSize(unsigned char component) const
        {
            switch (component)
            {
            case 0:
                return 3;
            case 1:
                return 4;
            case 2:
                return 2;
            case 3:
                return 3;
            case 4:
                return 1;
            case 5:
                return 2;
            case 6:
                return 3;
            case 7:
                return 4;
            default:
                break;
            }
        }
        void setLayoutFlags(unsigned int flags = Position | Color | TexCoord | Normals)
        {
            if (layoutFlags != flags)
            {
                layoutFlags = flags;
                vertexSize = 0;
                for (int i = 0; i < 8; i++)
                {
                    if (layoutFlags & (1 << i))
                        vertexSize += getComponentSize(i);
                }
                resize(vertexCount);
            }
        }
        virtual void setLayout() const
        {
            unsigned char offset;
            for (int i = 0; i < 8; i++)
            {
                if (layoutFlags & (1 << i))
                {
                    LayoutBuffer3D::Bind(i, getComponentSize(i), getVertexSize(), offset * sizeof(float));
                    offset += getComponentSize(i);
                }
            }
        }
    };
}