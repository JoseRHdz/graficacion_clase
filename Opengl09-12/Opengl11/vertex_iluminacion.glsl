#version 330

layout(location=0) in vec3 vertexPos;
layout(location=1) in vec3 vertexNorm;

out vec3 pos;
out vec3 norm;

uniform mat4 MVP;

// Modelo vista
uniform mat4 MV;

//NormalMatrix
uniform mat3 NM;


void main ()
{
	norm = normalize(NM*vertexNorm);
	pos = (MV*vec4(vertexPos,1.f)).xyz;
	gl_Position = MVP*vec4(vertexPos,1.f);
}
