#version 430

out vec4 color;
in vec2 fragTex;

uniform sampler2D gPosition;
uniform sampler2D gAlbedo;
uniform sampler2D gNormal;

struct Camera
{
	vec4 spin;
	vec3 pos;
};

struct DirectionalLight
{
	vec3 dir;
	vec3 col;
};


uniform DirectionalLight sun;
uniform Camera cam;

vec4 quatRotate(vec4 action, vec4 victim)
{
	float ar = action.w;	float br = victim.w;
	vec3 av = action.xyz;	vec3 bv = victim.xyz;
	return vec4(ar*bv + br*av + cross(av,bv), ar*br - dot(av,bv));
}

void main()
{
    vec4 fragPosition = texture(gPosition, fragTex);
    vec4 fragAlbedo = texture(gAlbedo, fragTex);
    vec4 fragNormal = texture(gNormal, fragTex);

    vec3 toLight = -1*(normalize(sun.dir));
/*
    vec4 quatToLight = vec4(toLight,0);
	vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
	vec4 spinQuatInv = vec4(cam.spin);
    quatToLight = quatRotate(quatToLight, spinQuatInv);
	quatToLight = quatRotate(spinQuat, quatToLight);
    toLight = quatToLight.xyz;
*/
    vec3 normal = fragNormal.rgb;	
	float diffuse = max(dot(toLight,normal),0.0);
	vec3 diffuseColor = diffuse*sun.col;


    color = vec4(diffuseColor,1.0) * fragAlbedo;
}