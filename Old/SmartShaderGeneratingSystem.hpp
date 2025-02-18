#pragma once
#include <iostream>
#include <string>
class SFSGS
{
	const std::string pointLight1 =
		R"(
struct PointLight
{
    vec4 col;
	float quadratic;
	float linear;
	vec3 pos;
};
		)";
	const std::string pointLight2 =
		R"(
const int TotalPointLights = __;
uniform PointLight pointLights[TotalPointLights];
		)";
	const std::string pointLight3 =
		R"(
vec4 CalcPointLight(int ID)
{
    vec3 lightVec = pointLights[ID].pos - v_pos;
    float dist = length(lightVec);
    float a = pointLights[ID].quadratic;
    float b = pointLights[ID].linear;
    float inten = 1.0 / (a * dist * dist + b * dist + 1.0);

    //diffuse
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0);
    
    //specular
    vec3 viewDirection = normalize(camPos - v_pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), _1);
	_0

    return pointLights[ID].col * (_3 inten * diffuse) + texColorSpec * specAmount * inten _4;
}
		)";
	const std::string directLight1 =
		R"(
struct DirectionalLight
{
    vec4 col;
	vec3 dir;
};
		)";
	const std::string directLight2 =
		R"(
const int TotalDirectionalLights = __;
uniform DirectionalLight directionalLights[TotalDirectionalLights];
		)";
	const std::string directLight3 =
		R"(
vec4 CalcDirectionalLight(int ID)
{

    //diffuse
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(-directionalLights[ID].dir);
    float diffuse = max(dot(normal, lightDirection), 0.0);
    
    //specular
    vec3 viewDirection = normalize(camPos - v_pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), _1);
    _0

    return directionalLights[ID].col * (_3 diffuse) + texColorSpec * specAmount _4;
}
		)";
	const std::string spotLight1 =
		R"(
struct SpotLight
{
    vec4 col;
	float quadratic;
	float linear;
	float outer;
	float inner;
	vec3 dir;
	vec3 pos;
};
		)";
	const std::string spotLight2 =
		R"(
const int TotalSpotLights = __;
uniform SpotLight spotLights[TotalSpotLights];
		)";
	const std::string spotLight3 =
		R"(
vec4 CalcSpotLight(int ID)
{
    float outerCone = spotLights[ID].outer;
    float innerCone = spotLights[ID].inner;

    //intensity
    vec3 lightVec = spotLights[ID].pos - v_pos;
    float dist = length(lightVec);
    float a = spotLights[ID].quadratic;
    float b = spotLights[ID].linear;
    float intensity = 1.0 / (a * dist * dist + b * dist + 1.0);


    //diffuse
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(spotLights[ID].pos - v_pos);
    float diffuse = max(dot(normal, lightDirection), 0.0);
    
    //specular
    vec3 viewDirection = normalize(camPos - v_pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), _1);
	_0

    float angle = dot(spotLights[ID].dir, -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0) * intensity;

    return spotLights[ID].col * (_3 diffuse * inten) + texColorSpec * inten * specAmount _4;
}
		)";
	const std::string materials =
		R"(
uniform vec4 m_ambient;
uniform vec4 m_diffuse;
uniform vec4 m_specular;
uniform vec4 m_emission;
uniform int m_highlights;
		)";
	const std::string lights =
		R"(
vec4 Lights()
{
    vec4 light = vec4(0.0, 0.0, 0.0, 0.0);
    _0_1_2
    return light;
}
		)";
	const std::string textures =
		R"(
uniform sampler2D u_textures[__];
		)";
	const std::string camPos =
		R"(
uniform vec3 camPos;
		)";
	const std::string inOut =
		R"(
layout(location = 0) out vec4 color;
in vec4 v_color;
in vec2 v_tex;
in vec3 v_normal;
in vec3 v_pos;
		)";
	// 0 - def inout
	// 1 - textures
	// 2 - material
	// 3 - point
	// 4 - dir
	// 5 - spot
	// 6 - specular
	// 7 - tex
	//
	unsigned char flags;
	unsigned short point;
	unsigned short dir;
	unsigned short spot;
	unsigned char tex;
	unsigned char texUse;
	unsigned char specMap;
	std::string endCode;
public:
	SFSGS()
		: flags(0), point(0), dir(0), spot(0), endCode(""), tex(0), specMap(0), texUse(0)
	{

	}
	static SFSGS& Begin(const std::string& version)
	{
		static SFSGS instance;
		instance.flags = 0;
		instance.point = 0;
		instance.dir = 0;
		instance.spot = 0;
		instance.tex = 0;
		instance.specMap = 0;
		instance.texUse = 0;
		instance.endCode = version + '\n';
		return instance;
	}
	SFSGS& DefaultInOut()
	{
		flags |= (1 << 0);
		return *this;
	}
	SFSGS& Textures(unsigned char count, char useTextureID = -1)
	{
		if (count == 0)
			return *this;
		flags |= (1 << 1);
		tex = count;
		if (useTextureID >= 0)
		{
			texUse = useTextureID;
			flags |= (1 << 7);
		}
		return *this;
	}
	SFSGS& Material()
	{
		flags |= (1 << 2);
		return *this;
	}
	SFSGS& PointL(unsigned short count)
	{
		if (count == 0)
			return *this;
		flags |= (1 << 3);
		point = count;
		return *this;
	}
	SFSGS& DirectL(unsigned short count)
	{
		if (count == 0)
			return *this;
		flags |= (1 << 4);
		dir = count;
		return *this;
	}
	SFSGS& SpotL(unsigned short count)
	{
		if (count == 0)
			return *this;
		flags |= (1 << 5);
		spot = count;
		return *this;
	}
	SFSGS& SpecMap(unsigned char index)
	{
		flags |= (1 << 6);
		specMap = index;
		return *this;
	}
	const std::string& Finish()
	{
		if (!flags)
			return endCode;

		if (flags & (1 << 0))
			endCode.append(inOut);
		if (flags & (1 << 1))
		{
			endCode.append(textures);
			endCode.replace(endCode.find("__"), 2, std::to_string(tex));
		}
		if (flags & (1 << 2))
			endCode.append(materials);
		if (flags & (1 << 3) || flags & (1 << 4) || flags & (1 << 5))
			endCode.append(camPos);
		for (int i = 0; i < 3; i++)
		{
			if (!(flags & (1 << (3 + i))))
				continue;
			switch (i)
			{
			case 0:
				endCode.append(pointLight1);
				endCode.append(pointLight2);
				endCode.replace(endCode.find("__"), 2, std::to_string(point));
				endCode.append(pointLight3);
				break;
			case 1:
				endCode.append(directLight1);
				endCode.append(directLight2);
				endCode.replace(endCode.find("__"), 2, std::to_string(dir));
				endCode.append(directLight3);
				break;
			case 2:
				endCode.append(spotLight1);
				endCode.append(spotLight2);
				endCode.replace(endCode.find("__"), 2, std::to_string(spot));
				endCode.append(spotLight3);
				break;
			}
			if (flags & (1 << 6) && flags & (1 << 1))
				endCode.replace(endCode.find("_0"), 2, "float texColorSpec = texture(u_textures[" + std::to_string(specMap) + "], v_tex).r;\n");
			else
				endCode.replace(endCode.find("_0"), 2, "float texColorSpec = 1;\n");

			if (flags & (1 << 2))
			{
				endCode.replace(endCode.find("_1"), 2, "m_highlights");
				endCode.replace(endCode.find("_3"), 2, "m_diffuse *");
				endCode.replace(endCode.find("_4"), 2, "* m_specular");
			}
			else
			{
				endCode.replace(endCode.find("_1"), 2, "1");
				endCode.replace(endCode.find("_3"), 2, "0.5 *");
				endCode.replace(endCode.find("_4"), 2, "* 0.4");
			}
		}
		if (flags & (1 << 3) || flags & (1 << 4) || flags & (1 << 5))
		{
			endCode.append(lights);
			if (flags & (1 << 3))
				endCode.replace(endCode.find("_0"), 2, 
					R"(
for (int i = 0; i < TotalPointLights; i++)
        light += CalcPointLight(i);)");
			else
				endCode.replace(endCode.find("_0"), 2,
					"");
			if (flags & (1 << 4))
				endCode.replace(endCode.find("_1"), 2,
					R"(
    for (int i = 0; i < TotalDirectionalLights; i++)
        light += CalcDirectionalLight(i);)");
			else
				endCode.replace(endCode.find("_1"), 2,
					"");
			if (flags & (1 << 5))
				endCode.replace(endCode.find("_2"), 2,
					R"(
    for (int i = 0; i < TotalSpotLights; i++)
        light += CalcSpotLight(i);)");
			else
				endCode.replace(endCode.find("_2"), 2,
					"");

		}
		if (flags & (1 << 0) && (flags & (1 << 3) || flags & (1 << 4) || flags & (1 << 5)))
		{
			endCode.append(
				R"(
void main()
{
	_1
	color = (Lights() + _0) * v_color _2;
}
				)"
			);
			if (flags & (1 << 2))
				endCode.replace(endCode.find("_0"), 2,
					"m_ambient");
			else
				endCode.replace(endCode.find("_0"), 2,
					"0");
			if (flags & (1 << 7) && flags & (1 << 0))
			{
				endCode.replace(endCode.find("_1"), 2,
					"vec4 texColor = texture(u_textures[" + std::to_string(texUse) + "], v_tex);");
				endCode.replace(endCode.find("_2"), 2,
					"* texColor");
			}
			else
			{
				endCode.replace(endCode.find("_1"), 2,
					"");
				endCode.replace(endCode.find("_2"), 2,
					"");
			}
		}
		else if (flags & (1 << 0))
		{
			endCode.append(
				R"(
void main()
{
	_1
	color = v_color _2;
}
				)"
			);
			if (flags & (1 << 7) && flags & (1 << 0))
			{
				endCode.replace(endCode.find("_1"), 2,
					"vec4 texColor = texture(u_textures[" + std::to_string(texUse) + "], v_tex);");
				endCode.replace(endCode.find("_2"), 2,
					"* texColor");
			}
			else
			{
				endCode.replace(endCode.find("_1"), 2,
					"");
				endCode.replace(endCode.find("_2"), 2,
					"");
			}
		}
		else
			endCode.append(
				R"(
void main()
{
}
				)"
			);
		return endCode;
	}
};