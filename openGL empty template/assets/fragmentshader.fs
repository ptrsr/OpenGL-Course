#version 330

in vec2 vuv;
out vec4 sColor;
uniform float checkerCount;
uniform vec2 mousepos;

void main (void) 
{
    float checkerSize = 1.0f/checkerCount;
    float brightness = 0.0f;
    float spotrange = 150.0f;
    float spotbrightness = 1.0f;
    float ambientIntensity = 0.1f;
    vec4 ambientColor = vec4(1,0,0,1);
    vec4 spotcolor = vec4(1,1,1,1);

    float dist = distance (vec3(mousepos.x, mousepos.y, 0), vec3(gl_FragCoord));

    brightness = 1 - dist/spotrange;
    if (brightness < 0 ) { brightness = 0; }

    float xmod = mod(vuv.x, checkerSize*2);
    float ymod = mod(vuv.y, checkerSize*2);

    if ((xmod <= checkerSize && ymod <= checkerSize) || (xmod > checkerSize && ymod > checkerSize))
    {
        sColor = vec4(1,1,1,1);
    }
    else
    {
        sColor = vec4(0,0,0,1);
    }

    sColor *= ambientColor * ambientIntensity + spotcolor * brightness;
}
