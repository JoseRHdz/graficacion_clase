#version 330

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;

out vec3 color;

void main()
{
	gl_Position = vec4(VertexPosition, 1.0);
	color = VertexColor;
}
