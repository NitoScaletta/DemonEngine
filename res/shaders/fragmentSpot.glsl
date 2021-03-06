#version 450 core
out vec4 FragColor;
in vec2 TexCoord;
in vec4 ourColor;
in vec3 outNormal;
in vec3 FragPos;



struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 


struct Light {
    vec2 position;
    vec2 direction;
    float cutoff;
    float cutoffouter;


    vec2 lightColor;
    vec2 ambient;
    vec2 diffuse;
    vec2 specular; 
    float constant;
    float linear;
    float quadratic;
};


uniform vec3 viewPos;
uniform Light light;
uniform Material material;


void main()
{
    //ambient diffuse
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
    

    //diffuse light
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir),0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoord).rgb;


    //specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    //spotlight
    float theta = dot(lightDir,normalize(-light.direction));
    float epsilion = light.cutoff - light.cutoffouter;
    float intensity=clamp((theta - light.cutoffouter)/epsilion, 0.0, 1.0);
    specular *= intensity;
    diffuse *= intensity;


//attenuation
    float distance = length(light.position -FragPos);
    float attenuation = 1/(light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;


    //vec3 ambient = lightColor * ambients;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);
    

}