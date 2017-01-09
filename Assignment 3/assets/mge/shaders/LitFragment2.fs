#version 330
#define DIRLIGHTS 2

uniform mat4 modelMatrix;
uniform vec3 modelColor;
uniform vec3 cameraPos;
uniform float shininess;

in vec3 fNormal;
in vec3 fPos;

out vec4 fColor;

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirLight dirLight[DIRLIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	float diff = max (0, dot(-light.direction, normal));
	vec3 ref   = reflect(-light.direction, normal);
	float spec = pow(max(dot(viewDir, ref), 0.0f), shininess);
	
	vec3 ambient  = light.ambient * modelColor;
	vec3 diffuse  = light.diffuse * diff * modelColor;
	vec3 specular = light.specular * spec * modelColor;
	
	return (ambient + diffuse + specular);
}

void main( void ) 
{
	vec3 wNormal = vec3 (modelMatrix * vec4(fNormal, 0));
	vec3 viewDir = normalize(cameraPos -  fPos);
	vec3 color;
	
	for (int i = 0; i < DIRLIGHTS; i++)
		color += CalcDirLight(dirLight[i], wNormal, viewDir);
	
	fColor = vec4(color, 1);
}
