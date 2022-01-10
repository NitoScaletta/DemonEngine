#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aLocalPosition;
layout (location = 2) in vec4 aColor;
layout (location = 3) in float aThickness;
layout (location = 4) in float aFade;


out vec2  FragPos;
out vec4  oColor;
out float  oThickness;
out float oFade;

uniform mat4 aMVP;

void main()
{
    oColor = aColor;
    oThickness = aThickness;
    oFade = aFade;

    gl_Position =  aMVP * aPos;
    FragPos = aLocalPosition.xy;
}
