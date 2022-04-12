#version 430

layout (vertices = 4) out;


uniform int LOD;

void main(void)
{
    if (gl_InvocationID == 0) // to not do same stuff 4 times
    {   
        // calculate A, B, C, D,E, F - based on your algorithm, or just set constants
        // set 2 innner tess. levels
        gl_TessLevelInner[0] = LOD;
        gl_TessLevelInner[1] = 2;
        // set 4 outer tess. levels (for each edge)
        gl_TessLevelOuter[0] = 2;
        gl_TessLevelOuter[1] = LOD;
        gl_TessLevelOuter[2] = 2;
        gl_TessLevelOuter[3] = LOD;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

}