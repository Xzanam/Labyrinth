#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPosWS;   // World-space position
out vec3 NormalWS;    // World-space normal

void main()
{
    // Clip-space position
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // World-space position
    FragPosWS = vec3(model * vec4(aPos, 1.0));

    // World-space normal
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    NormalWS = normalize(normalMatrix * aNormal);
}
