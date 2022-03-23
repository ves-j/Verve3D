#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;
uniform float lx;
uniform float ly;
uniform float lz;

mat4 buildTranslation(float x, float y, float z){
	return mat4(	1.0,		0,			0,			0,
			 		0, 		  1.0,			0,			0,
					0, 			0,		  1.0,			0,
					x, 			y,			z, 			1.0);
}

void main()
{
	gl_Position = camMatrix * model * vec4((aPos.x + lx), (aPos.y + ly), (aPos.z + lz), 1.0f);
}