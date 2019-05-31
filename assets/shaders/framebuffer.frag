
 #version 330
        
uniform sampler2D texture_color;

in vec3 world_pos;
in vec3 normal;
in vec2 tex_coord;
in vec4 vert_color;

out vec4 out_color;

void main()
{
    vec3 color = texture (texture_color, tex_coord).rgb;

    float i = (color.r + color.g + color.b) * 0.3333333333;

    // out_color = vec4(vec3(i, i, i), 0.0);
    out_color = vec4(tex_coord.xy, 155.0, 1.0);
}