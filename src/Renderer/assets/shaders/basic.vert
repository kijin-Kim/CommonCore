#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 u_MVP;
uniform vec3 u_Color;

out vec3 vColor;

void main()
{
    vColor = aColor * u_Color; // tint color
    gl_Position = u_MVP * vec4(aPos, 0.0, 1.0);
}
