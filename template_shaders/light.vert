#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
out vec4 v_color;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
void main()
{
    v_color = color;
    gl_Position = u_proj * u_view * u_model * vec4(position, 1.0f);
};