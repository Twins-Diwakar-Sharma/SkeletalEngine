#version 430

layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

struct Camera
{
	vec4 spin;
	vec3 pos;
};

uniform mat4 projection;
uniform Camera cam;

uniform sampler2D heightMap;
uniform int heightMapSize;

uniform int size;
uniform int tesselatedSize;
uniform vec2 step;
uniform vec2 position;

out vec3 fragWorldPos;

const float threshold=1.5f;


// debugs
out vec2 fragAbsSteppedObjectPos;
out float doMode;

out vec2 fragAbsSteppedObjectPosFRAG;
out float doModeFRAG;
out vec3 fragWorldPosFRAG;

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

void worldToScreenPos(vec3 worldPos, vec3 sizedPos)
{
    
    vec3 viewPos = worldPos.xyz - cam.pos;
	vec4 quatView = vec4(viewPos,0);
	vec4 spinQuat = vec4(-cam.spin.xyz, cam.spin.w);
	vec4 spinQuatInv = vec4(cam.spin);

	quatView = quatRotate(quatView, spinQuatInv);
	quatView = quatRotate(spinQuat, quatView);

	vec4 projectedPos = projection * vec4(quatView.xyz,1.0);
	gl_Position = projectedPos;

    fragWorldPos = worldPos;
    fragAbsSteppedObjectPos = abs((sizedPos.xz)/float(size));
}

void createVertex(vec3 sizedPos)
{
    // if absSteppedSizedPos > 2 donot EmitVertex
    vec3 worldPos = sizedPos + vec3(position.x, 0, position.y);
    // find height 
    worldToScreenPos(worldPos,sizedPos);
    EmitVertex();
}

void findAngleIndices(inout int indexX, inout int index90, inout int indexZ, inout vec3 sizedPos[3])
{
    vec2 dis[3];
    dis[0] = normalize(sizedPos[1].xz - sizedPos[0].xz);
    dis[1] = normalize(sizedPos[2].xz - sizedPos[1].xz);
    dis[2] = normalize(sizedPos[0].xz - sizedPos[2].xz); 



    if(dot(dis[0],dis[1]) == 0.0)
    {
        if(dis[0].x == 0)
        {
            indexZ = 0;
            indexX = 2;
        }
        else
        {
            indexX = 0;
            indexZ = 2;
        }
        index90 = 1;
    }
    if(dot(dis[1],dis[2]) == 0.0)
    {
        if(dis[1].x == 0)
        {
            indexZ = 1;
            indexX = 0;
        }
        else
        {
            indexX = 1;
            indexZ = 0;
        }
        index90 = 2;
    }
    if(dot(dis[2],dis[0]) == 0.0)
    {
        if(dis[2].x == 0)
        {
            indexZ = 2;
            indexX = 1;
        }
        else
        {
            indexX = 2;
            indexZ = 1;
        }
        index90 = 0;
    }

}

void main()
{
    vec3 sizedPos[3];
    sizedPos[1] = gl_in[1].gl_Position.xyz;
    sizedPos[2] = gl_in[2].gl_Position.xyz;
    sizedPos[0] = gl_in[0].gl_Position.xyz;

    int indexX = 0;
    int index90 = 1;
    int indexZ = 2;
    
    findAngleIndices(indexX, index90, indexZ, sizedPos);
    


    vec2 objectPos[3];
    objectPos[0] = gl_in[0].gl_Position.xz/size;
    objectPos[1] = gl_in[1].gl_Position.xz/size;
    objectPos[2] = gl_in[2].gl_Position.xz/size;

    int isDefault = -200;
    int removed = 0;
    
        if( step.y != 0 && (objectPos[indexZ].y == step.y*2 || objectPos[index90].y == step.y*2 || objectPos[indexX].y == step.y*2) )
        {
            // remove
            isDefault = 200;
            removed = 1;
        }

        if( step.x != 0 && (objectPos[indexZ].x == step.x*2 || objectPos[index90].x == step.x*2 || objectPos[indexX].x == step.x*2) )
        {
            // remove
            isDefault = 200;
            removed = 1;
        }

        if(removed == 0 && step.x != 0 && objectPos[indexZ].x == -step.x*2 && objectPos[index90].x == -step.x*2)
        {
            isDefault = 200;
            vec3 extrudeZ = sizedPos[indexZ] -step.x*vec3(tesselatedSize,0,0);
            vec3 extrude90 = sizedPos[index90] -step.x*vec3(tesselatedSize,0,0);
            vec3 quadMid =  (extrudeZ + sizedPos[index90])/2.0;
            vec3 hyptMid = (sizedPos[indexX] + sizedPos[indexZ])/2.0;

            createVertex(sizedPos[indexX]);
            createVertex(hyptMid);
            createVertex(sizedPos[index90]);
            createVertex(sizedPos[indexZ]);
            createVertex(quadMid);
            createVertex(extrudeZ);
            createVertex(extrude90);
            createVertex(quadMid);
            createVertex(sizedPos[index90]);
            if(step.y != 0) // create corner
            {
                vec3 botLeft = quadMid + vec3(-step.x*tesselatedSize/2,0,-step.y*tesselatedSize/2);
                vec3 topLeft = botLeft + vec3(0,0,-step.y*tesselatedSize);
                vec3 topRight = topLeft + vec3(step.x*tesselatedSize,0,0);
                vec3 botRight = topRight + vec3(0,0,step.y*tesselatedSize);
                vec3 newQuadMid = (topLeft + botRight)/2.0;
                createVertex(sizedPos[index90]); // degenerate
                createVertex(botLeft); // degenerate
                createVertex(botLeft);
                createVertex(topLeft);
                createVertex(newQuadMid);
                createVertex(topRight);
                createVertex(botRight);
                createVertex(newQuadMid);
                createVertex(botLeft);
            }

        }

        
 
        if(removed == 0 && step.y != 0 && objectPos[indexX].y == -step.y*2 && objectPos[index90].y == -step.y*2)
        {
            isDefault = 200;
            vec3 extrudeX = sizedPos[indexX] -step.y*vec3(0,0,tesselatedSize);
            vec3 extrude90 = sizedPos[index90] -step.y*vec3(0,0,tesselatedSize);
            vec3 quadMid =  (extrudeX + sizedPos[index90])/2.0;
            vec3 hyptMid = (sizedPos[indexX] + sizedPos[indexZ])/2.0;

            createVertex(sizedPos[indexZ]);
            createVertex(hyptMid);
            createVertex(sizedPos[index90]);
            createVertex(sizedPos[indexX]);
            createVertex(quadMid);
            createVertex(extrudeX);
            createVertex(extrude90);
            createVertex(quadMid);
            createVertex(sizedPos[index90]);
        }


        if(isDefault == -200 && removed == 0)
        {                                               
            vec3 newSizedPos = 0.5*(sizedPos[indexX] + sizedPos[indexZ]);
            createVertex(newSizedPos);
            createVertex(sizedPos[indexX]);
            createVertex(sizedPos[index90]);
            createVertex(sizedPos[indexZ]);
        }
      
    EndPrimitive();

}