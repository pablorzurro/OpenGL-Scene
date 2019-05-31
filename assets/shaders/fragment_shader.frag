
#version 330 core

in vec3 world_pos;
in vec3 normal;
in vec2 tex_coord;
in vec4 vert_color;

uniform sampler2D 	texture_color;
uniform vec3 		light_color;
uniform vec3 		light_pos;
uniform vec3 		view_pos;
uniform float 		ambient_intensity;

out vec4 out_color;

void main()
{
	float specular_strength = 0.5;

	vec3 ambient = ambient_intensity * light_color;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - world_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;
    
    // specular
    vec3 view_dir = normalize(view_pos - world_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);  

    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 128);

    vec3 specular = specular_strength * spec * light_color;  

	vec3 vertex_texture_color = texture2D(texture_color, tex_coord).rgb;
	
	vec3 result = (ambient + diffuse + specular) * vertex_texture_color;

	out_color =vec4(result, 1.0);
}
