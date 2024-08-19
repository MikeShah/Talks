#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec2 vertexTextureCoords;

out vec2 v_vertexTextureCoords;

void main()
{
    v_vertexTextureCoords= vertexTextureCoords;

	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}
