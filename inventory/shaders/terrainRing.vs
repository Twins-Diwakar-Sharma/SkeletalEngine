#version 430

layout (location = 0) in vec2 pos;

uniform int size;

void main()
{
	vec2 position = pos;
	vec2 sizedpos = size*position;
	gl_Position = vec4(sizedpos.x,0,sizedpos.y,1.0);
}
 