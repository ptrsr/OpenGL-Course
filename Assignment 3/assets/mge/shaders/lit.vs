#version 330

uniform	mat4 mvpMatrix;
uniform mat4 modelMatrix;
uniform vec3 diLightDir;

in vec3 vertex;
in vec3 normal;

out float diffuseIntensity;

void main( void )
{
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
	
	vec3 worldNormal = vec3 (modelMatrix * vec4(normal, 0));
	diffuseIntensity =  max (0, dot(-diLightDir, normalize (worldNormal)));
}
