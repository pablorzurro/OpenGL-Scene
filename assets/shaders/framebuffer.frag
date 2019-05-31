
 #version 330

in vec3 world_pos;
in vec2 tex_coord;

out vec4 out_color;

uniform sampler2D frame_color;

void main()
{
    vec3 color = texture (frame_color, tex_coord).rgb;

    float i = (color.r + color.g + color.b) * 0.3333333333;

    out_color = vec4(vec3(i, i, i), 1.0);
    // out_color = vec4(tex_coord, 0.5, 1.0);
}