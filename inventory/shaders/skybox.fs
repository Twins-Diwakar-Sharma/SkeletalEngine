#version 430

in vec3 fragTex;

out vec4 color;

uniform samplerCube skybox;

void main()
{
    color = texture(skybox, fragTex);
}