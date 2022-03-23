#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 projection;
uniform mat4 transform;

out vec2 fragTex;

void main()
{
    vec4 objectPos = vec4(pos,1);
    vec4 worldPos = transform * objectPos;
    gl_Position = projection * worldPos;

    fragTex = tex;
}