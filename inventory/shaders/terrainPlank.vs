#version 430

layout (location = 0) in vec2 pos;

uniform vec2 size;
uniform int rotate;


void main()
{
	vec2 objectPos = pos;
	vec2 sizedPos = size*objectPos;
	if(rotate == 1)
	{
		mat2 rot = mat2(
			0, -1,	// first column
			1, 0	// second column
		);

		sizedPos = rot * sizedPos;
	}
	gl_Position = vec4(sizedPos.x,0,sizedPos.y,1.0);
}
 