
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

out vec3 TexCoords;

void main()
{
    TexCoords = aPos;

    mat4 view_with_negated_position = mat4(mat3(view_matrix));

    gl_Position = projection_matrix * view_with_negated_position * vec4(aPos, 1.0);
} 
