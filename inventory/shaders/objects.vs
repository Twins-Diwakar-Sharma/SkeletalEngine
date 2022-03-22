#version 400

layout (location = 0) in vec3 pos;

uniform mat4 projection;

void main()
{
    vec4 worldPos = vec4(pos,1);
    worldPos.z = -4;
    gl_Position = projection * worldPos;
}