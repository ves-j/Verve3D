#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform int option;

vec4 inverseCol()
{
    return (vec4(vec3(1.0 - texture(screenTexture, texCoords)), 1.0));
}


void main()
{ 
    if(option == 1)
    {
        FragColor = inverseCol();
    }
    if(option == 0)
    {
        FragColor = texture(screenTexture, texCoords);
    }
    
}