#version 330

in vec4 vertex;
in vec2 uv;
out vec2 vuv;

uniform vec2 offset;

void main (void)
{
    vuv = uv;
    gl_Position = vertex + vec4(offset,0,0);
}

