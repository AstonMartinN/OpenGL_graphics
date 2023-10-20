#version 460

layout (location = 0) out vec2 uv;

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

// draw call 3

void main() {
    gl_Position = vec4(NDC[gl_VertexID], 1.0f);
    uv = UV[gl_VertexID];
}
