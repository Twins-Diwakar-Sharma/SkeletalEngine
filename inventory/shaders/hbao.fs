#version 430

out float color;
in vec2 fragTex;

uniform sampler2D gPosition;
uniform sampler2D gNormal;

uniform sampler2D noise;
uniform vec2 screenSize;

const int sampleCount=64;
uniform vec3 samples[sampleCount];
uniform int samplesSize;
uniform mat4 projection;


void main()
{

	vec2 noiseScale = screenSize/4.0;

	vec4 gBufferPositon = texture(gPosition, fragTex);
    vec3 fragPosition = gBufferPositon.xyz;
    vec3 fragNormal = texture(gNormal, fragTex).xyz;
	vec3 randomVec = texture(noise, fragTex * noiseScale).xyz;

	if( gBufferPositon.a == 0 )
	{
		color = (1);
		return;
	}

	vec3 tangent = normalize(randomVec - dot(randomVec,fragNormal)*fragNormal);
	vec3 bitangent = cross(fragNormal, tangent);
	mat3 TBN = mat3(tangent, bitangent, fragNormal);

	float occlusion = 0.0;
	float radius = 0.5;
	float bias = 0.025;
	for(int i=0; i<samplesSize; i++)
	{
		vec3 samplePos = TBN * samples[i];
		samplePos = fragPosition + samplePos * radius;
		vec4 offset = vec4(samplePos, 1.0);
		offset      = projection * offset;    // from view to clip-space
		offset.xyz /= offset.w;               // perspective divide
		offset.xyz  = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0  

		float sampleDepth = texture(gPosition, offset.xy).z; 
		float rangeCheck = smoothstep(0.0, 1.0, radius/abs(fragPosition.z - sampleDepth));
		occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0)*rangeCheck;  
	}

	occlusion = 1.0 - (occlusion / samplesSize);
    color = (occlusion); 
//	color = fragPosition;
}