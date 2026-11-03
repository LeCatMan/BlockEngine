#version 330 core
layout (location = 0) in vec3 LocalPosition;
layout (location = 1) in vec3 LocalColor;
layout (location = 2) in vec2 LocalTextureCoordinates;

out vec3 VertexColor;
out vec2 TextureCoordinates;

uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(LocalPosition, 1.0f);
    VertexColor = LocalColor;
    TextureCoordinates = LocalTextureCoordinates;
}