#version 430
layout(quads, equal_spacing, cw) in;

struct Camera
{
	vec4 spin;
	vec3 pos;
};

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

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec4 p[4];
    p[0] = gl_in[0].gl_Position;
    p[1] = gl_in[1].gl_Position;
    p[2] = gl_in[2].gl_Position;
    p[3] = gl_in[3].gl_Position;
    // Linear interpolation
    
    vec4 interpolatedPos =
    p[0] * (1-u) * (1-v) +
    p[1] * u * (1-v) +
    p[3] * v * (1-u) +
    p[2] * u * v;


    vec3 objectPos = interpolatedPos.xyz;

    vec3 worldPos =  objectPos;

	vec3 viewPos = worldPos.xyz - cam.pos;
	vec4 quatView = vec4(viewPos,0);
	vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
	vec4 spinQuatInv = vec4(cam.spin);

	quatView = quatRotate(quatView, spinQuatInv);
	quatView = quatRotate(spinQuat, quatView);

	vec4 projectedPos = projection * vec4(quatView.xyz,1.0);


	gl_Position = projectedPos;

}
