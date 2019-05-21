
#version 330 core

layout(location = 0) in vec3 aVertex;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aColor;

out vec2 TexCoord;
out vec3 FragPosition;
out vec3 Normals;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
//uniform float time;

void main()
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	vec4 modelPosition =  projectionMatrix * modelViewMatrix * vec4(aVertex, 1.0);
	
	TexCoord = aTexCoord;

	FragPosition = modelPosition.xyz;
	
	// la inversa de la traspuesta, se puede hacer una vez por malla en vez de una vez por vertice
	Normals = mat3(transpose(inverse(modelViewMatrix))) * aNormals;

	gl_Position =  modelPosition;
}