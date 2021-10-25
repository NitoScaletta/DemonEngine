#version 460 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTextID;
layout (location = 4) in vec3 aNormal;


out vec3 FragPos;
out vec2 TexCoord;
out vec4 Color;

uniform mat4 aMVP;

void main()
{
    Color = aColor;
    gl_Position = aMVP * aPos;
    FragPos = vec3(aPos);
}