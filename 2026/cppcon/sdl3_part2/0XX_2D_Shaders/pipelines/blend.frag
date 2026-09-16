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

// SLOT 0: Matches C struct 'GameStateUniforms' 
layout(set = 3, binding = 0, std140) uniform GameStateUniforms {
    float screen_width;
    float screen_height;
    float mouseX;
    float mouseY;
    float time;
    float color_scale;
    float alpha;
    float padding;
} gs;

void main() {

    // The original shader
    vec4 texture_color = texture(base_sprite, v_texCoord);
    // Do the color keying ourselves
    if(texture_color.r == 1.0 && texture_color.b == 1.0){
      out_color = vec4(0.0,0.0,0.0,0.0);
    }else{
      out_color = vec4(texture_color.rgb,gs.alpha);
    }
}
