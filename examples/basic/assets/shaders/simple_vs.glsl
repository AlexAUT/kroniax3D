#version 300 es

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 6) in vec2 v_uv;

uniform mat4 mvp;
uniform mat4 view;

out vec4 pos;
out vec4 normal;
out vec2 uv;

void main()
{
  gl_Position = mvp * vec4(v_position, 1.0);
  normal = view * vec4(v_normal, 0.0);
  pos = vec4(v_position, 1.0);
  uv = v_uv;
}
