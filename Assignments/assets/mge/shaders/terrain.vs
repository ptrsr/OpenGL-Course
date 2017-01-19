#version 330 

uniform	mat4 mvpMatrix;
uniform sampler2D heightMap;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 tCoord;
out vec3 fNormal;
out vec3 fPos;

vec4 CalcHeightMapNormal(sampler2D, vec2);

void main( void )
{
   vec4 bump = CalcHeightMapNormal(heightMap, uv);

	gl_Position = mvpMatrix * vec4(vertex + vec3(0, bump.a, 0), 1.0f);

	vec4 nbump = -bump;

	tCoord  = uv;
	fNormal = vec3(bump.x, bump.z, bump.y);
	fPos    = vertex;
}

vec4 CalcHeightMapNormal(sampler2D heightMap, vec2 uv)
{
	const vec2 size = vec2(2.0,0.0);
	const ivec3 off = ivec3(-1,0,1);

    vec4 wave = texture(heightMap, uv);
    float s11 = wave.x;
    float s01 = textureOffset(heightMap, uv, off.xy).x * 200;
    float s21 = textureOffset(heightMap, uv, off.zy).x * 200;
    float s10 = textureOffset(heightMap, uv, off.yx).x * 200;
    float s12 = textureOffset(heightMap, uv, off.yz).x * 200;

    vec3 va = normalize(vec3(size.xy,s21-s01));
    vec3 vb = normalize(vec3(size.yx,s12-s10));

	return vec4(cross(va, vb), s11);
}