#version 450 core
out vec4 FragColor;
in vec2 TexCoord;
in vec4 ourColor;

uniform vec4 u_Color;

void main()
{
    FragColor = vec4(1.0);
}