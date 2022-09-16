#version 430

out vec4 color;
in vec2 fragTex;

uniform sampler2D gAlbedo;

void main()
{
    vec4 albedo = texture(gAlbedo, fragTex);
    color = albedo;
}