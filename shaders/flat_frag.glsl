#version 300 es
precision mediump float;

layout(location = 0) out vec4 fragColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform vec3 cameraPos;

in vec3 v_Pos;
in vec3 v_WorldPos;
in vec3 v_Normal;

struct LightData {
    vec3 position;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
LightData light = LightData(
vec3(1.2f, 1.0f, -2.0f),
vec3(1.0),

vec3(0.2, 0.2, 0.2),
vec3(0.5, 0.5, 0.5),
vec3(1.0, 1.0, 1.0),

1.0f,
0.09f,
0.032f
);

float ambientStrength = 0.2;
vec3 color = vec3(0.7, 0.4, 0.1);

void main() {

    /*vec3 color;
    if ((abs(v_Pos.x) + abs(v_Pos.y) + abs(v_Pos.z)) > 2.6 || abs(v_Pos.x * v_Pos.y) > 0.95 || abs(v_Pos.x * v_Pos.z) > 0.95 || abs(v_Pos.z * v_Pos.y) > 0.95) {
        color = vec3(0.5);
    } else {
        color = vec3(1.0 - v_Pos.xy, 1.0);
    }*/

    vec3 lightDir = normalize(-light.position - v_WorldPos);
    vec3 norm = normalize(v_Normal);


    vec3 ambient = ambientStrength * light.color;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - v_WorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec * light.color;


    float distance    = length(light.position - v_WorldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular) * color;

    fragColor = vec4(result, 1.0);
}