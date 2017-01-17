#version 330

uniform sampler2D textureDiffuse;
in vec2 texCoord;
out vec4 fColor;

void main( void ) {
	fColor = texture(textureDiffuse,texCoord);
}
