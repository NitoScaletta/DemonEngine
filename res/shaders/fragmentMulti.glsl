#version 450 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 outNormal;
in vec3 FragPos;


struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float cutoffouter;

    vec3 lightColor;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
    float constant;
    float linear;
    float quadratic;
};


struct DirLight 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};


struct PointLight {
    vec3 position;
    vec3 lightColor;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
// uniform vec3 aColor;
uniform Material material;
uniform DirLight dirlight;
#define N_POINT 10
uniform PointLight pointlight[N_POINT];
uniform SpotLight spotlight;
uniform vec3 viewPos;

vec3 norm;
vec3 lightDir;
vec3 viewDir;

vec3 calcDirLight(DirLight light)
{
    vec3 ambient = light.ambient *  texture(material.diffuse, TexCoord).rgb;
    float diff = max(dot(norm, lightDir),0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    return ambient+diffuse+specular;
}


vec3 calcPointLight(PointLight light)
{
    float distance = length(light.position -FragPos);
    float attenuation = 1/(light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    float diff = max(dot(norm, lightDir),0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoord).rgb;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient+diffuse+specular;
}


vec3 calcSpotLight(SpotLight light)
{
    vec3 ambient = light.ambient *  texture(material.diffuse, TexCoord).rgb;


    lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir),0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoord).rgb;


    //specular lighting
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
    return result;
}



void main()
{
    viewDir = normalize(viewPos - FragPos);
    norm = normalize(outNormal);
    lightDir = normalize(-dirlight.direction);
    vec3 result =  calcDirLight(dirlight);
    for(int i = 0; i < N_POINT; i++)
    {
        lightDir = normalize(pointlight[i].position - FragPos);
        result += calcPointLight(pointlight[i]);
    }

    result += calcSpotLight(spotlight);
    FragColor = vec4(result,1.0);
}