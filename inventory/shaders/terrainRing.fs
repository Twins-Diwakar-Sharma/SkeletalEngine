#version 430

out vec4 outColor;

in vec3 fragWorldPos;


struct DirectionalLight
{
	vec3 dir;
	vec3 col;
};

uniform DirectionalLight sun;

uniform sampler2D heightMap;
uniform int heightMapSize;


// debugs
in vec2 fragAbsSteppedObjectPos;
in float doMode;

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
	vec3 worldPos = fragWorldPos;

	float hL = getHeightFromTexture(worldPos.x-1, worldPos.z);
	float hR = getHeightFromTexture(worldPos.x+1, worldPos.z);
	float hD = getHeightFromTexture(worldPos.x, worldPos.z-1);
	float hU = getHeightFromTexture(worldPos.x, worldPos.z+1);


	vec3 normFromTex = normalize(vec3(hL-hR, 2.0, hD-hU));

	vec3 fragNorm = normFromTex;

	vec3 toLight = normalize(-1*sun.dir);	
	float diffuse = max(dot(toLight,fragNorm),0.1);
	vec3 diffuseColor = diffuse*sun.col;
	vec4 color = vec4(1,0,0,1);
    
    // debug
    if(fragAbsSteppedObjectPos.x > 1.5 || fragAbsSteppedObjectPos.y > 1.5)
        color = (1.0-doMode)*vec4(0.5,0,1,1) + doMode*vec4(0,0.5,1,1);

	outColor = vec4(diffuseColor,1.0) * color;
	//outColor = color;
}