#version 330
#define DLIGHTS 0
#define PLIGHTS 0
#define SLIGHTS 1

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
	
}; uniform DirLight dirLight[5];

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
}; uniform PointLight pointLight[5];

struct SpotLight
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
	float cutOff;
	float outerCutOff;
	
}; uniform SpotLight spotLight[5];


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	float diff = max(0, dot(-light.direction, normal));
	vec3 ref   = reflect(light.direction, normal);
	float spec = pow(max(dot(viewDir, ref), 0), shininess);
	
	vec3 ambient  = light.ambient * modelColor;
	vec3 diffuse  = light.diffuse * diff * modelColor;
	vec3 specular = light.specular * spec * modelColor;
	
	return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(fPos - light.position);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
    
	
    float distance    = length(light.position - fPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
				 
    vec3 ambient  = light.ambient  * modelColor * attenuation;
    vec3 diffuse  = light.diffuse  * diff * modelColor * attenuation;
    vec3 specular = light.specular * spec * modelColor * attenuation;

	return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(fPos - light.position);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
	
	float distance    = length(light.position - fPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance)); 
				 
    float theta = dot(lightDir, light.direction); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f) * attenuation;
	
    vec3 ambient  = light.ambient  * intensity * modelColor;
    vec3 diffuse  = light.diffuse  * intensity * diff * modelColor;
    vec3 specular = light.specular * intensity * spec * modelColor;

    return (ambient + diffuse + specular);
}

void main( void ) 
{
	vec3 wNormal = vec3 (modelMatrix * vec4(fNormal, 0));
	vec3 viewDir = normalize(cameraPos -  fPos);
	vec3 color;
	
	for (int i = 0; i < DLIGHTS; i++)
		color += CalcDirLight(dirLight[i], wNormal, viewDir);
	
	for (int i = 0; i < PLIGHTS; i++)
		color += CalcPointLight(pointLight[i], wNormal, viewDir);
	
	for (int i = 0; i < SLIGHTS; i++)
		color += CalcSpotLight(spotLight[i], wNormal, viewDir);
	
	fColor = vec4(color, 1);
}
