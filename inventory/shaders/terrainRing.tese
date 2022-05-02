#version 430
layout(quads, equal_spacing, cw) in;

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

    float doMode = 0;

    vec3 sizedPos = interpolatedPos.xyz;

    vec3 worldPos =  sizedPos + vec3(position.x,0,position.y);
    
    // cut the overlaps = push them behind sort of
    if(sizedPos.x == 2*size && step.x == 1)
    {
        worldPos.x = worldPos.x - tesselatedSize;
    }
    if(sizedPos.x == -2*size && step.x == -1)
    {
        worldPos.x = worldPos.x + tesselatedSize;
    }
    if(sizedPos.z == 2*size && step.y == 1)
    {
        worldPos.z = worldPos.z - tesselatedSize;
    }
    if(sizedPos.z == -2*size && step.y == -1)
    {
        worldPos.z = worldPos.z + tesselatedSize;
    }

    gl_Position = interpolatedPos;


}
