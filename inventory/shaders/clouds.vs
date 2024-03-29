#version 430
struct Camera
{
	vec4 spin;
	vec3 pos;
};

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 nor;

uniform mat4 projection;
uniform mat4 transform;
uniform Camera cam;

out vec2 fragTex;
out vec3 fragNor;

out vec3 camPos;
out vec3 fragWorldPos;

vec4 quatRotate(vec4 action, vec4 victim)
{
	float ar = action.w;	float br = victim.w;
	vec3 av = action.xyz;	vec3 bv = victim.xyz;
	return vec4(ar*bv + br*av + cross(av,bv), ar*br - dot(av,bv));
}


void main()
{
	vec3 position = pos;
    vec4 objectPos = vec4(position,1);
    vec4 worldPos = transform * objectPos;
  

	vec3 viewPos = worldPos.xyz - cam.pos;
	vec4 quatView = vec4(viewPos,0);
	vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
	vec4 spinQuatInv = vec4(cam.spin);

	quatView = quatRotate(quatView, spinQuatInv);
	quatView = quatRotate(spinQuat, quatView);

	vec4 projectedPos = projection * vec4(quatView.xyz,1.0);


	gl_Position = projectedPos;

    fragTex = tex;
	vec3 normal = nor;
	fragNor = normalize((transform * vec4(normal,0.0) ).xyz) ;
	camPos = cam.pos;
	fragWorldPos = worldPos.xyz;
}