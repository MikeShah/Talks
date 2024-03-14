#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexNormals;

out vec3 v_vertexNormals;

void main()
{
    v_vertexNormals = vertexNormals;

	float rot_y = 230.0f;
	mat4 ry = mat4( cos(rot_y),0.0, -sin(rot_y), 0.0,
					0.0, 1.0, 0.0, 0.0,
					sin(rot_y), 0.0, cos(rot_y), 0.0,
					0.0,0.0,0.0,1.0);

	gl_Position = ry * vec4(position.x, position.y-0.4f, position.z, 1.0f);
}
