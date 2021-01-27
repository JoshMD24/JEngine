#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

//uniform sampler2D inputTexture;
uniform vec3 viewPosition;

struct Material
{
    sampler2D diffuseMap;
    float shininess; // Ns
    float transparency; //d
    vec3 ambient; //Ka
    vec3 diffuse; //Kd
    vec3 specular; //Ks
};

uniform Material material;

struct Light
{
    vec3 lightPosition;
    float ambient;
    float diffuse;
    vec3 lightColor;
};

uniform Light lightSource;

void main()
{

    //ambient
    vec3 ambient = lightSource.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * lightSource.lightColor;
    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightSource.lightPosition - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse)* texture(material.diffuseMap, TexCoords).rgb * lightSource.lightColor;
    //specular
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * lightSource.lightColor;

    vec3 result = ambient + diffuse + specular;

    fColour = vec4(result, 0.8f);

}
