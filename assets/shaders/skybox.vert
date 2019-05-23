
#version 330 core
layout (location = 0) in vec3 in_position;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;

out vec3 delete_tex_coord;

void main()
{
    mat4 view_with_negated_position = mat4(mat3(view_matrix));

    delete_tex_coord = vec3(in_position.x, -in_position.y, in_position.z);

    gl_Position = proj_matrix * view_with_negated_position * vec4(in_position, 1.0);
} 
