#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
in vec4 ourColor;
in vec4 o_aPos;

uniform sampler2D m_texture;

void main()
{
    FragColor = texture(m_texture, TexCoord);
}