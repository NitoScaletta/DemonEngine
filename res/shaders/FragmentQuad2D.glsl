#version 450 core
out vec4 FragColor;

in vec2 oTexCoord;
in vec4 oColor;
in vec4 FragPos;
in float oTextID;

uniform sampler2D m_texture;

void main()
{
    FragColor = oColor;
}