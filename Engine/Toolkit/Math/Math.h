/*
 * Copyright (c) scott.cgi All Rights Reserved.
 *
 * This source code belongs to project Mojoc, which is a pure C Game Engine hosted on GitHub.
 * The Mojoc Game Engine is licensed under the MIT License, and will continue to be iterated with coding passion.
 *
 * License  : https://github.com/scottcgi/Mojoc/blob/master/LICENSE
 * GitHub   : https://github.com/scottcgi/Mojoc
 * CodeStyle: https://github.com/scottcgi/Mojoc/wiki/Code-Style
 *
 * Since    : 2013-1-24
 * Update   : 2019-1-18
 * Author   : scott.cgi
 */


#ifndef MATH_H
#define MATH_H


#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>

#include "Engine/Toolkit/Utils/Array.h"
#include "Engine/Toolkit/Platform/Log.h"


struct AMath
{
    /**
     * Test polygon contains 2D point, return true inside or false outside.
     * one point contains pair of x, y.
     */
    bool  (*TestPolygonPoint)(Array(float)* pointArr, float x, float y);

    /**
     * Rotate 2D point by angle.
     * one point contains pair of x, y.
     */
    void  (*RotatePoints2)   (Array(float)* pointArr, float angle, Array(float)* outRotatedPointArr);
};


extern struct AMath AMath[1];


//----------------------------------------------------------------------------------------------------------------------


#define GOLDEN_RATIO      0.618033988749894f


/**
 * The value of (PI / 180.0f).
 */
#define DEGREE_TO_RADIAN  0.017453292519943f


/**
 * The value of (PI / 360.0f).
 */
#define DEGREE_TO_RADIAN2 0.008726646259972f


/**
 * The value of (180.0f / PI).
 */
#define RADIAN_TO_DEGREE  57.29577951308232f


#define MATH_PI           3.141592653589793f


/**
 * The value of (2 * PI).
 */
#define MATH_2PI          6.283185307179586f


/**
 * The value of (PI / 2).
 */
#define MATH_PI2          1.570796326794897f


//----------------------------------------------------------------------------------------------------------------------


/**
 * Random float in range [0.0, 1.0].
 */
static inline float AMath_Random()
{
    return (float) (rand() / (double) RAND_MAX);
}


/**
 * Random integer in range [from, to].
 */
static inline int AMath_RandomInt(int from, int to)
{
    return (from) + rand() % ((to) - (from) + 1);
}


/**
 * Random float in range [from, to].
 */
static inline float AMath_RandomFloat(float from, float to)
{
    return from + AMath_Random() * ((to) - (from));
}


/**
 * Random seed by system time.
 */
static inline void AMath_RandomSeedByTime()
{
    srand((unsigned) time(NULL));
}


/**
 * Convert degree to radian.
 */
static inline float AMath_ToRadian(float degree)
{
    return degree * DEGREE_TO_RADIAN;
}


/**
 * Convert radian to degree.
 */
static inline float AMath_ToDegree(float radian)
{
    return radian * RADIAN_TO_DEGREE;
}


/**
 * Cos by degree.
 */
static inline float AMath_Cos(float degree)
{
    return cosf(AMath_ToRadian(degree));
}


/**
 * Sin by degree.
 */
static inline float AMath_Sin(float degree)
{
    return sinf(AMath_ToRadian(degree));
}


/**
 * Degree by atan2.
 */
static inline float AMath_Atan2(float x, float y)
{
    return AMath_ToDegree(atan2f(y, x));
}


/**
 * Degree by acosf.
 */
static inline float AMath_Acos(float ratio)
{
    return AMath_ToDegree(acosf(ratio));
}


/**
 * Degree by asinf.
 */
static inline float AMath_Asin(float ratio)
{
    return AMath_ToDegree(asinf(ratio));
}


/**
 * Compare float value equals.
 */
static inline bool AMath_IsFloatEqual(float x, float y)
{
    return fabsf((x) - (y)) <= FLT_EPSILON;
}


/**
 * Fast square inverse root float.
 */
static inline float AMath_InvSqrtf(float x)
{
    union { float f; int i; } u = {x};

    u.i = 0x5f3759df - (u.i >> 1);

    return u.f * (1.5f - 0.5f * x * u.f * u.f);
}


/**
 * Fast square root float.
 * equals AMath_InvSqrtf(x) * x.
 */
static inline float AMath_Sqrtf(float x)
{
    union { float f; int i; } u = {x};

    u.i = 0x5f3759df - (u.i >> 1);
    x  *= u.f; // reduce one multiplication and increase one assignment

    return x * (1.5f - 0.5f * x * u.f);
}


/**
 * Min in x and y, macro can use generic parameter.
 */
#define AMath_Min(x, y) \
    (((x) < (y)) ? (x) : (y))


/**
 * Max in a and b, macro can use generic parameter.
 */
#define AMath_Max(x, y) \
    (((x) > (y)) ? (x) : (y))


/**
 * Clamp x in min and max, macro can use generic parameter.
 */
#define AMath_Clamp(x, min, max) \
    (AMath_Min((max), AMath_Max((x), (min))))


#endif