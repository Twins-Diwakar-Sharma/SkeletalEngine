#version 430

layout (location = 0) in vec2 pos;

uniform int size;

void main()
{
	vec2 objectPos = pos;
	vec2 sizedPos = size*objectPos;
	gl_Position = vec4(sizedPos.x,0,sizedPos.y,1.0);
}
 