#version 330

layout(location=0) in vec3 vertexpos;
layout(location=1) in vec3 vertexnorm;

out vec3 lightintensity;

uniform vec4 lightpos;
uniform float shininess;
uniform vec3 kd;
uniform vec3 ld;
uniform vec3 ka;
uniform vec3 ks;
uniform vec3 la;
uniform vec3 ls;

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
	vec3 r = reflect(-s,viewnorm);
	vec3 v = normalize(viewpos.xyz);
	vec3 ambiental = la*ka;
	vec3 specular = ls*ks*pow(max(dot(r,v),0.0),shininess);
	vec3 difuse = ld*kd*max(0.0,dot(s,viewnorm));
	lightintensity = ambiental+difuse+specular;
	gl_Position = MVP*vec4(vertexpos,1.0);
}
