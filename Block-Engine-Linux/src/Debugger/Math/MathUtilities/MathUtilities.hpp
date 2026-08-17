#ifndef MATHUTILITIES_HPP
#define MATHUTILITIES_HPP

#include <stdio.h>
#include <stdarg.h>

// ------------------------
// Types
// ------------------------

// ------------------------
// Float
// ------------------------

// float X , float Y , float Width , float Height.
typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rectanglef;

// float X , float Y.
typedef struct {
    float x;
    float y;
} Vector2f;

// float X , float Y , float Z.
typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

// float X , float Y , float Z.
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector4f;

// ------------------------
// Int
// ------------------------

// int X , int Y , int Width , int Height.
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

// int X , int Y.
typedef struct {
    int x;
    int y;
} Vector2;

// int X , int Y , int Z.
typedef struct {
    int x;
    int y;
    int z;
} Vector3;

// int X , int Y , int Z , int W.
typedef struct {
    int x;
    int y;
    int z;
    int w;
} Vector4;

// ------------------------
// Inline helper functions
// ------------------------

// Get the center of the screen.
static inline Vector2 CenterOfScreen(Vector2 screen) {
    return (Vector2){screen.x / 2, screen.y / 2};
}

// Get the half of the number.
static inline int Half(int number) {
    return number / 2;
}

// Get the half of the Vector2.
static inline Vector2 HalfV2(Vector2 v) {
    return (Vector2){v.x / 2, v.y / 2};
}

// Get the half of the Vector3.
static inline Vector3 HalfV3(Vector3 v) {
    return (Vector3){v.x / 2, v.y / 2, v.z / 2};
}

// Get the half of the Vector4.
static inline Vector4 HalfV4(Vector4 v) {
    return (Vector4){v.x / 2, v.y / 2, v.z / 2, v.w / 2};
}

// ------------------------
// Float
// ------------------------

// Get the half of the number.
static inline float Halff(float number) {
    return number / 2;
}

static inline double sum(int count, ...) {
    va_list args;
    va_start(args, count);
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, double);
    }
    va_end(args);
    return total;
}

#endif
