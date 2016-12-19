//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1
#define PI 3.141592653589f

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;
uniform int		phases;
uniform float   clock;

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in int phase;

out vec2 texCoord; //make sure the texture coord is interpolated

void main( void )
{
	float multi = sin((float(phase) / float(phases)) * PI) + 1;
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex * multi, 1.0f);
	texCoord = uv;
}
