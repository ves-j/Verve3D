#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform int option;
uniform float gamma;

const float offset_x = 1.0f / 800.0f;  
const float offset_y = 1.0f / 800.0f;  

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x,  offset_y), vec2( 0.0f,    offset_y), vec2( offset_x,  offset_y),
    vec2(-offset_x,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset_x,  0.0f),
    vec2(-offset_x, -offset_y), vec2( 0.0f,   -offset_y), vec2( offset_x, -offset_y) 
);



vec4 inverseCol()
{
    return (vec4(vec3(1.0 - texture(screenTexture, texCoords)), 1.0));
}

vec4 blur()
{
    float blurKernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * blurKernel[i];
    return (vec4(color, 1.0f));
}

vec4 sharpen()
{
    float sharpenKernel[9] = float[](
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0
    );

    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * sharpenKernel[i];
    return (vec4(color, 1.0f));
}

vec4 emboss()
{
    float embossKernel[9] = float[](
        -2, -1,  0,
        -1,  1,  1,
         0,  1,  2
    );

    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * embossKernel[i];
    return (vec4(color, 1.0f));
}

vec4 outline()
{
    float testKernel[9] = float[](
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    );

    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * testKernel[i];
    return (vec4(color, 1.0f));
}

void main()
{ 
    if(option == 1)
    {
        if(gl_FragCoord.x < 1262 && gl_FragCoord.x > 8 && gl_FragCoord.y < 854 && gl_FragCoord.y > 9)
        {
            FragColor = inverseCol();
        }
        else
        {
            FragColor = texture(screenTexture, texCoords);
        }
        
    }
    if(option == 2)
    {
        if(gl_FragCoord.x < 1262 && gl_FragCoord.x > 8 && gl_FragCoord.y < 854 && gl_FragCoord.y > 9)
        {
            vec4 tex = texture(screenTexture, texCoords);
            float average =  0.2126 * tex.r + 0.7152 * tex.g + 0.0722 * tex.b;
            FragColor = vec4(average, average, average, 1.0);
        }
        else
        {
            FragColor = texture(screenTexture, texCoords);
        }
        
    }

    if(option == 3)
    {
        if(gl_FragCoord.x < 1262 && gl_FragCoord.x > 8 && gl_FragCoord.y < 854 && gl_FragCoord.y > 9)
        {
            FragColor = blur();
        }
        else
        {
            FragColor = texture(screenTexture, texCoords);
        }
    }

    if(option == 4)
    {
        if(gl_FragCoord.x < 1262 && gl_FragCoord.x > 8 && gl_FragCoord.y < 854 && gl_FragCoord.y > 9)
        {
            FragColor = sharpen();
        }
        else
        {
            FragColor = texture(screenTexture, texCoords);
        }
    }

    if(option == 5)
    {
        if(gl_FragCoord.x < 1262 && gl_FragCoord.x > 8 && gl_FragCoord.y < 854 && gl_FragCoord.y > 9)
        {
            FragColor = emboss();
        }
        else
        {
            FragColor = texture(screenTexture, texCoords);
        }
    }

    if(option == 6)
    {
        if(gl_FragCoord.x < 1262 && gl_FragCoord.x > 8 && gl_FragCoord.y < 854 && gl_FragCoord.y > 9)
        {
            FragColor = outline();
        }
        else
        {
            FragColor = texture(screenTexture, texCoords);
        }
    }

    if(option == 0)
    {
        FragColor = texture(screenTexture, texCoords);
    }
    
}