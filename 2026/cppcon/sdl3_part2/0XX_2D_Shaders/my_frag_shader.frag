///////////////////////
//////  Shader  ///////
///////////////////////
#version 450
// Input from vertex shader (or 2D renderer defaults)
layout(location = 0) in vec4 v_color;
layout(location = 1) in vec2 v_texCoord;
// Default texture sampler
layout(set = 2, binding = 0) uniform sampler2D base_sprite;
// Output color to the screen target
layout(location = 0) out vec4 out_color;

// SLOT 0: Matches C struct 'EnvironmentUniforms' 
// Driven by: SDL_SetGPURenderStateFragmentUniforms(custom_state, 0, &env_data, ...)
layout(set = 3, binding = 0, std140) uniform EnvironmentBlock {
    float screen_width;
    float screen_height;
    float time;
    float padding; // Crucial 16-byte boundary match to mirror CPU struct padding
} env;

void main() {
    float wave = sin((v_texCoord.x * 10.0) + (env.time * 5.0));
    
    // Mix the shape's original draw color with our uniform tint and dynamic wave factor
    vec4 final_color = v_color;
    final_color.rgb += vec3(wave * 0.2);
    //out_color =  final_color;

    vec4 texture_color = texture(base_sprite, v_texCoord);
    out_color = texture_color;
}
