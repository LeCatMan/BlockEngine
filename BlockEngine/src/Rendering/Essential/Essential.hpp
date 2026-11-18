#pragma once

#include "../Color/Color.hpp"
#include "../Texture/Texture.hpp"


// ========================
// |         VAO          |
// ========================


BlockResult CreateVAO(unsigned int *VAO);


BlockResult DestroyVAO(unsigned int VAO);


// ========================
// |         VBO          |
// ========================


BlockResult CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, bool RGBA, BlockTextureFlags TextureBorder = BLOCK_TEXTURE_REPEAT, Color TextureBorderColor = Color(255, 0, 255, 255));


BlockResult DestroyVBO(unsigned int VBO);


// ========================
// |         EBO          |
// ========================


BlockResult CreateEBO(const unsigned int *Indices, size_t Size, unsigned int *EBO);


BlockResult DestroyEBO(unsigned int EBO);


// ========================
// |    Shader Program    |
// ========================


BlockResult ShaderProgram(unsigned int *Shader, unsigned int VertexShader, unsigned int FragmentShader);

BlockResult DestroyShader(unsigned int Shader);

