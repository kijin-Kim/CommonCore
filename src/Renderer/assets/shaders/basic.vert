#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
uniform vec4 u_Color;

out vec4 vColor;

void main()
{
    vColor = u_Color;
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 0.0, 1.0);
}
