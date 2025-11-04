#version 460

layout(location = 0) out vec4 v_color;

in vec4 o_color;

void main()
{
  v_color = o_color;
}