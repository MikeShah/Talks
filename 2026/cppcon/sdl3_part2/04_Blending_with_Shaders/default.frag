#version 460

layout(set = 3, binding = 0, std140) uniform Constants
{
    float color_scale;
} _27;

layout(set = 2, binding = 0) uniform texture2D u_texture;
layout(set = 2, binding = 0) uniform sampler u_sampler;

layout(location = 0) in vec4 input_v_color;
layout(location = 1) in vec2 input_v_uv;
layout(location = 0) out vec4 _entryPointOutput_o_color;

void main()
{
    vec4 _102 = texture(sampler2D(u_texture, u_sampler), input_v_uv);
    _entryPointOutput_o_color = vec4(_102.xyz * _27.color_scale, _102.w) * input_v_color;
}





