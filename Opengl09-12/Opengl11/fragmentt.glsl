#version 450

out vec4 FragColor;
in vec3 pos;
in vec3 norm;
in vec2 tcoord;

uniform vec4 LightPos;
uniform float shininess;
uniform vec3 L;
uniform vec3 Ks;
uniform vec3 La;
uniform sampler2D colorTex;

vec3 phongModel(vec3 position,vec3 normal)
{
    vec3 s = normalize((LightPos.xyz-position));    
    vec3 color = texture(colorTex, tcoord).rgb;
    vec3 ambiental = La*color;
    float sDotN = max(dot(s,normal),0.0);
    vec3 difuse = color*sDotN;
    vec3 specular = vec3(0.0);
    if(sDotN > 0.0){    
        vec3 v = normalize(-position.xyz);
        vec3 h = normalize(v + s);
        specular = Ks*pow(max(dot(h,normal),0.0),shininess);
    }    
	return ambiental + L*(specular+difuse);
}

void main()
{
	FragColor = vec4(phongModel(pos,normalize(norm)),1.0);
}

