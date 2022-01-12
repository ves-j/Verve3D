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

void main()
{
	vec3 crntPos = vec3(model * translation * -rotation * scale * vec4(size * (aPos.x + py + aNormal.x * outlining), size * (aPos.y + px + aNormal.y * outlining), size * (aPos.z + pz + aNormal.z * outlining), 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}