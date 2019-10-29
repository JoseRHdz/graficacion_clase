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
uniform sampler2D heightTex;

vec2 findOffset (vec3 v, out float height)
{
	int nSteps = int(mix(60,10,abs(v.z)));
	float bumpScale = 0.03;
	float hSteps = 1.0/nSteps;

	vec2 offset = (bumpScale*v.xy)/(nSteps*v.z);
	vec2 tc = tcoord;
	float ht = 1.0;

	height = texture(heightTex,tc).r;

	while (height<ht)
	{
		ht -= hSteps;
		tc -= offset;
		height = texture(heightTex,tc).r;
	}

	return tc;
}


bool isOcculed (float height,vec2 tc,vec3 s)
{
	int nSteps = int(mix(60,10,s.z));
	float bumpScale = 0.03;
	vec2 offset = (s.xy*bumpScale)/(nSteps*s.z);
	float hSteps = 1.0/nSteps;
	float ht = height + hSteps*0.5;

	while (height<ht && ht<1.0)
	{
		ht += hSteps;
		tc += offset;
		height = texture(heightTex,tc).r;
	}

	return ht<1.0;
}

void main ()
{
}
