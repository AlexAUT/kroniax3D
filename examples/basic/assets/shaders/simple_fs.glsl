#version 300 es

precision mediump float;

in vec4 pos;

layout (location = 0) out vec4 fragColor;

void main()
{
  fragColor = vec4(1.0, pos.y + 0.5, pos.x + 0.5, 1.0);
}
