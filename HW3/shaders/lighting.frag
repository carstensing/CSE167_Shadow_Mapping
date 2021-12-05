#version 330 core

in vec4 position; // raw vertex_position in the model coord
in vec3 normal;   // raw vertex_normal in the model coord

uniform mat4 modelview; // from model coord to eye coord
uniform mat4 view;      // from world coord to eye coord

uniform sampler2D depthMap;

// Material parameters
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emision;
uniform float shininess;

// Light source parameters
const int maximal_allowed_lights = 10;
uniform bool enablelighting;
uniform int nlights;
uniform vec4 lightpositions[ maximal_allowed_lights ]; // world coord
uniform vec4 lightcolors[ maximal_allowed_lights ];

// Output the frag color
out vec4 fragColor;

void main (void){
    if (!enablelighting){
        // Default normal coloring
        vec3 N = normalize(normal);
        fragColor = vec4(0.5f*N + 0.5f , 1.0f);

        float Depth = texture(depthMap, position.xy).x;
        // Depth = 1.0 - (1.0 - Depth) * 25.0;
        fragColor = vec4(vec3(Depth), 1.0f);
        // fragColor = texture(depthMap, position.xy);

    } else {
        mat4 camera = inverse(view);
        mat4 model = camera * modelview;
        mat3 model_A = mat3(model[0][0], model[0][1], model[0][2], model[1][0], model[1][1], model[1][2], model[2][0], model[2][1], model[2][2]);
        mat3 model_normalizer = inverse(transpose(model_A));
        vec3 n = normalize(vec3(model_normalizer * normalize(normal)));

        vec4 ver_pos = vec4(model * position);
        vec4 eye = vec4(camera[3][0], camera[3][1], camera[3][2], camera[3][3]);
        vec3 v = normalize(vec3(ver_pos.w*eye.xyz - eye.w*ver_pos.xyz));

        vec4 lights = vec4(0);
        for (int i=0; i < nlights; i++) {
            vec3 l = normalize(vec3(ver_pos.w*lightpositions[i].xyz - lightpositions[i].w*ver_pos.xyz));
            vec3 h = normalize(v+l);
            lights += (ambient + diffuse*max(dot(n,l), 0.0f) + specular*pow(max(dot(n,h), 0.0f), shininess)) * lightcolors[i];
        }
        fragColor = emision + lights;
    }
}
