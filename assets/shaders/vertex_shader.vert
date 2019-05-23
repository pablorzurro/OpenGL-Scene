
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 3) in vec4 in_vert_color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec3 delete_world_pos;
out vec3 delete_normal;
out vec2 delete_tex_coord;
out vec4 delete_color;

void main()
{
	mat4 model_view_matrix = view_matrix * model_matrix;

	vec4 model_pos = model_view_matrix * vec4(in_position, 1.0);
	gl_Position = proj_matrix * model_pos;

	vec4 normal =  model_view_matrix * vec4(in_normal, 0.0);

	delete_world_pos = model_pos.xyz;
	delete_normal = normal.xyz;
	delete_tex_coord= in_tex_coord;	
	delete_color = in_vert_color;
}
