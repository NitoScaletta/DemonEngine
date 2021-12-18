#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec2 FragPos;
out vec2 TexCoord;

uniform mat4 aMVP;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = aMVP * aPos;
    FragPos = aPos.xy;
}
