#version 430
layout(quads, equal_spacing, cw) in;

struct Camera
{
	vec4 spin;
	vec3 pos;
};

uniform mat4 projection;
uniform Camera cam;

uniform vec2 size;
uniform int rotate;
uniform vec2 position;

uniform sampler2D heightMap;
uniform int heightMapSize;
uniform vec2 step;

out vec3 fragWorldPos;

const float threshold=1.5f;

vec4 quatRotate(vec4 action, vec4 victim)
{
	float ar = action.w;	float br = victim.w;
	vec3 av = action.xyz;	vec3 bv = victim.xyz;
	return vec4(ar*bv + br*av + cross(av,bv), ar*br - dot(av,bv));
}

float getHeightFromTexture(float x, float z)
{
    // rescale x,z from [-heightMapSize/2,+heightMapSize/2] in [0,1] scale
    x = x + heightMapSize/2.0;
    z = -z; // because -ve z is top
    z = z + heightMapSize/2.0;
    x = x/float(heightMapSize);
    z = z/float(heightMapSize);

    // get heightMapValue
    vec4 heightMapColor = texture(heightMap,vec2(x,z));
    float heightMapValue = heightMapColor.r;

    // rescale heightMapValue from [0,1] to [-heightMapSize/2,+heightMapSize/2]
    heightMapValue = 2*heightMapValue;
    heightMapValue = heightMapValue - 1;
    heightMapValue = heightMapValue * heightMapSize/2;

    return heightMapValue;
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


    vec3 sizedPos = interpolatedPos.xyz;

    vec3 worldPos =  sizedPos + vec3(position.x,0,position.y);
    worldPos.y = getHeightFromTexture(worldPos.x,worldPos.z);
    
    vec2 absSizedPos = abs(sizedPos.xz);
    vec2 absShiftedObjectPos = sizedPos.xz;
    if(rotate == 1)
        absShiftedObjectPos.x += -step.x*(2*size.x + 0.5*size.y);
    else
        absShiftedObjectPos.y += -step.y*(2*size.x + 0.5*size.y);

    absShiftedObjectPos = abs(absShiftedObjectPos/size.x);

  //  if(rotate == 1) // vertical
 //   {
        if(int(mod(absSizedPos.y,2*size.y)) == size.y )
        {
            float alpha = 1;
            if( (sizedPos.x >= 0 && step.x >= 0) || (sizedPos.x <= 0 && step.x <= 0) )
                alpha = (2.0 - (size.y/size.x) - threshold)/(2.0 - threshold);
            float heightFront = getHeightFromTexture(worldPos.x, worldPos.z - size.y);
            float heightBack = getHeightFromTexture(worldPos.x, worldPos.z + size.y);
            float averageHeight = (heightFront+heightBack)/2.0;
            worldPos.y = (1.0 - alpha)*worldPos.y + alpha*averageHeight;
        }
 //   }  
 //   else    // horizontal
 //   {
        if(int(mod(absSizedPos.x,2*size.y)) == size.y )
        {
            float alpha = 1;
            if( (sizedPos.y >= 0 && step.y >= 0) || (sizedPos.y <= 0 && step.y <= 0) )
                alpha = (2.0 - (size.y/size.x) - threshold)/(2.0 - threshold);
            float heightLeft = getHeightFromTexture(worldPos.x - size.y, worldPos.z);
            float heightRight = getHeightFromTexture(worldPos.x + size.y, worldPos.z);
            float averageHeight = (heightLeft+heightRight)/2.0;
            worldPos.y = (1.0 - alpha)*worldPos.y + alpha*averageHeight;
        }
 //   }  

	vec3 viewPos = worldPos.xyz - cam.pos;
	vec4 quatView = vec4(viewPos,0);
	vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
	vec4 spinQuatInv = vec4(cam.spin);

	quatView = quatRotate(quatView, spinQuatInv);
	quatView = quatRotate(spinQuat, quatView);

	vec4 projectedPos = projection * vec4(quatView.xyz,1.0);


	gl_Position = projectedPos;
    fragWorldPos = worldPos;

}
