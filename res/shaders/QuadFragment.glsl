#version 450 core
out vec4 FragColor;
in vec2 TexCoord;
in vec4 ourColor;

uniform sampler2D m_texture;

void main()
{
    FragColor = ourColor;
}