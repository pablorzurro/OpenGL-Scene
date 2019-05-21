
#version 330 core

in vec3 in_world_pos;
in vec3 in_normal;
in vec2 in_tex_coord;
in vec4 in_vert_color;

uniform sampler2D 	texture_color;
uniform vec3 		light_color;
uniform vec3 		light_pos;
uniform float 		ambient_intensity;

out vec4 out_color;

void main()
{
	vec3 normal = normalize(in_normal);
	vec3 light_dir = normalize(light_pos - in_world_pos);

	float diff = max(dot(normal, light_dir), 0.0);
	vec3 diffuse = diff * light_color;
	
	vec3 ambient = ambient_intensity * light_color;;
	vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);
	
	vec3 differential;
	differential = texture(texture_color, normalize(in_tex_coord)).rgb;

	out_color = vec4(differential, 1.0);
}
