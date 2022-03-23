#version 400

in vec2 fragTex;

out vec4 color;
uniform sampler2D albedo;

void main()
{
    color = texture(albedo,fragTex);
    if(color.a < 0.4)
        discard;
}