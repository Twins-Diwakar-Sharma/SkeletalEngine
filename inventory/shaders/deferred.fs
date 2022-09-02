#version 430

out vec4 color;
in vec2 fragTex;

uniform sampler2D gPosition;
uniform sampler2D gAlbedo;
uniform sampler2D gNormal;

void main()
{
    vec4 albedo = texture(gAlbedo, fragTex);
    color = albedo;
}