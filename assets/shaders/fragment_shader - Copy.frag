
#version 330 core

uniform Uniforms {
	// sampler2D texture_color;
   	vec3 light_color;
	vec3 light_pos;
	float ambient_intensity;
} u;

in VertexData {
    vec3 world_pos;
	vec3 normal;
	vec2 tex_coord;
} i;

out vec4 out_color;

void main()
{
	vec3 normal = normalize(i.normal);
	vec3 light_dir = normalize(u.light_pos - i.world_pos);

	float diff = max(dot(normal, light_dir), 0.0);
	vec3 diffuse = diff * u.light_color;

	vec3 ambient = u.ambient_intensity * u.light_color;
	vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);

	out_color = vec4(result, 1.0);
}
