#version 460

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec2 uv;

layout(binding = 0) uniform sampler2D colorTex;

void main()
{
	FragColor = vec4(0.0, 1.0, 0.0, 1.0); //texture(colorTex, uv);
}
