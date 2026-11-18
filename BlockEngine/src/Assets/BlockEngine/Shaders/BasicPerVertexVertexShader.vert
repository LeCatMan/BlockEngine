#version 330 core

layout (location = 0) in vec3 LocalPosition;
layout (location = 1) in vec4 LocalColor;

out vec4 VertexColor;

uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(LocalPosition, 1.0);
    VertexColor = LocalColor;
}