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
  
    gl_Position = interpolatedPos;

}
