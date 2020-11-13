#version 300 es
precision mediump float;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform vec3 cameraPos;

out vec3 v_Pos;
out vec3 v_WorldPos;
out vec3 v_Normal;

void main() {
    v_Pos = a_Position;
    v_Normal = mat3(transpose(inverse(transform))) * a_Normal;

    vec4 pos = transform * vec4(a_Position, 1.0);
    v_WorldPos = pos.xyz;
    gl_Position = projection * view * pos;
}
