#version 330 core

out vec4 FragColor;

in vec2 TextureCoordinates;
in vec3 VertexColor;

uniform sampler2D Texture;
uniform vec4 color;

void main()
{
    FragColor = texture(Texture, TextureCoordinates) * vec4(VertexColor, 1.0f) * color;
}
