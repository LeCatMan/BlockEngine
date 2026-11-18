#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
uniform vec4 color;

void main()
{
    FragColor = VertexColor * color;
}
