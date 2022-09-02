#version 430

layout (location=0) out vec4 gPosition;
layout (location=1) out vec4 gAlbedo;
layout (location=2) out vec4 gNormal;

in vec3 fragWorldPos;


struct DirectionalLight
{
	vec3 dir;
	vec3 col;
};

uniform DirectionalLight sun;

const float threshold = 1.20;
const float noiseSpan = 128;

in vec3 camPos;

// random value between -1 and 1
vec2 randomVec2(vec2 st)
{
    st = vec2( dot(st,vec2(0.650,-0.420)),
              dot(st,vec2(-0.290,0.260)) );
    return -1.0 + 2.0*fract(sin(st)*12024.561);
}

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

float fbm(vec2 p) 
{
  
    // Initial values
    float value = 0.0;
    float amplitude = 0.5;

    // Loop of octaves
    int OCTAVES = 12;
    for (int i = 0; i < OCTAVES; i++) 
    {
        value += amplitude * (perlinNoise(p));
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

vec3 getNormal(float x, float y)
{
    float h = 0.2;
    vec3 me = vec3(x,0,y);
  
    vec3 meX = vec3(x+h,0,y);
    vec3 meZ = vec3(x,0,y+h);

    me.y = getProceduralHeight(me.x,me.z);
    meX.y = getProceduralHeight(meX.x,meX.z);
    meZ.y = getProceduralHeight(meZ.x,meZ.z);

    vec3 ans = normalize(cross(meZ-me,meX-me));

    return ans;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////

const float exp =  2.7182818;

void main()
{
    vec4 outColor;
	vec3 worldPos = fragWorldPos;

	//vec3 fragNorm = getNormal(worldPos.x,worldPos.z);
    vec3 fragNorm = vec3(0,1,0);

	vec3 toLight = normalize(-1*sun.dir);	
	float diffuse = max(dot(toLight,fragNorm),0.2);
    vec3 sunCol = vec3(1,1,0.8);
	vec3 diffuseColor = diffuse*sunCol;
	vec4 color = vec4(0.86, 0.56, 0.5, 1);
   // vec4 color = vec4(0.1,0.1,0.4,1);

/*
    float stoneLambda = smoothstep(0.4,0.75,fragNorm.y);
   // vec3 grassColor = vec3(0.42, 0.52, 0.09);
    vec3 stoneColor = vec3(0.4,0.3,0.4);
    color.rgb = (1.0 - stoneLambda)*color.rgb + stoneLambda*(stoneColor);
    
    float grassLambda = 0;
    if(fragNorm.y > 0.85)
        grassLambda = 1;

    vec3 grassColor = vec3(0.42, 0.52, 0.09);
    color.rgb = (1.0 - grassLambda)*color.rgb + grassLambda*(grassColor);
*/
	outColor = vec4(diffuseColor,1.0) * color;

	//outColor = color;

    float t = length(worldPos.xz - camPos.xz);
    //float lamda = pow(exp,-0.005*t);
    vec4 lamda = vec4(pow(exp,-0.004*t),pow(exp,-0.008*t),pow(exp,-0.016*t),1);
    vec4 fogColor = vec4(0.51,0.51,0.51,1);
    outColor = (vec4(1.0) - lamda)*fogColor + lamda*outColor;


/*
    vec3 skyColor = vec3(0.8,0.9,1);
    outColor.rgb += ((1 + fragNorm.y)/20.0)*skyColor;
    outColor.rgb += sunCol/10;

    outColor.rgb = smoothstep(0,1,outColor.rgb);
*/

    gPosition = vec4(worldPos,1);
    gAlbedo = outColor;
    gNormal = vec4(fragNorm,1);
}