#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform float outlining;

// imgui uniforms
uniform float size;
uniform float px;
uniform float py;
uniform float pz;

uniform float rx;
uniform float ry;
uniform float rz;

mat4 buildTranslation(float x, float y, float z){
	return mat4(	1.0,		0,			0,			0,
			 		0, 		  1.0,			0,			0,
					0, 			0,		  1.0,			0,
					y, 			x,			z, 			1.0);
}

mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

mat4 rotationY( in float angle ) {
	return mat4(	cos(angle),		0,		sin(angle),	0,
			 				0,		1.0,			 0,	0,
					-sin(angle),	0,		cos(angle),	0,
							0, 		0,				0,	1);
}

mat4 rotationZ( in float angle ) {
	return mat4(	cos(angle),		-sin(angle),	0,	0,
			 		sin(angle),		cos(angle),		0,	0,
							0,				0,		1,	0,
							0,				0,		0,	1);
}

void main()
{
	vec3 crntPos = vec3(model * buildTranslation(px, py, pz) * -rotationX(rx) * rotationY(ry) * rotationZ(rz) * scale * vec4(size * (aPos.x + aNormal.x * outlining), size * (aPos.y + aNormal.y * outlining), size * (aPos.z + aNormal.z * outlining), 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}