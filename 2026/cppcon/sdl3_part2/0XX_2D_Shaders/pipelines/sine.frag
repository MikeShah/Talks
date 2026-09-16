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
    // mouse coordinates with inverted coordinates for the 'y' to match cpu and gpu layout
    vec2 mouse = vec2(gs.mouseX/gs.screen_width,(gs.mouseY/gs.screen_height));
    float wave = sin((v_texCoord.x * 10.0) + (gs.time * 5.0));

    // Mix the shape's original draw color with our uniform tint and dynamic wave factor
    vec4 final_color = v_color;
    final_color.rgb += vec3(wave * 0.2);
    out_color =  final_color;

    // The original shader
    vec4 texture_color = texture(base_sprite, v_texCoord);
    out_color = mix(texture_color,final_color,0.25);
    if(distance(mouse,v_texCoord) < 0.25){
      out_color = mix(texture_color,vec4(1.0,1.0,1.0,0.5),0.5);
    }
}
