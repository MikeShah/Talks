#version 430 core

in vec3 v_vertexNormals;
in vec2 v_vertexTextureCoords;
in vec3 v_worldSpaceFragment;
uniform sampler2D uDiffTexture;
uniform vec3 uLightPos;
out vec4 color;

void main(){
		vec3 normals = normalize(v_vertexNormals);
		vec3 lightDirection = normalize(uLightPos-v_worldSpaceFragment);
		float diff = max(0.0f,dot(lightDirection,normals));

		vec3 diffuseColors = vec3(0,0,0);
		diffuseColors = texture(uDiffTexture,v_vertexTextureCoords).rgb;
		vec3 lighting = diff * diffuseColors;
		color = vec4(lighting,1.0f);
		//color = vec4(diffuseColors.r,diffuseColors.g,diffuseColors.b,1.0);
}


