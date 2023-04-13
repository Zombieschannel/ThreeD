#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;
out vec4 v_color;
out vec2 v_tex;
out vec3 v_normal;
out vec3 v_pos;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
void main()
{
    v_pos = vec3(u_model * vec4(position, 1.0f));
    v_color = color;
    gl_Position = u_proj * u_view * u_model * vec4(position, 1.0f);
    v_tex = texCoord;
    v_normal = normal;
};