#version 450

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;

out vec3 pos;
out vec3 norm;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 N;

out vec3 color;

void main()
{
    pos = (MV*vec4(VertexPosition,1.0)).xyz;
    norm = N*VertexNormal;
	gl_Position = MVP*vec4(VertexPosition, 1.0);	
}
