#version 330

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;
layout (location=3) in vec4 VertexTangent;

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
	vec3 tang = normalize(NM*VertexTangent.xyz);
	vec3 binorm = normalize(cross(norm, tang)) * VertexTangent.w;
	mat3 TBN = mat3(
        tang.x, binorm.x, norm.x,
        tang.y, binorm.y, norm.y,
        tang.z, binorm.z, binorm.z);
    vec3 pos = (MV*vec4(VertexPosition,1.0)).xyz;
    lightDir = TBN * (LightPos.xyz -pos);
    viewDir = TBN * normalize(-pos);
    tcoord = VertexTexCoord;
	gl_Position = MVP*vec4(VertexPosition, 1.0);	
}
