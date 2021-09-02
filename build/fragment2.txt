#version 330 core
out vec4 FragColor;

  
//in vec3 ourColor;
in vec2 TexCoord;
in float oTextID;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D text[2];

void main()
{
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5); 
    //FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(oTextID, oTextID, oTextID, 1);
    int index = int(oTextID);
    FragColor =  texture(text[index], TexCoord);
   
}