#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 lightcolor;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;


void main()
{       
    FragColor = texture(texture_diffuse1, TexCoords);
}