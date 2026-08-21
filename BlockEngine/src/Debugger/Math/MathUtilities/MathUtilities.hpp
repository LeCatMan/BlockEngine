#ifndef MATHUTILITIES_HPP
#define MATHUTILITIES_HPP
#include <stdarg.h>


// ########################
// #        FLOAT         #
// ########################

typedef struct
{
    float x;
    float y;
    float width;
    float height;
} FloatRectangle;

typedef struct
{
    float x;
    float y;
} FloatVector2;

typedef struct
{
    float x;
    float y;
    float z;
} FloatVector3;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} FloatVector4;


// ########################
// #         INT          #
// ########################

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} IntRectangle;

typedef struct
{
    int x;
    int y;
} IntVector2;

typedef struct
{
    int x;
    int y;
    int z;
} IntVector3;

typedef struct
{
    int x;
    int y;
    int z;
    int w;
} IntVector4;


// ########################
// #      2D HELPERS      #
// ########################

// Get the center of the screen.
static inline IntVector2 CenterOfScreen(IntVector2 screen)
{
    return (IntVector2){
        screen.x / 2,
        screen.y / 2
    };
}

// Get half of an IntVector2.
static inline IntVector2 HalfIntVector2(IntVector2 vector)
{
    return (IntVector2){
        vector.x / 2,
        vector.y / 2
    };
}

// Get half of a FloatVector2.
static inline FloatVector2 HalfFloatVector2(FloatVector2 vector)
{
    return (FloatVector2){
        vector.x / 2.0f,
        vector.y / 2.0f
    };
}


// ########################
// #      3D HELPERS      #
// ########################

// Get half of an IntVector3.
static inline IntVector3 HalfIntVector3(IntVector3 vector)
{
    return (IntVector3){
        vector.x / 2,
        vector.y / 2,
        vector.z / 2
    };
}

// Get half of a FloatVector3.
static inline FloatVector3 HalfFloatVector3(FloatVector3 vector)
{
    return (FloatVector3){
        vector.x / 2.0f,
        vector.y / 2.0f,
        vector.z / 2.0f
    };
}


// ########################
// #      4D HELPERS      #
// ########################

// Get half of an IntVector4.
static inline IntVector4 HalfIntVector4(IntVector4 vector)
{
    return (IntVector4){
        vector.x / 2,
        vector.y / 2,
        vector.z / 2,
        vector.w / 2
    };
}

// Get half of a FloatVector4.
static inline FloatVector4 HalfFloatVector4(FloatVector4 vector)
{
    return (FloatVector4){
        vector.x / 2.0f,
        vector.y / 2.0f,
        vector.z / 2.0f,
        vector.w / 2.0f
    };
}


// ########################
// #    NUMBER HELPERS    #
// ########################

// Get half of an integer.
static inline int HalfInt(int number)
{
    return number / 2;
}

// Get half of a float.
static inline float HalfFloat(float number)
{
    return number / 2.0f;
}


// ########################
// #    OTHER HELPERS     #
// ########################

static inline double Sum(int count, ...)
{
    va_list args;
    va_start(args, count);

    double total = 0.0;

    for (int i = 0; i < count; ++i)
    {
        total += va_arg(args, double);
    }

    va_end(args);

    return total;
}


#endif
