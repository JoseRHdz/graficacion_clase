#version 330

out vec4 FragColor;
in vec3 lightintensity;

void main()
{

	FragColor = vec4(0.400,0.804,0.667,1.0)*vec4(lightintensity,1.0);
}
