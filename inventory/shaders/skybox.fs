#version 430

in vec3 fragTex;
in vec3 fragPos;

layout (location=0) out vec4 gPosition;
layout (location=1) out vec4 gAlbedo;
layout (location=2) out vec4 gNormal;

uniform samplerCube skybox;

void main()
{
    gPosition = vec4(fragPos,0);
    gAlbedo = texture(skybox, fragTex);
    gNormal = vec4(normalize(fragPos),1);
}