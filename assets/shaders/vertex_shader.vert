
#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 vertColor;

out vec2 TexCoord;
out vec3 FragPosition;
out vec3 Normals;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
//uniform float time;

void main()
{
	//float offset = ((vertex.x * vertex.x) + (vertex.z * vertex.z));
	//float frequency = 0.3;
	//float speed = 2;
	//sin(time * speed + vertex.x * frequency)

	vec4 modelPosition = modelViewMatrix * vec4(vertex, 1.0);
	
	TexCoord = aTexCoord;

	FragPosition = modelPosition.xyz;
	
	// la inversa de la traspuesta, se puede hacer una vez por malla en vez de una vez por vertice
	Normals = mat3(transpose(inverse(modelViewMatrix))) * aNormals;
	gl_Position = projectionMatrix * modelPosition;
}
