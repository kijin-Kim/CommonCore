#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 u_MVP;
uniform vec4 u_Color;

out vec4 vColor;

void main()
{
    vColor = u_Color;
    gl_Position = u_MVP * vec4(aPos, 0.0, 1.0);
}
