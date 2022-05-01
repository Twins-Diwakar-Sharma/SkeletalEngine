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


const float threshold=1.5f;




out GEO
{
    vec3 pos;
    float doMode;
    vec2 fragAbsAdjustedObjectPos;
    vec3 fragWorldPos;
} geoOut;

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



    float ringSize = size.x;
    float tesselatedSize = size.y;

    vec3 sizedPos = interpolatedPos.xyz;
/*
    if(step.x == 1)
    {
        sizedPos.x = sizedPos.x - tesselatedSize;
    }
    if(step.x == -1)
    {
        sizedPos.x = sizedPos.x + tesselatedSize;
    }

    if(step.y == 1)
    {
        sizedPos.y
    }*/

    vec3 worldPos =  sizedPos + vec3(position.x,0,position.y);

    // cut if 0
    if(rotate == 1 && sizedPos.x == 0)
    {
        worldPos.x = worldPos.x - tesselatedSize/2;  
    }
    if(rotate == 0 && sizedPos.y == 0)
    {
        worldPos.y = worldPos.y - tesselatedSize/2;
    }

    worldPos.y = getHeightFromTexture(worldPos.x,worldPos.z);


    vec2 adjustedSizedPos = sizedPos.xz;
    if(rotate == 1)
        adjustedSizedPos.x = adjustedSizedPos.x -step.x*(2*ringSize - 0.5*tesselatedSize);
    else
        adjustedSizedPos.y = adjustedSizedPos.y -step.y*(2*ringSize - 0.5*tesselatedSize);
    
    vec2 absAdjustedSizedPos = abs(adjustedSizedPos);
    vec2 absAdjustedObjectPos = absAdjustedSizedPos/ringSize;
    
    geoOut.doMode = 0;
    if(absAdjustedObjectPos.y >= threshold && int(mod(absAdjustedSizedPos.x,2*tesselatedSize)) == tesselatedSize)
    {
        geoOut.doMode = 1;
        float alpha = (absAdjustedObjectPos.y - threshold)/(2.0 - threshold);
        float heightLeft = getHeightFromTexture(worldPos.x - tesselatedSize, worldPos.z);
        float heightRight = getHeightFromTexture(worldPos.x + tesselatedSize, worldPos.z);
        float averageHeight = (heightLeft+heightRight)/2.0;
        worldPos.y = (1.0 - alpha)*worldPos.y + alpha*averageHeight;
    }
    if(absAdjustedObjectPos.x >= threshold && int(mod(absAdjustedSizedPos.y,2*tesselatedSize)) == tesselatedSize)
    {
        geoOut.doMode = 1;
        float alpha = (absAdjustedObjectPos.x - threshold)/(2.0 - threshold); 
        float heightFront = getHeightFromTexture(worldPos.x, worldPos.z - tesselatedSize);
        float heightBack = getHeightFromTexture(worldPos.x, worldPos.z + tesselatedSize);
        float averageHeight = (heightFront+heightBack)/2.0;
        worldPos.y = (1.0 - alpha)*worldPos.y + alpha*averageHeight;
    }

    

    geoOut.pos = worldPos;
    geoOut.fragWorldPos = worldPos;

    geoOut.fragAbsAdjustedObjectPos = absAdjustedObjectPos;

}
