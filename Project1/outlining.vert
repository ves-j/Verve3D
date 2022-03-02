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
	vec3 crntPos = vec3(model * translation * -rotationX(rx) * rotationY(ry) * rotationZ(rz) * scale * vec4(size * (aPos.x + py + aNormal.x * outlining), size * (aPos.y + px + aNormal.y * outlining), size * (aPos.z + pz + aNormal.z * outlining), 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}