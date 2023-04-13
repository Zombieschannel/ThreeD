#version 330 core
layout(location = 0) out vec4 color;
in vec4 v_color;
in vec2 v_tex;
in vec3 v_normal;
in vec3 v_pos;



uniform sampler2D u_textures[8];
uniform vec3 camPos;

struct Light
{
    vec4 col;
	float specInten;
	int type;
	float quadratic;
	float linear;
	float specPow;
	float outer;
	float inner;
	vec3 dir;
	vec3 pos;
};
uniform Light lights[3];


vec4 pointLight(Light light)
{
    vec3 lightVec = light.pos - v_pos;
    float dist = length(lightVec);
    float a = light.quadratic;
    float b = light.linear;
    float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
    
    //ambient
    float ambient = 0.2f;

    //diffuse
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    
    //specular
    float specularLight = light.specInten;
    vec3 viewDirection = normalize(camPos - v_pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), light.specPow);
    float specular = specAmount * specularLight;
    float texColorSpec = texture(u_textures[2], v_tex).r;

    return light.col * (diffuse * inten + ambient) + texColorSpec * specular * inten;
}
vec4 directLight(Light light)
{
    //ambient
    float ambient = 0.2f;

    //diffuse
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(-light.dir);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    
    //specular
    float specularLight = light.specInten;
    vec3 viewDirection = normalize(camPos - v_pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), light.specPow);
    float specular = specAmount * specularLight;
    float texColorSpec = texture(u_textures[2], v_tex).r;

    return light.col * (diffuse + ambient) + texColorSpec * specular;
}
vec4 spotLight(Light light)
{
    float outerCone = light.outer;
    float innerCone = light.inner;
    //ambient
    float ambient = 0.2f;

    //diffuse
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(light.pos - v_pos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    
    //specular
    float specularLight = light.specInten;
    vec3 viewDirection = normalize(camPos - v_pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), light.specPow);
    float specular = specAmount * specularLight;
    float texColorSpec = texture(u_textures[2], v_tex).r;

    float angle = dot(light.dir, -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.f);

    return light.col * (diffuse * inten + ambient) + texColorSpec * inten * specular;
}
void main()
{
   
    
    vec4 texColor = texture(u_textures[0], v_tex);
    vec4 Light = vec4(0.f, 0.f, 0.f, 0.f);
    for (int i = 0; i < 3; i++)
    {
        if (lights[i].type == 2)
        {
            Light += spotLight(lights[i]);
        }
        else if (lights[i].type == 1)
            Light += directLight(lights[i]);
        else
            Light += pointLight(lights[i]); 
    }
    color = texColor * v_color;
};