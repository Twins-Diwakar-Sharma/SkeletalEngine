#version 430

layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;


struct Camera
{
	vec4 spin;
	vec3 pos;
};

uniform mat4 projection;
uniform Camera cam;
uniform sampler2D heightMap;
uniform int heightMapSize;
uniform int tesselatedSize;

out vec3 fragWorldPos;
out vec2 fragAbsSteppedObjectPos;
out float doMode;

const float threshold = 1.5f;

in GEO
{
    vec3 pos;
    vec3 fragWorldPos;
    vec2 fragAbsSteppedObjectPos;
    float doMode;
} geoIn[];

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

void createVertex(int i)
{
    vec3 worldPos = geoIn[i].pos;
    vec3 viewPos = worldPos.xyz - cam.pos;
    vec4 quatView = vec4(viewPos,0);
    vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
    vec4 spinQuatInv = vec4(cam.spin);

    quatView = quatRotate(quatView, spinQuatInv);
    quatView = quatRotate(spinQuat, quatView);

    vec4 projectedPos = projection * vec4(quatView.xyz,1.0);
    gl_Position = projectedPos;
    fragWorldPos = geoIn[i].fragWorldPos;
    fragAbsSteppedObjectPos = geoIn[i].fragAbsSteppedObjectPos;
    doMode = geoIn[i].doMode;
    
    EmitVertex();
}

void createNewVertex(vec3 gWorldPos, vec3 gFragWorldPos, vec2 gFragAbsSteppedObjectPos, float gDoMode)
{
    vec3 worldPos = gWorldPos;
    fragWorldPos = gFragWorldPos;
    fragAbsSteppedObjectPos = gFragAbsSteppedObjectPos;
    doMode = gDoMode;
    worldPos.y = getHeightFromTexture(worldPos.x,worldPos.z);
    vec3 viewPos = worldPos.xyz - cam.pos;
    vec4 quatView = vec4(viewPos,0);
    vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
    vec4 spinQuatInv = vec4(cam.spin);

    quatView = quatRotate(quatView, spinQuatInv);
    quatView = quatRotate(spinQuat, quatView);

    vec4 projectedPos = projection * vec4(quatView.xyz,1.0);
    gl_Position = projectedPos;

    
    EmitVertex();
}

void main()
{
    vec2 dis[3];
    dis[0] = geoIn[0].pos.xz - geoIn[1].pos.xz;
    dis[1] = geoIn[1].pos.xz - geoIn[2].pos.xz;
    dis[2] = geoIn[2].pos.xz - geoIn[0].pos.xz;

    int rightAngleIndex = 0;
    int otherIndexA = 0;
    int otherIndexB = 0;
    for(int i=0; i<3; i++)
    {
        int j = int(mod(i+1,3));
        if(dot(dis[i],dis[j]) == 0)
        {
            rightAngleIndex = j;
            otherIndexA = i;
            otherIndexB = int(mod(j+1,3));
        }
    }

    vec3 newWorldPos = 0.5*(geoIn[otherIndexA].pos + geoIn[otherIndexB].pos);
    vec3 newFragWorldPos = newWorldPos;
    vec2 newFragAbsSteppedObjectPos = geoIn[rightAngleIndex].fragAbsSteppedObjectPos;
    float newDoMode = geoIn[rightAngleIndex].doMode;

    createVertex(otherIndexA);
    createVertex(rightAngleIndex);
    createNewVertex(newWorldPos,newFragWorldPos,newFragAbsSteppedObjectPos,newDoMode);
    createVertex(otherIndexB);

    EndPrimitive();
}