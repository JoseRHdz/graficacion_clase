#version 450

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;
layout (location=3) in vec3 VertexTangent;
layout (location=4) in vec3 VertexBinormal;

out vec3 lightDir;
out vec3 viewDir;
out vec2 tcoord;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM;
uniform vec4 LightPos;

void main()
{
	vec3 norm = normalize(NM*VertexNormal);
	vec3 tang = normalize(NM*VertexTangent);
	vec3 binorm = normalize(NM*VertexBinormal);
	mat3 TBN = transpose(mat3(tang, binorm, norm));
    vec3 pos = vec3(MV*vec4(VertexPosition,1.0));
    lightDir = normalize(TBN * (LightPos.xyz -pos));
    viewDir = TBN * normalize(-pos);
    tcoord = VertexTexCoord;
	gl_Position = MVP*vec4(VertexPosition, 1.0);	
}
