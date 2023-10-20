#version 460

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec2 uv;

layout(binding = 0) uniform sampler2D colorTex;

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

void main()
{//textureSize(colorTex, 0)
    FragColor = vec4(0.0);
    for (int i = 0; i < NUM_OF_CONV_POINTS; i++) {
        FragColor += GAUSS_POINT[i] * texture(colorTex, uv + CONV_POINT[i] / vec2(2560.0, 1440.0));
    }
}
