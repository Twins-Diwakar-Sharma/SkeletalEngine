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

uniform int size;
uniform int tesselatedSize;
uniform vec2 step;
uniform vec2 position;

out vec3 fragWorldPos;

const float threshold=1.20;
const float noiseSpan = 128;


// debugs
out vec2 fragAbsSteppedObjectPos;

out vec2 fragAbsSteppedObjectPosFRAG;
out float doModeFRAG;
out vec3 fragWorldPosFRAG;

// random value between -1 and 1
vec2 randomVec2(vec2 st)
{
    st = vec2( dot(st,vec2(0.650,-0.420)),
              dot(st,vec2(-0.290,0.260)) );
    return -1.0 + 2.0*fract(sin(st)*12024.561);
}

// this needs a global const variable : noiseSpan 
float perlinNoise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

   // vec2 u = f*f*(3.0-2.0*f);
    vec2 u = f*f*f*(f*(f*6.0-15.0)+10.0);
    return mix( mix( dot( randomVec2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( randomVec2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( randomVec2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( randomVec2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

float fbm (vec2 p) 
{
  
    // Initial values
    float value = 0.0;
    float amplitude = 1;

    // Loop of octaves
    int OCTAVES = 4;
    for (int i = 0; i < OCTAVES; i++) 
    {
        value += amplitude * perlinNoise(p);
        p *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

float getProceduralHeight(float x, float z)
{
   vec2 p = vec2(x,z)/noiseSpan;
   float value = fbm(p);
  // float value = perlinNoise(p);
   float height = value * noiseSpan;
   return height;

}

vec4 quatRotate(vec4 action, vec4 victim)
{
	float ar = action.w;	float br = victim.w;
	vec3 av = action.xyz;	vec3 bv = victim.xyz;
	return vec4(ar*bv + br*av + cross(av,bv), ar*br - dot(av,bv));
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
    fragAbsSteppedObjectPos = abs((sizedPos.xz + tesselatedSize*step))/float(size);
   //fragAbsSteppedObjectPos = abs((sizedPos.xz))/float(size);
}


float getDefaultVertexHeight(vec3 worldPos, vec3 sizedPos)
{
    worldPos.y = getProceduralHeight(worldPos.x,worldPos.z);
    vec2 steppedSizedPos = sizedPos.xz + tesselatedSize*step;
    vec2 absSteppedSizedPos = abs(steppedSizedPos);
    vec2 absSteppedObjectPos = absSteppedSizedPos/float(size);
    if(absSteppedObjectPos.x >= threshold || absSteppedObjectPos.y >= threshold)
    {
        vec2 moddedValue;
        moddedValue.x = int(mod(absSteppedSizedPos.x,2*tesselatedSize));
        moddedValue.y = int(mod(absSteppedSizedPos.y,2*tesselatedSize));
        if(moddedValue.x != moddedValue.y)
        {
            vec2 alpha;
            alpha.x = (absSteppedObjectPos.x - threshold)/(2.0 - threshold);
            alpha.x = clamp(alpha.x,0,1);
            alpha.y = (absSteppedObjectPos.y - threshold)/(2.0 - threshold);
            alpha.y = clamp(alpha.y,0,1);
            float maxAlpha = max(alpha.x,alpha.y);
            float averageHeight = 0;
            if(moddedValue.x == tesselatedSize)
            {
                float heightLeft = getProceduralHeight(worldPos.x - tesselatedSize,worldPos.z);
                float heightRight = getProceduralHeight(worldPos.x + tesselatedSize,worldPos.z);
                averageHeight = (heightLeft + heightRight)/2.0;
            } 
            else if(moddedValue.y == tesselatedSize)
            {
                float heightTop = getProceduralHeight(worldPos.x,worldPos.z - tesselatedSize);
                float heightBot = getProceduralHeight(worldPos.x,worldPos.z + tesselatedSize);
                averageHeight = (heightTop + heightBot)/2.0;
            }

            worldPos.y = (1.0 - maxAlpha)*worldPos.y + maxAlpha*averageHeight;
        }
    }

    return worldPos.y;
}


float getQuadMidHeight(inout vec3 worldPos, vec3 sizedPos)
{
    worldPos.y = getProceduralHeight(worldPos.x,worldPos.z);
    vec2 steppedSizedPos = sizedPos.xz + tesselatedSize*step;
    vec2 absSteppedSizedPos = abs(steppedSizedPos);
    vec2 absSteppedObjectPos = absSteppedSizedPos/float(size);

    if(absSteppedObjectPos.x >= threshold || absSteppedObjectPos.y >= threshold)
    {
        vec2 alpha;
        alpha.x = (absSteppedObjectPos.x - threshold)/(2.0 - threshold);
        alpha.x = clamp(alpha.x,0,1);
        alpha.y = (absSteppedObjectPos.y - threshold)/(2.0 - threshold);
        alpha.y = clamp(alpha.y,0,1);
        float maxAlpha = max(alpha.x,alpha.y);
        float averageHeight = 0;
        vec2 moddedValue;
        moddedValue.x = int(mod(absSteppedSizedPos.x,2*tesselatedSize));
        moddedValue.y = int(mod(absSteppedSizedPos.y,2*tesselatedSize));
        if( moddedValue.x != moddedValue.y)
        {
            float heightLeftTop = getProceduralHeight(worldPos.x-tesselatedSize/2, worldPos.z-tesselatedSize/2);
            float heightRightBot = getProceduralHeight(worldPos.x+tesselatedSize/2, worldPos.z+tesselatedSize/2);
            averageHeight = (heightLeftTop + heightRightBot)/2.0;
        }
        else
        {
            float heightLeftBot = getProceduralHeight(worldPos.x-tesselatedSize/2, worldPos.z+tesselatedSize/2);
            float heightRightTop = getProceduralHeight(worldPos.x+tesselatedSize/2,worldPos.z-tesselatedSize/2);
            averageHeight = (heightLeftBot + heightRightTop)/2.0;
        }
        worldPos.y = (1.0 - maxAlpha)*worldPos.y + maxAlpha*averageHeight;
    }
    
    return worldPos.y;
}



void createVertex(vec3 sizedPos, int heightCondition)
{
    vec3 worldPos = sizedPos + vec3(position.x, 0, position.y);                                                                       
    // find height 
    if(heightCondition == 0 || heightCondition == 2)
        worldPos.y = getDefaultVertexHeight(worldPos,sizedPos);
    else if(heightCondition == 1)
        worldPos.y = getQuadMidHeight(worldPos,sizedPos);
    // heightCondition == 2 do nothings
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

        createVertex(sizedPos[indexX],0);
        createVertex(hyptMid,1);
        createVertex(sizedPos[index90],0);
        createVertex(sizedPos[indexZ],0);
        createVertex(quadMid,1);
        createVertex(extrudeZ,0);
        createVertex(extrude90,0);
        createVertex(quadMid,1);
        createVertex(sizedPos[index90],0);
        if(step.y != 0) // create corner
        {
            vec3 botLeft = quadMid + vec3(-step.x*tesselatedSize/2,0,-step.y*tesselatedSize/2);
            vec3 topLeft = botLeft + vec3(0,0,-step.y*tesselatedSize);
            vec3 topRight = topLeft + vec3(step.x*tesselatedSize,0,0);
            vec3 botRight = topRight + vec3(0,0,step.y*tesselatedSize);
            vec3 newQuadMid = (topLeft + botRight)/2.0;
            createVertex(sizedPos[index90],2); // degenerate
            createVertex(botLeft,2); // degenerate
            createVertex(botLeft,0);
            createVertex(topLeft,0);
            createVertex(newQuadMid,1);
            createVertex(topRight,0);
            createVertex(botRight,0);
            createVertex(newQuadMid,1);
            createVertex(botLeft,0);
        }

    }

    if(removed == 0 && step.y != 0 && objectPos[indexX].y == -step.y*2 && objectPos[index90].y == -step.y*2)
    {
        isDefault = 200;
        vec3 extrudeX = sizedPos[indexX] -step.y*vec3(0,0,tesselatedSize);
        vec3 extrude90 = sizedPos[index90] -step.y*vec3(0,0,tesselatedSize);
        vec3 quadMid =  (extrudeX + sizedPos[index90])/2.0;
        vec3 hyptMid = (sizedPos[indexX] + sizedPos[indexZ])/2.0;

        createVertex(sizedPos[indexZ],0);
        createVertex(hyptMid,1);
        createVertex(sizedPos[index90],0);
        createVertex(sizedPos[indexX],0);
        createVertex(quadMid,1);
        createVertex(extrudeX,0);
        createVertex(extrude90,0);
        createVertex(quadMid,1);
        createVertex(sizedPos[index90],0);
    }


    if(isDefault == -200 && removed == 0)
    {                                               
        vec3 hypMidSizedPos = 0.5*(sizedPos[indexX] + sizedPos[indexZ]);
        createVertex(sizedPos[indexX],0);
        createVertex(sizedPos[index90],0);
        createVertex(hypMidSizedPos,1);
        createVertex(sizedPos[indexZ],0);
    }
      
    EndPrimitive();

}