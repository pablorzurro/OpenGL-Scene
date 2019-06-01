
#version 330 core

in vec3 tex_coord;

uniform samplerCube skyboxCubeMap;

out vec4 out_color;

void main() 
{    
    // out_color = vec4(0.1,0.1, 0.1, 0.0)  + vec4(tex_coord.xyz, 1.0);
    out_color = texture(skyboxCubeMap, tex_coord);
    // out_color = vec4(tex_coord.xyz, 1.0);
}
