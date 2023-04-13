#pragma once
#include "ColorF.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
namespace DDD
{
	class Material3D
	{
		ColorF ambient;
		ColorF diffuse;
		ColorF specular;
		ColorF emission;
		int Ns;
		void getVec3(sf::Vector3f& vec, const std::string& tmp)
		{
			sf::Vector3i offset;
			offset.x = tmp.find(' ', 3);
			offset.y = tmp.find(' ', offset.x + 1);
			offset.z = tmp.find('\n', offset.y + 1);
			if (offset.z == tmp.npos)
				offset.z = tmp.find('\0', offset.y + 1);
			offset.z -= offset.y;
			offset.y -= offset.x;
			offset.x -= 2;
			vec.x = stof(tmp.substr(3, offset.x));
			vec.y = stof(tmp.substr(3 + offset.x, offset.y));
			vec.z = stof(tmp.substr(3 + offset.x + offset.y, offset.z));
		}
	public:
		Material3D()
			: ambient(0.f, 0.f, 0.f, 1.f), diffuse(0.f, 0.f, 0.f, 1.f), specular(0.f, 0.f, 0.f, 1.f), emission(0.f, 0.f, 0.f), Ns(0.f)
		{

		}
		Material3D(const ColorF& ambient, const ColorF& diffuse, const ColorF& specular, const ColorF& emission, int highlights)
			: ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), Ns(highlights)
		{

		}
		const ColorF& getAmbient() const
		{
			return ambient;
		}
		const ColorF& getDiffuse() const
		{
			return diffuse;
		}
		const ColorF& getSpecular() const
		{
			return specular;
		}
		const ColorF& getEmission() const
		{
			return emission;
		}
		const int& getHighlights() const
		{
			return Ns;
		}
		void setAmbient(const ColorF& col)
		{
			ambient = col;
		}
		void setDiffuse(const ColorF& col)
		{
			diffuse = col;
		}
		void setSpecular(const ColorF& col)
		{
			specular = col;
		}
		void setEmission(const ColorF& col)
		{
			emission = col;
		}
		void setHighlights(int highlight)
		{
			Ns = highlight;
		}
		bool loadFromStream(sf::InputStream& stream)
		{
			std::string tmp;
			bool break1 = 0;
			while (1)
			{
				while (1)
				{
					char x;
					stream.read(&x, 1);
					tmp += x;
					if (x == '\0' || stream.getSize() == stream.tell())
						break1 = 1;
					if (x == '\n' || x == '\0' || stream.getSize() == stream.tell())
						break;
				}
				if (tmp[0] == 'K' && tmp[1] == 'a')
				{
					sf::Vector3f vec;
					getVec3(vec, tmp);
					ambient = ColorF(vec.x, vec.y, vec.z, 1.f);
				}
				if (tmp[0] == 'K' && tmp[1] == 'd')
				{
					sf::Vector3f vec;
					getVec3(vec, tmp);
					diffuse = ColorF(vec.x, vec.y, vec.z, 1.f);
				}
				if (tmp[0] == 'K' && tmp[1] == 's')
				{
					sf::Vector3f vec;
					getVec3(vec, tmp);
					specular = ColorF(vec.x, vec.y, vec.z, 1.f);
				}
				if (tmp[0] == 'K' && tmp[1] == 'e')
				{
					sf::Vector3f vec;
					getVec3(vec, tmp);
					emission = ColorF(vec.x, vec.y, vec.z, 1.f);
				}
				if (tmp[0] == 'N' && tmp[1] == 's')
				{
					int x;
					x = tmp.find(' ', 3);
					x -= 2;
					Ns = stof(tmp.substr(3, x));
				}
				tmp = "";
				if (break1)
					break;
			}
			return 1;
		}
		bool loadFromFile(const std::string& filename)
		{
			sf::FileInputStream load1;
			if (!load1.open(filename))
				return 0;
			return loadFromStream(load1);
		}
		bool loadFromMemory(const std::string& file)
		{
			sf::MemoryInputStream load1;
			load1.open(file.c_str(), file.size());
			return loadFromStream(load1);
		}
	};
}