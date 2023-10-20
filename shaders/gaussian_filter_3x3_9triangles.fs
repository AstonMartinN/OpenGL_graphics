#version 460

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec2 uv;
layout(location = 1) in vec2 conv_point;
layout(location = 2) in float gauss_point;

layout(binding = 0) uniform sampler2D colorTex;

void main()
{//textureSize(colorTex, 0)
    FragColor = gauss_point * texture(colorTex, uv + conv_point / vec2(2560.0, 1440.0));
}
