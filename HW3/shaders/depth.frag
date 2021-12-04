#version 330 core

in vec4 position; // raw vertex_position in the model coord
in vec3 normal;   // raw vertex_normal in the model coord

// Output the frag color
out vec4 fragColor;

void main (void){
    // far, near are from camera's clipping plane
    float near = 0.01f;
    float far = 100.0f;
    float ndc_z = 2 * gl_FragCoord.z - 1;
    float lin_z = (2.0 * near * far) / (far + near - ndc_z * (far - near)); 
    fragColor = vec4(vec3(lin_z / (far - near)), 1.0f);
}
