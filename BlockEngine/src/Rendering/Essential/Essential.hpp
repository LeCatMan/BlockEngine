#pragma once
#include <stdio.h>
#include "../Color/Color.hpp"


// ========================
// |         VAO          |
// ========================


void CreateVAO(unsigned int *VAO);


void DestroyVAO(unsigned int VAO);


// ========================
// |         VBO          |
// ========================


/**
 * @param Stride you can put it to 0 to auto stride.
 */
void CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, size_t Stride, Color BorderColor, bool RGBA);


void DestroyVBO(unsigned int VBO);


// ========================
// |         EBO          |
// ========================


void CreateEBO(const unsigned int *Indices, size_t Size, unsigned int *EBO);


void DestroyEBO(unsigned int EBO);


// ========================
// |    Shader Program    |
// ========================


void ShaderProgram(unsigned int *Shader, unsigned int VertexShader, unsigned int FragmentShader);

void DestroyShader(unsigned int Shader);

