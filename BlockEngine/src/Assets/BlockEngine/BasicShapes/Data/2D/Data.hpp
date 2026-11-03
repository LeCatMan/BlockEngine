#pragma once


/** 
 * Basic shapes provided by Block Engine.
 * 
 * These shapes are ready to use and cover common
 * use cases. You do not need to create your own
 * vertex data unless you need a shape that is not
 * provided here.
 * 
 * The data is kept readable so you can understand
 * and modify the shapes if needed.
**/


// =========================
// |       Triangle        |
// =========================


extern const float TriangleVertices[9];
extern const float TriangleVerticesColor[21];
extern const float TriangleVerticesColorUV[27];
extern const unsigned int TriangleIndices[3];


// =========================
// |        Square         |
// =========================


extern const float SquareVertices[12];
extern const float SquareVerticesUV[20];
extern const float SquareVerticesColor[28];
extern const float SquareVerticesColorUV[36];
extern const unsigned int SquareIndices[6];


// =========================
// |       Transform       |
// =========================


extern const float BasicTransform[16];

