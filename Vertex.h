#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "ColorF.h"
namespace DDD
{
	class Vertex3D
	{
		float position[3];
		float color[4];
		float texCoord[2];
		float normals[3];
		float texID;
	public:
		Vertex3D()
			: position{ 0, 0, 0 }, color{ 1, 1, 1, 1 }, texCoord{ 0, 0 }, normals{0, 0, 0}, texID(0)
		{
		}
		Vertex3D(const sf::Vector3f& pos)
			: position{ pos.x, pos.y, pos.z }, color{ 1, 1, 1, 1 }, texCoord{ 0, 0 }, normals{ 0, 0, 0 }, texID(0)
		{

		}
		
		Vertex3D(const sf::Vector3f& pos, const ColorF& col)
			: position{ pos.x, pos.y, pos.z }, color{ col.r, col.g, col.b, col.a }, normals{ 0, 0, 0 }, texCoord{ 0, 0 }, texID(0)
		{

		}
		Vertex3D(const sf::Vector3f& pos, const ColorF& col, const sf::Vector2f& tex)
			: position{ pos.x, pos.y, pos.z }, color{ col.r, col.g, col.b, col.a }, texCoord{ tex.x, tex.y }, normals{ 0, 0, 0 }, texID(0)
		{

		}
		Vertex3D(const sf::Vector3f& pos, const ColorF& col, const sf::Vector2f& tex, const sf::Vector3f& normal)
			: position{ pos.x, pos.y, pos.z }, color{ col.r, col.g, col.b, col.a }, texCoord{ tex.x, tex.y }, normals{ normal.x, normal.y, normal.z }, texID(0)
		{

		}
		Vertex3D(const sf::Vector3f& pos, const ColorF& col, const sf::Vector2f& tex, const sf::Vector3f& normal, const float& ID)
			: position{ pos.x, pos.y, pos.z }, color{ col.r, col.g, col.b, col.a }, texCoord{ tex.x, tex.y }, normals{ normal.x, normal.y, normal.z }, texID(ID)
		{

		}
		~Vertex3D()
		{

		}
		void setPosition(float x, float y, float z)
		{
			position[0] = x;
			position[1] = y;
			position[2] = z;
		}
		void setPosition(const sf::Vector3f& pos)
		{
			position[0] = pos.x;
			position[1] = pos.y;
			position[2] = pos.z;
		}
		void move(float x, float y, float z)
		{
			position[0] += x;
			position[1] += y;
			position[2] += z;
		}
		void move(const sf::Vector3f& pos)
		{
			position[0] += pos.x;
			position[1] += pos.y;
			position[2] += pos.z;
		}
		void setColor(const ColorF& col)
		{
			color[0] = col.r;
			color[1] = col.g;
			color[2] = col.b;
			color[3] = col.a;
		}
		void addColor(const ColorF& col)
		{
			color[0] += col.r;
			color[1] += col.g;
			color[2] += col.b;
			color[3] += col.a;
		}
		void setTexCoord(const float& x, const float& y)
		{
			texCoord[0] = x;
			texCoord[1] = y;
		}
		void setTexCoord(const sf::Vector2f& tex)
		{
			texCoord[0] = tex.x;
			texCoord[1] = tex.y;
		}
		void setNormal(const float& x, const float& y, const float& z)
		{
			normals[0] = x;
			normals[1] = y;
			normals[2] = z;
		}
		void setNormal(const sf::Vector3f& normal)
		{
			normals[0] = normal.x;
			normals[1] = normal.y;
			normals[2] = normal.z;
		}
		void setTexID(float ID)
		{
			texID = ID;
		}
		sf::Vector3f getPosition() const
		{
			return sf::Vector3f(position[0], position[1], position[2]);
		}
		ColorF getColor() const
		{
			return ColorF(color[0], color[1], color[2], color[3]);
		}
		sf::Vector2f getTexCoord() const
		{
			return sf::Vector2f(texCoord[0], texCoord[1]);
		}
		float getTexID() const
		{
			return texID;
		}
	};
}