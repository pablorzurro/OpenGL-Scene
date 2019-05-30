
#version 330 core

in vec3 world_pos;
in vec3 normal;
in vec2 tex_coord;
in vec4 vert_color;

uniform sampler2D 	texture_color;
uniform vec3 		light_color;
uniform vec3 		light_pos;
uniform float 		ambient_intensity;

out vec4 out_color;

void main()
{
	vec3 normal = normalize(normal);
	vec3 light_dir = normalize(light_pos - world_pos);

	float diff = max(dot(normal, light_dir), 0.0);
	vec3 diffuse = diff * light_color;
	
	vec3 ambient = ambient_intensity * light_color;;
	vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);
	
	vec3 vertex_texture_color = texture2D(texture_color, tex_coord).rgb;

	out_color = vec4(vertex_texture_color, 0.6);
}
