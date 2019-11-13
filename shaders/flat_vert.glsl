#version 300 es
precision mediump float;

layout(location = 0) in vec3 a_Position;

out vec3 v_Pos;

void main() {
    v_Pos = a_Position;
    gl_Position = vec4(a_Position * 0.5, 1.0);
}
