#version 330

layout(location=0) in vec3 vertexpos;
layout(location=1) in vec3 vertexnorm;

out vec3 lightintensity;

uniform vec4 lightpos;
uniform vec3 kd;
uniform vec3 ld;

uniform mat4 MVP;

// Modelo vista
uniform mat4 MV;

// Matriz normal
uniform mat3 NM;

void main ()
{
	vec4 viewpos = MV*vec4(vertexpos,1.0);
	vec3 viewnorm = normalize(NM*vertexnorm);
	vec3 s = normalize(vec3(lightpos-viewpos));
	lightintensity = ld*kd*max(0.0,dot(s,viewnorm));
	gl_Position = MVP*vec4(vertexpos,1.0);
}
