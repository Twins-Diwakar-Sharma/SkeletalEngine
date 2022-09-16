#version 430

struct Camera
{
	vec4 spin;
	vec3 pos;
};

layout (location = 0) in vec3 pos;

out vec3 fragTex;

uniform mat4 projection;
uniform Camera cam;

vec4 quatRotate(vec4 action, vec4 victim)
{
	float ar = action.w;	float br = victim.w;
	vec3 av = action.xyz;	vec3 bv = victim.xyz;
	return vec4(ar*bv + br*av + cross(av,bv), ar*br - dot(av,bv));
}

void main()
{
    fragTex = pos;

    
    vec4 quatView = vec4(pos,0);
	vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
	vec4 spinQuatInv = vec4(cam.spin);

	quatView = quatRotate(quatView, spinQuatInv);
	quatView = quatRotate(spinQuat, quatView);

	vec3 viewPos = quatView.xyz;

    vec4 projectedPos = projection * vec4(viewPos,1.0);
    

    gl_Position = projectedPos;
}