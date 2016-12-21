#version 330

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 diLightColor;

in float diffuseIntensity;

out vec4 fColor;

void main( void ) 
{
    vec3 ambientTerm = ambientColor * diffuseColor;
    vec3 diffuseTerm = diffuseIntensity * diLightColor * diffuseColor;
    vec3 specularTerm = vec3(0,0,0);

	fColor = vec4 (ambientTerm + diffuseTerm, 1);
	//fColor = vec4 (vec3(1.0f,0.0f,0.0f), 1);
}
