
#version 330 core

in vec3 _VertNormals;
in vec2 _TexCoords;
in vec3 _FragPosition;

out vec4 _FragColor;

// uniform sampler2D ourTexture;

uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{
	vec3 norm = normalize(_VertNormals);
	vec3 lightDir = normalize(lightPosition - _FragPosition);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;

	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);

	_FragColor = vec4(result, 1.0);
}
