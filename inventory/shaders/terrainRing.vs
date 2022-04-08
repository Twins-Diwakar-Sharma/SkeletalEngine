#version 430

layout (location = 0) in vec2 pos;

uniform int size;
uniform vec2 position;

void main()
{
	vec2 objectPos = pos;
	vec2 sizedPos = size*objectPos;
	vec2 worldPos = sizedPos + position;
	gl_Position = vec4(worldPos.x,0,worldPos.y,1.0);
}
 