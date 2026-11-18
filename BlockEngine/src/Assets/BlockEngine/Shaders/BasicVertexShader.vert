#version 330 core

layout (location = 0) in vec3 LocalPosition;

uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(LocalPosition, 1.0);
}