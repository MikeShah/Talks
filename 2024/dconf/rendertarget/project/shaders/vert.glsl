#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;

out vec3 v_vertexColors;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
		v_vertexColors = vertexColors;

		mat4 MVP = uProjection * uView * uModel;
		gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0f);
}
