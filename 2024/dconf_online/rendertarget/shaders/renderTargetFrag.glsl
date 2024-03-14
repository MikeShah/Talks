#version 410 core

in vec2 v_vertexTextureCoords;

layout (location=0) out vec4 color0;

uniform sampler2D screenTexture;

void main()
{
//    float time = 500.0;
//	color = vec4(v_vertexColors.r,v_vertexColors.g, v_vertexColors.b, 1.0f);
    color0 = texture(screenTexture,v_vertexTextureCoords);
//    color0 = texture(screenTexture, v_vertexTextureCoords+ 0.005*vec2( sin(time+1024.0*v_vertexTextureCoords.x),cos(time+768.0*v_vertexTextureCoords.y)) );


}
