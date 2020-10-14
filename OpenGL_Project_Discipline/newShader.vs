#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 newShader;

void main()
{
    gl_Position = newShader * vec4(aPos, 1.0);
}