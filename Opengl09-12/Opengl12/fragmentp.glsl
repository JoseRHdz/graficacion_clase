#version 450

out vec4 FragColor;
in vec3 pos;
in vec3 norm;

uniform vec4 lightpos;
uniform float shininess;
uniform vec3 kd;
uniform vec3 ld;
uniform vec3 ka;
uniform vec3 ks;
uniform vec3 la;
uniform vec3 ls;

vec3 phongModel(vec3 position,vec3 normal)
{
	vec3 s = normalize((lightpos.xyz-position));
    vec3 r = reflect(-s,normal);
    vec3 v = normalize(-position.xyz);
    vec3 ambiental = la*ka;
    vec3 specular = ls*ks*pow(max(dot(r,v),0.0),shininess);
    vec3 difuse = ld*kd*max(0.0,dot(s,normal));
	return ambiental+specular+difuse;
}

void main()
{
	FragColor = vec4(phongModel(pos,normalize(norm)),1.0);
}

