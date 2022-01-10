#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTextID;


out vec2  FragPos;
out vec4  oColor;
out vec2  oTexCoord;
out float oTextID;

uniform mat4 aMVP;

void main()
{
    oColor = aColor;
    oTexCoord = aTexCoord;
    oTextID = aTextID;

    gl_Position =  aMVP * aPos;
    FragPos =aPos.xy;
}
