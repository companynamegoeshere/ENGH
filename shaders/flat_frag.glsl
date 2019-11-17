#version 300 es
precision mediump float;

layout(location = 0) out vec4 fragColor;

in vec3 v_Pos;

void main() {

    //float p1 = abs(gl_FragCoord.x * 2.0 - 1.0);
    //float p2 = abs(gl_FragCoord.y * 2.0 - 1.0);

    //fragColor = vec4(vec3(p1 * p2), 1.0 );
    fragColor = vec4(1.0 - v_Pos.xy, 1.0, 1.0 );
    if ((abs(v_Pos.x) + abs(v_Pos.y) + abs(v_Pos.z)) > 2.6 || abs(v_Pos.x * v_Pos.y) > 0.95 || abs(v_Pos.x * v_Pos.z) > 0.95 || abs(v_Pos.z * v_Pos.y) > 0.95) {
        fragColor = vec4(vec3(0.5), 1.0);
    }
}