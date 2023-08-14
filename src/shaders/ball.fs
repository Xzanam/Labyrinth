#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

in vec3 FragPos; //for diffused lighting
uniform vec3 lightcolor;
uniform vec3 objectcolor;

uniform vec3 lightPos;  
uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;


struct Material{
    sampler2D diffuse;  
    vec3 specular; 
    float shininess; 

};

struct Light{
    vec3 position; 
    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular; 

};

uniform Light light;
uniform Material material; 
 

void main()
{       
    // FragColor = texture(texture_diffuse1, TexCoords);


    vec3 ambient =light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse =light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); 

    //for specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir),0.0), 32);
    vec3 specular = light.specular  * (spec * material.specular);
      
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0f);
}