// Basic shapes provided by Block Engine.
//
// These shapes are ready to use and cover common
// use cases. You do not need to create your own
// vertex data unless you need a shape that is not
// provided here.
//
// The data is kept readable so you can understand
// and modify the shapes if needed.


// =========================
// |       Triangle        |
// =========================


// Position only
const float TriangleVertices[9] = {
    //  x      y      z
       0.5f, -0.5f, 0.0f,   // Bottom right
      -0.5f, -0.5f, 0.0f,   // Bottom left
       0.0f,  0.5f, 0.0f    // Top
};


// Position + Color
const float TriangleVerticesColor[21] = {
    // Position              // Color
    //  x      y      z       r      g      b      a
       0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   // Bottom right
      -0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   // Bottom left
       0.0f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f    // Top
};


// Position + Color + UV
const float TriangleVerticesColorUV[27] = {
    // Position              // Color              // UV
    //  x      y      z       r      g      b      a       u      v
       0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,   // Bottom right
      -0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   1.0f, 0.0f,   // Bottom left
       0.0f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f,   0.5f, 1.0f    // Top
};


const unsigned int TriangleIndices[3] = {
    0, 1, 2
};


// =========================
// |        Square         |
// =========================


// Position + UV
const float SquareVerticesUV[20] = {
    // Position              // UV
    //  x      y      z       u      v
      -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,    1.0f, 0.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,   // Top left
       0.5f,  0.5f, 0.0f,    1.0f, 1.0f    // Top right
};


// Position + Color
const float SquareVerticesColor[28] = {
    // Position              // Color
    //  x      y      z       r      g      b      a
      -0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f,   // Top left
       0.5f,  0.5f, 0.0f,    1.0f,  1.0f,  0.0f, 1.0f    // Top right
};

// Position + Color + UV
const float SquareVerticesColorUV[36] = {
    // Position              // Color              // UV
    //  x      y      z       r      g      b      a       u      v
      -0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   1.0f, 0.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f,   0.0f, 1.0f,   // Top left
       0.5f,  0.5f, 0.0f,    1.0f,  1.0f,  0.0f, 1.0f,   1.0f, 1.0f    // Top right
};


// Position only
const float SquareVertices[12] = {
    //  x      y      z
      -0.5f, -0.5f, 0.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,   // Top left
       0.5f,  0.5f, 0.0f    // Top right
};


const unsigned int SquareIndices[6] = {
    0, 1, 2,
    1, 3, 2
};
