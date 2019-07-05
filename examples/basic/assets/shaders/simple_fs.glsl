#version 300 es

precision mediump float;

in vec4 pos;
in vec4 normal;

layout (location = 0) out vec4 fragColor;

uniform vec4 color;

void main()
{
  float diffuse = max(0.0, dot(normal, vec4(0.0, 0.0, 1.0f, 0.0)));
  fragColor = color * clamp(0.5 + 0.5 * diffuse, 0.0, 1.0);

  fragColor.a = 1.0;
}
