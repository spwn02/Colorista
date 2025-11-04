#version 460

layout(location = 0) in vec2 i_position;
layout(location = 1) in vec4 i_color;

out vec4 o_color;

void main()
{
  gl_Position = vec4(i_position, 0.0, 1.0);
  o_color = i_color;
}