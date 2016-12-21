#version 330

uniform	mat4 mvpMatrix;

in vec3 vertex;
in vec3 normal;

out vec3 fNormal;

void main( void )
{
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
	fNormal = normal;
}
