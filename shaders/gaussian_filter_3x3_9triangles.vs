#version 460

layout (location = 0) out vec2 uv;
layout (location = 1) out vec2 conv_point;
layout (location = 2) out float gauss_point;

#define NUM_OF_VERTICES 3

vec3 NDC[NUM_OF_VERTICES] = vec3[](
    vec3(-1.0, -1.0, 0.0),
    vec3(3.0, -1.0, 0.0),
    vec3(-1.0, 3.0, 0.0)
);

vec2 UV[NUM_OF_VERTICES] = vec2[](
    vec2(0.0, 0.0),
    vec2(2.0, 0.0),
    vec2(0.0, 2.0)
);

#define NUM_OF_CONV_POINTS 3 * 3

vec2 CONV_POINT[NUM_OF_CONV_POINTS] = vec2[](
    vec2(-1.0, 1.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0),

    vec2(-1.0, 0.0),
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),

    vec2(-1.0, -1.0),
    vec2(0.0, -1.0),
    vec2(1.0, -1.0)
);

float GAUSS_POINT[NUM_OF_CONV_POINTS] = float[](
    0.07511360795411152, 0.12384140315297398, 0.07511360795411152, 
    0.12384140315297398, 0.2041799555716581, 0.12384140315297398, 
    0.07511360795411152, 0.12384140315297398, 0.07511360795411152
);

// draw call 9 * 3 = 27

void main() {
    gl_Position = vec4(NDC[gl_VertexID % 3], 1.0f);
    uv = UV[gl_VertexID % 3];
    conv_point = CONV_POINT[gl_VertexID / 3];
    gauss_point = GAUSS_POINT[gl_VertexID / 3];
}
