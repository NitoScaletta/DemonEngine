#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec4 ourColor;
in vec3 outNormal;
in vec3 FragPos;



struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 


struct Light {
    vec3 position;
    vec3 lightColor;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform sampler2D texture1;
uniform vec3 viewPos;
uniform Light light;
uniform Material material;


void main()
{
    //ambient diffuse
    vec3 ambient = light.ambient * material.ambient;

    //diffuse light
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir),0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    //vec3 ambient = lightColor * ambients;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(texture(texture1, TexCoord)*vec4(result,1.0));
}