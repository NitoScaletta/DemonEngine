#version 450 core
out vec4 FragColor;
in vec2 TexCoord;
in vec2 FragPos;
in vec4 oColor;


void main(){

    float thickness = 1;
    float fade =  0.005;

    float distance =  1 - length(FragPos.xy);
    float circleAlpha = smoothstep(0.0, fade, distance);
    circleAlpha *= smoothstep(thickness + fade, thickness, distance);

    FragColor = vec4(oColor.rgb,circleAlpha);
}