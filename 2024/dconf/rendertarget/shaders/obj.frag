#version 410 core

in vec3 v_vertexNormals;

out vec4 color;

void main()
{
	color = vec4(v_vertexNormals.r,v_vertexNormals.g, v_vertexNormals.b, 1.0f);
}
