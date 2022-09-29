#version 430

out vec4 outColor;

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
    int OCTAVES = 2;
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
	vec3 worldPos = fragWorldPos;
	float divider = 0.5;
	float value = getProceduralHeight(worldPos.x/divider, worldPos.z/divider);
	value = value/noiseSpan;
	value = smoothstep(-0.2,0.6,value);

	vec3 cloudColor = vec3(0.9,0.9,0.9);
	vec3 skyColor = vec3(0.8,0.9,1);


	outColor.rgb = (1-value)*skyColor + value;
}