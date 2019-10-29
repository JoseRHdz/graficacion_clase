#version 330

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;

out vec3 pos;
out vec3 norm;
out vec2 tcoord;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM;

void main()
{
    pos = (MV*vec4(VertexPosition,1.0)).xyz;
    norm = NM*VertexNormal;
    tcoord = VertexTexCoord;
	gl_Position = MVP*vec4(VertexPosition, 1.0);	
}
