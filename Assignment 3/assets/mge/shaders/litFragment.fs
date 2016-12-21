#version 330

uniform mat4 modelMatrix;
uniform vec3 diLightDir;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 diLightColor;

in vec3 fNormal;

out vec4 fColor;

void main( void ) 
{
	vec3 worldNormal = vec3 (modelMatrix * vec4(fNormal, 0));
	float diffuseIntensity =  max (0, dot(-diLightDir, normalize (worldNormal)));

    vec3 ambientTerm = ambientColor * diffuseColor;
    vec3 diffuseTerm = diffuseIntensity * diLightColor * diffuseColor;
    vec3 specularTerm = vec3(0,0,0);

	fColor = vec4 (ambientTerm + diffuseTerm, 1);
}
