#version 430


struct DirectionalLight
{
	vec3 dir;
	vec3 col;
};

in vec2 fragTex;
in vec3 fragNor;

out vec4 color;
uniform sampler2D albedo;
uniform DirectionalLight sun;

void main()
{
    vec3 toLight = normalize(-1*sun.dir);	
	float diffuse = max(dot(toLight,fragNor),0.1);
	vec3 diffuseColor = diffuse*sun.col;
	color = vec4(diffuseColor,1.0)  * texture(albedo,fragTex);
	if(color.a < 0.2)
		discard;
}