#version 300 es

layout (location = 1) in vec3 v_position;

uniform mat4 mvp;

out vec4 pos;

void main()
{
  gl_Position = mvp * vec4(v_position, 1.0);
  pos = vec4(v_position, 1.0);
}
