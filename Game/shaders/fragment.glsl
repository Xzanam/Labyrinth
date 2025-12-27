#version 460 core

in vec3 FragPosWS;
in vec3 NormalWS;

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction; // World-space light direction

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight dirLight;
uniform vec3 objectColor;
uniform vec3 viewPos;   // Camera position in world space


vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);


void main()
{
    vec3 norm = normalize(NormalWS);
    vec3 viewDir =  normalize(viewPos - FragPosWS);

    vec3 result = calcDirectionalLight(dirLight, norm, viewDir);

    FragColor = vec4(result, 1.0);
}


vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir ) {

    vec3 lightDir = normalize(-light.direction);
    //diff
    float diff = max(dot(normal, lightDir), 0.0);

    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // 32.0 is the shininiess value

    vec3 ambient = light.ambient * objectColor;
    vec3 diffuse  = light.diffuse * diff * objectColor;
    vec3 specular = light.specular * spec * objectColor;
    return (ambient + diffuse + specular);
}
