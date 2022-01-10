#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTextID;

out vec4 ourColor;
out vec2 TexCoord;
out float oTextID;


uniform mat4 aMVP;

void main()
{
    gl_Position = aMVP * aPos;
    oTextID = aTextID;
    ourColor = aColor;
    TexCoord = aTexCoord;
}