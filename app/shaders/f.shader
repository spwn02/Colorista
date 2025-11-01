#version 460

layout(location = 0) out vec4 v_color;

in vec2 o_position;

void main()
{
  v_color = vec4(o_position / 2 + 0.5, 1.0, 1.0);
}