
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 3) in vec4 in_vert_color;

uniform Uniforms {
    mat4 model_view_matrix;
	mat4 proj_matrix;
} u;

out VertexData {
    vec3 world_pos;
	vec3 normal;
	vec2 tex_coord;
} o;

void main()
{
	vec4 model_pos = u.model_view_matrix * vec4(in_position, 1.0);
	o.world_pos = model_pos.xyz;
	gl_Position = u.proj_matrix * model_pos;

	vec4 normal =  u.model_view_matrix * vec4(in_normal, 0.0);
	o.normal = normal.xyz;
	o.tex_coord= in_tex_coord;	
}
