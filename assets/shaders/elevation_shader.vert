
// Triangular alrededor del vertex de entrada con las uvs siendo en tres cuadrantes y luego calcular su producto vectorial 

#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 3) in vec4 in_vert_color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform sampler2D height_map;

out vec3 world_pos;
out vec3 normal;
out vec2 tex_coord;
out vec4 vert_color;

void main()
{
	mat4 model_view_matrix = view_matrix * model_matrix;

	vec4 texture_color = texture(height_map, in_tex_coord);
	float texture_color_grey = (texture_color.x + texture_color.y + texture_color.z) / 3.0;

	float pos_y = in_position.y + texture_color_grey / 2.0;

	vec4 model_pos = model_view_matrix * vec4(in_position.x, pos_y, in_position.z, 1.0);
	gl_Position = proj_matrix * model_pos;

	vec4 n = model_view_matrix * vec4(in_normal, 0.0);

	world_pos = model_pos.xyz;
	normal = n.xyz;
	tex_coord= in_tex_coord;	
	vert_color = in_vert_color;
}
