#version 330
        
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 3) in vec4 in_vert_color;

out vec3 world_pos;
out vec3 normal;
out vec2 tex_coord;
out vec4 vert_color;


void main()
{
    gl_Position = vec4(in_position.xy, 0.0, 1.0);

    world_pos = in_position;
    normal = in_normal;
    tex_coord  = in_tex_coord;
    vert_color = in_vert_color;
}