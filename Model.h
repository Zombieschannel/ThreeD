#pragma once
#include <vector>
#include "VertexArray.h"
#include <string>
namespace DDD
{
	class Model3D
	{
	private:
		VertexArray3D vao;
		friend class Mesh3D;
		VertexBuffer3D vbo;
		DDD::ColorF color = DDD::ColorF(1.f);
		void GetVector(sf::Vector3f& vec, const char* start, unsigned int size)
		{
			std::string tempString;
			int cnt = 0;
			for (int i = 0; i < size; i++)
			{
				if (*(start + i) == ' ')
				{
					tempString = "";
					i++;
					while (1)
					{
						if (*(start + i) == ' ' || *(start + i) == '\0')
							break;
						tempString += *(start + i);
						i++;
					}
					i--;
					if (cnt == 0)
						vec.x = std::stof(tempString);
					if (cnt == 1)
						vec.y = std::stof(tempString);
					if (cnt == 2)
					{
						vec.z = std::stof(tempString);
						cnt = 0;
						break;
					}
					cnt++;
				}
			}
		}
		sf::Vector3i getFV(const char* start, unsigned int size)
		{
			int arr[3] = {0, 0, 0};
			int cnt = 0;
			int num = 0;
			for (int i = 0; i <= size; i++)
			{
				if (*(start + i) == '/' || *(start + i) == ' ' || *(start + i) == '\0' || *(start + i) == '\n' || *(start + i) == '\r')
				{
					arr[num] = cnt;
					cnt = 0;
					num++;
				}
				else
				{
					if (cnt == 0)
						cnt = *(start + i) - 48;
					else
					{
						cnt *= 10;
						cnt += *(start + i) - 48;
					}
				}
			}
			return sf::Vector3i(arr[0], arr[1], arr[2]);
		}
		void getFace(std::vector<sf::Vector3i>& vec, const char* start, unsigned int size)
		{
			int cnt = 0;
			for (int i = 0; i <= size; i++)
			{
				if (*(start + i) == ' ' || *(start + i) == '\n' || *(start + i) == '\0' || *(start + i) == '\r')
				{
					sf::Vector3i t = getFV((start + i - cnt), cnt);
					//std::cout << t.x <<  " " << t.y << " " << t.z << std::endl;
					vec.push_back(t);
					cnt = 0;
				}
				else
					cnt++;
			}
		}
		void PerLine(const char* start, unsigned int size, bool scanMode, std::vector<sf::Vector3f>& pos1, std::vector<sf::Vector3f>& nor1, std::vector<sf::Vector2f>& tex1, int& posCnt, int& texCnt, int& norCnt, int& vboSize)
		{

			if (start[0] == 'v' && start[1] == ' ')
			{
				if (!scanMode)
				{
					sf::Vector3f pos;
					GetVector(pos, &start[1], size - 1);
					pos1[posCnt] = pos;
					//vbo[objectName][vertexCount] = Vertex3D(pos, color);
				}
				posCnt++;
			}
			if (start[0] == 'v' && start[1] == 'n')
			{
				if (!scanMode)
				{
					sf::Vector3f pos;
					GetVector(pos, &start[2], size - 2);
					nor1[norCnt] = pos;
					//vbo[objectName][vertexCount] = Vertex3D(pos, color);
				}
				norCnt++;
			}
			if (start[0] == 'v' && start[1] == 't')
			{
				if (!scanMode)
				{
					sf::Vector3f pos;
					GetVector(pos, &start[2], size - 2);
					tex1[texCnt] = sf::Vector2f(pos.x, pos.y);
					//vbo[objectName][vertexCount] = Vertex3D(pos, color);
				}
				texCnt++;
			}
			else if (start[0] == 'f' && start[1] == ' ')
			{
				
				if (!scanMode)
				{
					std::vector<sf::Vector3i> ind;
					getFace(ind, &start[2], size - 2);
					int count = 0;
					for (int i = 0; i < ind.size() - 2; i++)
					{
						float random = (float)rand() / RAND_MAX / 2;
						color = DDD::ColorF(random + 0.5);
						vbo[vboSize + count] = Vertex3D(pos1[ind[0].x - 1], color, tex1.size() != 0 ? tex1[ind[0].y - 1] : sf::Vector2f(0, 0), nor1.size() != 0 ? nor1[ind[0].z - 1] : sf::Vector3f(0, 0, 0));
						count++;
						vbo[vboSize + count] = Vertex3D(pos1[ind[i + 1].x - 1], color, tex1.size() != 0 ? tex1[ind[i + 1].y - 1] : sf::Vector2f(0, 0), nor1.size() != 0 ? nor1[ind[i + 1].z - 1] : sf::Vector3f(0, 0, 0));
						count++;
						vbo[vboSize + count] = Vertex3D(pos1[ind[i + 2].x - 1], color, tex1.size() != 0 ? tex1[ind[i + 2].y - 1] : sf::Vector2f(0, 0), nor1.size() != 0 ? nor1[ind[i + 2].z - 1] : sf::Vector3f(0, 0, 0));
						count++;
					}
				}
				vboSize += 3 * ((std::count(start, (start + size), '/') / 2) - 2);
			}
			/*else if (start[0] == 'o' && start[1] == ' ')
			{
				
				if (objectName != "" && scanMode)
				{
					vbo[objectName].resize(vboSize);
					vao[objectName];
					std::cout << "Object " << objectName << " has " << vboSize << " vertices" << std::endl;

				}
				objectName.clear();
				objectName.append((start + 2), size - 2);
					
			}*/
			
		}
	public:
		
		bool loadFromStream(sf::InputStream& load1)
		{
			/*std::ifstream load1;
			std::ifstream load2;
			std::string file;
			int triangleCNT = 0;
			int vertexCNT = 0;
			int normalCNT = 0;
			int textureCNT = 0;
			int materialCNT = 0;
			int objectCNT = 0;
			load1.open(filename);
			load2.open(filename);
			if (load2.is_open())
			{
				while (getline(load2, file))
				{
					if (file[0] == 'v' && file[1] == ' ')
						vertexCNT++;
					if (file[0] == 'v' && file[1] == 't')
						textureCNT++;
					if (file[0] == 'f' && file[1] == ' ')
					{
						int slashCNT = count(file.begin(), file.end(), '/');
						if (slashCNT == 6)
							triangleCNT++;
						if (slashCNT == 8)
							quadCNT++;
					}
					if (file[0] == 'v' && file[1] == 'n')
						normalCNT++;
					if (file[0] == 'u' && file[1] == 's' && file[2] == 'e' && file[3] == 'm')
					{
						string temp = "";
						bool active = 0;
						for (int i = 7; i < file.size(); i++)
							temp += file[i];
						for (int i = 0; i < materials.size(); i++)
							if (materialNames[i] == temp)
							{
								active = 1;
								break;
							}
						if (!active)
						{
							materialCNT++;
							materialNames.push_back(temp);
						}
					}
					if (file[0] == 'o' && file[1] == ' ')
						objectCNT++;
				}
				shading.resize(objectCNT, 0);
				objects.resize(objectCNT);
				for (int i = 0; i < objectCNT; i++)
					objects[i].resize(triangleCNT, quadCNT);
				materials.resize(materialCNT);
				if (materialCNT == 0)
					materials.resize(1);

				Vector3f* vertices = new Vector3f[vertexCNT];
				Vector3f* normals = new Vector3f[normalCNT];
				Vector2f* textures = new Vector2f[textureCNT];
				vertexCNT = 0;
				normalCNT = 0;
				triangleCNT = 0;
				textureCNT = 0;
				quadCNT = 0;
				materialCNT = 0;
				objectCNT = -1;
				while (getline(load1, file))
				{
					if (file[0] == 'v' && file[1] == ' ')
					{
						GetVector(vertices[vertexCNT], file);
						vertexCNT++;
					}
					else if (file[0] == 'v' && file[1] == 'n')
					{
						GetVector(normals[normalCNT], file);
						normalCNT++;
					}
					else if (file[0] == 'v' && file[1] == 't')
					{
						GetVector(textures[textureCNT], file);
						textureCNT++;
					}
					else if (file[0] == 'f' && file[1] == ' ')
					{
						objects[objectCNT].GetFace(vertices, file, triangleCNT, normals, quadCNT, textures);
					}
					else if (file[0] == 'o' && file[1] == ' ')
						objectCNT++;
					else if (file[0] == 's' && file[1] == ' ')
					{
						if (file[2] == '1')
							shading[objectCNT] = 1;
						else if (file[2] == 'o')
							shading[objectCNT] == 0;
					}
					else if (file[0] == 'u' && file[1] == 's' && file[2] == 'e')
					{
						string temp = "";
						for (int i = 7; i < file.size(); i++)
							temp += file[i];
						for (int i = 0; i < materials.size(); i++)
							if (materialNames[i] == temp)
							{
								objects[objectCNT].currentMaterial = &materials[i];
								break;
							}
					}

				}

				delete[] vertices;
				delete[] normals;
				delete[] textures;
				load1.close();
				load2.close();
			}
			else
			{
				cout << "Unable to open model: " << filename << endl;
				return 0;
			}

			return 1;
		}*/
			std::string file;
			std::vector<sf::Vector3f> pos;
			std::vector<sf::Vector3f> nor;
			std::vector<sf::Vector2f> tex;
			vbo.clear();
			int vboSize = 0;
			int posCnt = 0;
			int norCnt = 0;
			int texCnt = 0;
			file.resize(load1.getSize());
			load1.read(&file[0], load1.getSize());
			unsigned int start = 0;
			for (int i = 0; i < file.size(); i++)
			{
				if (file[i] == '\n' || file[i] == '\0' || file[i] == '\r')
				{
					PerLine(&file[start], i - start, 1, pos, nor, tex, posCnt, texCnt, norCnt, vboSize);
					i++;
					start = i;
				}
			}
			pos.resize(posCnt);
			nor.resize(norCnt);
			tex.resize(texCnt);
			vbo.resize(vboSize);
			//std::cout << "Object " << " has " << vboSize << " vertices" << std::endl;
			start = 0;

			vboSize = 0;
			posCnt = 0;
			norCnt = 0;
			texCnt = 0;
			for (int i = 0; i < file.size(); i++)
			{
				if (file[i] == '\n' || file[i] == '\0' || file[i] == '\r')
				{
					PerLine(&file[start], i - start, 0, pos, nor, tex, posCnt, texCnt, norCnt, vboSize);
					i++;
					start = i;
				}
			}
			vao.setVBO(vbo);
			return 1;
		}
		void setColor(const DDD::ColorF& color)
		{
			this->color = color;
			for (int i = 0; i < vbo.getVertexCount(); i++)
				vbo[i].setColor(color);
			vao.setVBO(vbo);
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
		const DDD::VertexArray3D& getVertexArray() const
		{
			return vao;
		}
		DDD::VBO& getVertexBuffer()
		{
			return vbo;
		}
	};
}