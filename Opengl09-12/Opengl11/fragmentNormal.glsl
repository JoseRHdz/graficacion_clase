#version 330

out vec4 FragColor;
in vec3 lightDir;
in vec3 viewDir;
in vec2 tcoord;

uniform float shininess;
uniform vec3 L;
uniform vec3 Ks;
uniform vec3 La;
uniform sampler2D colorTex;
uniform sampler2D normalTex;

vec3 phongModel(vec3 n)
{
    vec3 color = texture(colorTex, tcoord).rgb;
    vec3 s = normalize(lightDir);
    vec3 ambient = La*color;
    float sDotN = max(dot(s,n),0.0);
    vec3 difuse = color*sDotN;
    vec3 specular = vec3(0.0);
    if(sDotN > 0.0){    
        vec3 v = normalize(viewDir);
        vec3 h = normalize(v + s);
        specular = Ks*pow(max(dot(h,n),0.0),shininess);
    }    
	return ambient + L*(specular+difuse);
}

void main()
{
	vec3 normal = texture(normalTex, tcoord).rgb;
	normal = normalize(2.0 * normal -1.0);
	FragColor = vec4(phongModel(normal),1.0);
}

