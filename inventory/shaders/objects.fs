#version 430

layout (location=0) out vec4 gPosition;
layout (location=1) out vec4 gAlbedo;
layout (location=2) out vec4 gNormal;

struct DirectionalLight
{
	vec3 dir;
	vec3 col;
};

in vec2 fragTex;
in vec3 fragNor;
in vec3 fragPos;

uniform sampler2D albedo;
uniform DirectionalLight sun;

void main()
{
    vec3 toLight = normalize(-1*sun.dir);	
	float diffuse = max(dot(toLight,fragNor),0.1);
	vec3 diffuseColor = diffuse*sun.col;
	vec4 color = vec4(diffuseColor,1.0)  * texture(albedo,fragTex);
	if(color.a < 0.2)
		discard;
	
	gPosition = vec4(fragPos,1);
	gAlbedo = color;
	gNormal = vec4(fragNor,1);

}