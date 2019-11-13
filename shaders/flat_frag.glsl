#version 300 es
precision mediump float;

layout(location = 0) out vec4 fragColor;

in vec3 v_Pos;

void main() {

    //float p1 = abs(gl_FragCoord.x * 2.0 - 1.0);
    //float p2 = abs(gl_FragCoord.y * 2.0 - 1.0);

    //fragColor = vec4(vec3(p1 * p2), 1.0 );
    fragColor = vec4(1.0 - v_Pos.xy, 1.0, 1.0 );
}