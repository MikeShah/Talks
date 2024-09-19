#version 460 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexNormals;
layout(location=2) in vec2 vertexTextures;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uLightPos;

out vec3 v_vertexNormals;
out vec2 v_vertexTextureCoords;
out vec3 v_worldSpaceFragment;

void main()
{
    v_vertexNormals = vertexNormals;
	v_vertexTextureCoords= vertexTextures;

	// World space the position of the vertex
	v_worldSpaceFragment = vec3(uModel*vec4(position,1.0f));

	mat4 MVP = uProjection *  uView * uModel;
	gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0f);
}

