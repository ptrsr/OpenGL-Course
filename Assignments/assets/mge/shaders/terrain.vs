//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;
uniform sampler2D heightMap;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord;

void main( void )
{
	vec4 hColor = texture(heightMap, uv);
	float height = (hColor.r + hColor.b + hColor.g) / 3.0f;
	vec3 nVertex = vertex + vec3(0, height, 0);
	gl_Position = mvpMatrix * vec4(nVertex, 1.0f);
	texCoord = uv;
}
