#version 430

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in TRI {
    vec2 fragAbsSteppedObjectPos;
    float doMode;
    vec3 fragWorldPos;
} tri[];

out vec2 fragAbsSteppedObjectPosFRAG;
out float doModeFRAG;
out vec3 fragWorldPosFRAG;

void something(int index)
{
    gl_Position = gl_in[index].gl_Position;
    fragAbsSteppedObjectPosFRAG =   tri[index].fragAbsSteppedObjectPos;
    doModeFRAG  =   tri[index].doMode;
    fragWorldPosFRAG = tri[index].fragWorldPos;
    
    EmitVertex();
}

void main()
{
    something(0);
    something(1);
    something(2);

    EndPrimitive();
}
