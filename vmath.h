#pragma once
/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_AOS_C_V_SCALAR_H
#define _VECTORMATH_AOS_C_V_SCALAR_H

#include <math.h>

#ifdef _VECTORMATH_DEBUG
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _VECTORMATH_AOS_C_TYPES_H
#define _VECTORMATH_AOS_C_TYPES_H

/* A 3-D vector in array-of-structures format
 */
typedef struct _VmathVector3
{
    float x;
    float y;
    float z;
}
VmathVector3;

/* A 4-D vector in array-of-structures format
 */
typedef struct _VmathVector4
{
    float x;
    float y;
    float z;
    float w;
}
VmathVector4;

/* A 3-D point in array-of-structures format
 */
typedef struct _VmathPoint3
{
    float x;
    float y;
    float z;
}
VmathPoint3;

/* A quaternion in array-of-structures format
 */
typedef struct _VmathQuat
{
    float x;
    float y;
    float z;
    float w;
}
VmathQuat;

/* A 3x3 matrix in array-of-structures format
 */
typedef struct _VmathMatrix3
{
    VmathVector3 col0;
    VmathVector3 col1;
    VmathVector3 col2;
} VmathMatrix3;

/* A 4x4 matrix in array-of-structures format
 */
typedef struct _VmathMatrix4
{
    VmathVector4 col0;
    VmathVector4 col1;
    VmathVector4 col2;
    VmathVector4 col3;
} VmathMatrix4;

/* A 3x4 transformation matrix in array-of-structures format
 */
typedef struct _VmathTransform3
{
    VmathVector3 col0;
    VmathVector3 col1;
    VmathVector3 col2;
    VmathVector3 col3;
} VmathTransform3;

#endif

/*
 * Construct a 3-D vector from x, y, and z elements
 */
static inline VmathVector3 vmathV3MakeFromElems_V( float x, float y, float z );

/*
 * Copy elements from a 3-D point into a 3-D vector
 */
static inline VmathVector3 vmathV3MakeFromP3_V( VmathPoint3 pnt );

/*
 * Set all elements of a 3-D vector to the same scalar value
 */
static inline VmathVector3 vmathV3MakeFromScalar_V( float scalar );

/*
 * Set the x element of a 3-D vector
 */
static inline void vmathV3SetX_V( VmathVector3 *result, float x );

/*
 * Set the y element of a 3-D vector
 */
static inline void vmathV3SetY_V( VmathVector3 *result, float y );

/*
 * Set the z element of a 3-D vector
 */
static inline void vmathV3SetZ_V( VmathVector3 *result, float z );

/*
 * Get the x element of a 3-D vector
 */
static inline float vmathV3GetX_V( VmathVector3 vec );

/*
 * Get the y element of a 3-D vector
 */
static inline float vmathV3GetY_V( VmathVector3 vec );

/*
 * Get the z element of a 3-D vector
 */
static inline float vmathV3GetZ_V( VmathVector3 vec );

/*
 * Set an x, y, or z element of a 3-D vector by index
 */
static inline void vmathV3SetElem_V( VmathVector3 *result, int idx, float value );

/*
 * Get an x, y, or z element of a 3-D vector by index
 */
static inline float vmathV3GetElem_V( VmathVector3 vec, int idx );

/*
 * Add two 3-D vectors
 */
static inline VmathVector3 vmathV3Add_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Subtract a 3-D vector from another 3-D vector
 */
static inline VmathVector3 vmathV3Sub_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Add a 3-D vector to a 3-D point
 */
static inline VmathPoint3 vmathV3AddP3_V( VmathVector3 vec, VmathPoint3 pnt );

/*
 * Multiply a 3-D vector by a scalar
 */
static inline VmathVector3 vmathV3ScalarMul_V( VmathVector3 vec, float scalar );

/*
 * Divide a 3-D vector by a scalar
 */
static inline VmathVector3 vmathV3ScalarDiv_V( VmathVector3 vec, float scalar );

/*
 * Negate all elements of a 3-D vector
 */
static inline VmathVector3 vmathV3Neg_V( VmathVector3 vec );

/*
 * Construct x axis
 */
static inline VmathVector3 vmathV3MakeXAxis_V( );

/*
 * Construct y axis
 */
static inline VmathVector3 vmathV3MakeYAxis_V( );

/*
 * Construct z axis
 */
static inline VmathVector3 vmathV3MakeZAxis_V( );

/*
 * Multiply two 3-D vectors per element
 */
static inline VmathVector3 vmathV3MulPerElem_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Divide two 3-D vectors per element
 * NOTE: 
 * Floating-point behavior matches standard library function divf4.
 */
static inline VmathVector3 vmathV3DivPerElem_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Compute the reciprocal of a 3-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function recipf4.
 */
static inline VmathVector3 vmathV3RecipPerElem_V( VmathVector3 vec );

/*
 * Compute the square root of a 3-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function sqrtf4.
 */
static inline VmathVector3 vmathV3SqrtPerElem_V( VmathVector3 vec );

/*
 * Compute the reciprocal square root of a 3-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function rsqrtf4.
 */
static inline VmathVector3 vmathV3RsqrtPerElem_V( VmathVector3 vec );

/*
 * Compute the absolute value of a 3-D vector per element
 */
static inline VmathVector3 vmathV3AbsPerElem_V( VmathVector3 vec );

/*
 * Copy sign from one 3-D vector to another, per element
 */
static inline VmathVector3 vmathV3CopySignPerElem_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Maximum of two 3-D vectors per element
 */
static inline VmathVector3 vmathV3MaxPerElem_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Minimum of two 3-D vectors per element
 */
static inline VmathVector3 vmathV3MinPerElem_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Maximum element of a 3-D vector
 */
static inline float vmathV3MaxElem_V( VmathVector3 vec );

/*
 * Minimum element of a 3-D vector
 */
static inline float vmathV3MinElem_V( VmathVector3 vec );

/*
 * Compute the sum of all elements of a 3-D vector
 */
static inline float vmathV3Sum_V( VmathVector3 vec );

/*
 * Compute the dot product of two 3-D vectors
 */
static inline float vmathV3Dot_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Compute the square of the length of a 3-D vector
 */
static inline float vmathV3LengthSqr_V( VmathVector3 vec );

/*
 * Compute the length of a 3-D vector
 */
static inline float vmathV3Length_V( VmathVector3 vec );

/*
 * Normalize a 3-D vector
 * NOTE: 
 * The result is unpredictable when all elements of vec are at or near zero.
 */
static inline VmathVector3 vmathV3Normalize_V( VmathVector3 vec );

/*
 * Compute cross product of two 3-D vectors
 */
static inline VmathVector3 vmathV3Cross_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Outer product of two 3-D vectors
 */
static inline VmathMatrix3 vmathV3Outer_V( VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Pre-multiply a row vector by a 3x3 matrix
 */
static inline VmathVector3 vmathV3RowMul_V( VmathVector3 vec, VmathMatrix3 mat );

/*
 * Cross-product matrix of a 3-D vector
 */
static inline VmathMatrix3 vmathV3CrossMatrix_V( VmathVector3 vec );

/*
 * Create cross-product matrix and multiply
 * NOTE: 
 * Faster than separately creating a cross-product matrix and multiplying.
 */
static inline VmathMatrix3 vmathV3CrossMatrixMul_V( VmathVector3 vec, VmathMatrix3 mat );

/*
 * Linear interpolation between two 3-D vectors
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline VmathVector3 vmathV3Lerp_V( float t, VmathVector3 vec0, VmathVector3 vec1 );

/*
 * Spherical linear interpolation between two 3-D vectors
 * NOTE: 
 * The result is unpredictable if the vectors point in opposite directions.
 * Does not clamp t between 0 and 1.
 */
static inline VmathVector3 vmathV3Slerp_V( float t, VmathVector3 unitVec0, VmathVector3 unitVec1 );

/*
 * Conditionally select between two 3-D vectors
 */
static inline VmathVector3 vmathV3Select_V( VmathVector3 vec0, VmathVector3 vec1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3-D vector
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV3Print_V( VmathVector3 vec );

/*
 * Print a 3-D vector and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV3Prints_V( VmathVector3 vec, const char *name );

#endif

/*
 * Construct a 4-D vector from x, y, z, and w elements
 */
static inline VmathVector4 vmathV4MakeFromElems_V( float x, float y, float z, float w );

/*
 * Construct a 4-D vector from a 3-D vector and a scalar
 */
static inline VmathVector4 vmathV4MakeFromV3Scalar_V( VmathVector3 xyz, float w );

/*
 * Copy x, y, and z from a 3-D vector into a 4-D vector, and set w to 0
 */
static inline VmathVector4 vmathV4MakeFromV3_V( VmathVector3 vec );

/*
 * Copy x, y, and z from a 3-D point into a 4-D vector, and set w to 1
 */
static inline VmathVector4 vmathV4MakeFromP3_V( VmathPoint3 pnt );

/*
 * Copy elements from a quaternion into a 4-D vector
 */
static inline VmathVector4 vmathV4MakeFromQ_V( VmathQuat quat );

/*
 * Set all elements of a 4-D vector to the same scalar value
 */
static inline VmathVector4 vmathV4MakeFromScalar_V( float scalar );

/*
 * Set the x, y, and z elements of a 4-D vector
 * NOTE: 
 * This function does not change the w element.
 */
static inline void vmathV4SetXYZ_V( VmathVector4 *result, VmathVector3 vec );

/*
 * Get the x, y, and z elements of a 4-D vector
 */
static inline VmathVector3 vmathV4GetXYZ_V( VmathVector4 vec );

/*
 * Set the x element of a 4-D vector
 */
static inline void vmathV4SetX_V( VmathVector4 *result, float x );

/*
 * Set the y element of a 4-D vector
 */
static inline void vmathV4SetY_V( VmathVector4 *result, float y );

/*
 * Set the z element of a 4-D vector
 */
static inline void vmathV4SetZ_V( VmathVector4 *result, float z );

/*
 * Set the w element of a 4-D vector
 */
static inline void vmathV4SetW_V( VmathVector4 *result, float w );

/*
 * Get the x element of a 4-D vector
 */
static inline float vmathV4GetX_V( VmathVector4 vec );

/*
 * Get the y element of a 4-D vector
 */
static inline float vmathV4GetY_V( VmathVector4 vec );

/*
 * Get the z element of a 4-D vector
 */
static inline float vmathV4GetZ_V( VmathVector4 vec );

/*
 * Get the w element of a 4-D vector
 */
static inline float vmathV4GetW_V( VmathVector4 vec );

/*
 * Set an x, y, z, or w element of a 4-D vector by index
 */
static inline void vmathV4SetElem_V( VmathVector4 *result, int idx, float value );

/*
 * Get an x, y, z, or w element of a 4-D vector by index
 */
static inline float vmathV4GetElem_V( VmathVector4 vec, int idx );

/*
 * Add two 4-D vectors
 */
static inline VmathVector4 vmathV4Add_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Subtract a 4-D vector from another 4-D vector
 */
static inline VmathVector4 vmathV4Sub_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Multiply a 4-D vector by a scalar
 */
static inline VmathVector4 vmathV4ScalarMul_V( VmathVector4 vec, float scalar );

/*
 * Divide a 4-D vector by a scalar
 */
static inline VmathVector4 vmathV4ScalarDiv_V( VmathVector4 vec, float scalar );

/*
 * Negate all elements of a 4-D vector
 */
static inline VmathVector4 vmathV4Neg_V( VmathVector4 vec );

/*
 * Construct x axis
 */
static inline VmathVector4 vmathV4MakeXAxis_V( );

/*
 * Construct y axis
 */
static inline VmathVector4 vmathV4MakeYAxis_V( );

/*
 * Construct z axis
 */
static inline VmathVector4 vmathV4MakeZAxis_V( );

/*
 * Construct w axis
 */
static inline VmathVector4 vmathV4MakeWAxis_V( );

/*
 * Multiply two 4-D vectors per element
 */
static inline VmathVector4 vmathV4MulPerElem_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Divide two 4-D vectors per element
 * NOTE: 
 * Floating-point behavior matches standard library function divf4.
 */
static inline VmathVector4 vmathV4DivPerElem_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Compute the reciprocal of a 4-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function recipf4.
 */
static inline VmathVector4 vmathV4RecipPerElem_V( VmathVector4 vec );

/*
 * Compute the square root of a 4-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function sqrtf4.
 */
static inline VmathVector4 vmathV4SqrtPerElem_V( VmathVector4 vec );

/*
 * Compute the reciprocal square root of a 4-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function rsqrtf4.
 */
static inline VmathVector4 vmathV4RsqrtPerElem_V( VmathVector4 vec );

/*
 * Compute the absolute value of a 4-D vector per element
 */
static inline VmathVector4 vmathV4AbsPerElem_V( VmathVector4 vec );

/*
 * Copy sign from one 4-D vector to another, per element
 */
static inline VmathVector4 vmathV4CopySignPerElem_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Maximum of two 4-D vectors per element
 */
static inline VmathVector4 vmathV4MaxPerElem_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Minimum of two 4-D vectors per element
 */
static inline VmathVector4 vmathV4MinPerElem_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Maximum element of a 4-D vector
 */
static inline float vmathV4MaxElem_V( VmathVector4 vec );

/*
 * Minimum element of a 4-D vector
 */
static inline float vmathV4MinElem_V( VmathVector4 vec );

/*
 * Compute the sum of all elements of a 4-D vector
 */
static inline float vmathV4Sum_V( VmathVector4 vec );

/*
 * Compute the dot product of two 4-D vectors
 */
static inline float vmathV4Dot_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Compute the square of the length of a 4-D vector
 */
static inline float vmathV4LengthSqr_V( VmathVector4 vec );

/*
 * Compute the length of a 4-D vector
 */
static inline float vmathV4Length_V( VmathVector4 vec );

/*
 * Normalize a 4-D vector
 * NOTE: 
 * The result is unpredictable when all elements of vec are at or near zero.
 */
static inline VmathVector4 vmathV4Normalize_V( VmathVector4 vec );

/*
 * Outer product of two 4-D vectors
 */
static inline VmathMatrix4 vmathV4Outer_V( VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Linear interpolation between two 4-D vectors
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline VmathVector4 vmathV4Lerp_V( float t, VmathVector4 vec0, VmathVector4 vec1 );

/*
 * Spherical linear interpolation between two 4-D vectors
 * NOTE: 
 * The result is unpredictable if the vectors point in opposite directions.
 * Does not clamp t between 0 and 1.
 */
static inline VmathVector4 vmathV4Slerp_V( float t, VmathVector4 unitVec0, VmathVector4 unitVec1 );

/*
 * Conditionally select between two 4-D vectors
 */
static inline VmathVector4 vmathV4Select_V( VmathVector4 vec0, VmathVector4 vec1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 4-D vector
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV4Print_V( VmathVector4 vec );

/*
 * Print a 4-D vector and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV4Prints_V( VmathVector4 vec, const char *name );

#endif

/*
 * Construct a 3-D point from x, y, and z elements
 */
static inline VmathPoint3 vmathP3MakeFromElems_V( float x, float y, float z );

/*
 * Copy elements from a 3-D vector into a 3-D point
 */
static inline VmathPoint3 vmathP3MakeFromV3_V( VmathVector3 vec );

/*
 * Set all elements of a 3-D point to the same scalar value
 */
static inline VmathPoint3 vmathP3MakeFromScalar_V( float scalar );

/*
 * Set the x element of a 3-D point
 */
static inline void vmathP3SetX_V( VmathPoint3 *result, float x );

/*
 * Set the y element of a 3-D point
 */
static inline void vmathP3SetY_V( VmathPoint3 *result, float y );

/*
 * Set the z element of a 3-D point
 */
static inline void vmathP3SetZ_V( VmathPoint3 *result, float z );

/*
 * Get the x element of a 3-D point
 */
static inline float vmathP3GetX_V( VmathPoint3 pnt );

/*
 * Get the y element of a 3-D point
 */
static inline float vmathP3GetY_V( VmathPoint3 pnt );

/*
 * Get the z element of a 3-D point
 */
static inline float vmathP3GetZ_V( VmathPoint3 pnt );

/*
 * Set an x, y, or z element of a 3-D point by index
 */
static inline void vmathP3SetElem_V( VmathPoint3 *result, int idx, float value );

/*
 * Get an x, y, or z element of a 3-D point by index
 */
static inline float vmathP3GetElem_V( VmathPoint3 pnt, int idx );

/*
 * Subtract a 3-D point from another 3-D point
 */
static inline VmathVector3 vmathP3Sub_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Add a 3-D point to a 3-D vector
 */
static inline VmathPoint3 vmathP3AddV3_V( VmathPoint3 pnt, VmathVector3 vec );

/*
 * Subtract a 3-D vector from a 3-D point
 */
static inline VmathPoint3 vmathP3SubV3_V( VmathPoint3 pnt, VmathVector3 vec );

/*
 * Multiply two 3-D points per element
 */
static inline VmathPoint3 vmathP3MulPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Divide two 3-D points per element
 * NOTE: 
 * Floating-point behavior matches standard library function divf4.
 */
static inline VmathPoint3 vmathP3DivPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Compute the reciprocal of a 3-D point per element
 * NOTE: 
 * Floating-point behavior matches standard library function recipf4.
 */
static inline VmathPoint3 vmathP3RecipPerElem_V( VmathPoint3 pnt );

/*
 * Compute the square root of a 3-D point per element
 * NOTE: 
 * Floating-point behavior matches standard library function sqrtf4.
 */
static inline VmathPoint3 vmathP3SqrtPerElem_V( VmathPoint3 pnt );

/*
 * Compute the reciprocal square root of a 3-D point per element
 * NOTE: 
 * Floating-point behavior matches standard library function rsqrtf4.
 */
static inline VmathPoint3 vmathP3RsqrtPerElem_V( VmathPoint3 pnt );

/*
 * Compute the absolute value of a 3-D point per element
 */
static inline VmathPoint3 vmathP3AbsPerElem_V( VmathPoint3 pnt );

/*
 * Copy sign from one 3-D point to another, per element
 */
static inline VmathPoint3 vmathP3CopySignPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Maximum of two 3-D points per element
 */
static inline VmathPoint3 vmathP3MaxPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Minimum of two 3-D points per element
 */
static inline VmathPoint3 vmathP3MinPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Maximum element of a 3-D point
 */
static inline float vmathP3MaxElem_V( VmathPoint3 pnt );

/*
 * Minimum element of a 3-D point
 */
static inline float vmathP3MinElem_V( VmathPoint3 pnt );

/*
 * Compute the sum of all elements of a 3-D point
 */
static inline float vmathP3Sum_V( VmathPoint3 pnt );

/*
 * Apply uniform scale to a 3-D point
 */
static inline VmathPoint3 vmathP3Scale_V( VmathPoint3 pnt, float scaleVal );

/*
 * Apply non-uniform scale to a 3-D point
 */
static inline VmathPoint3 vmathP3NonUniformScale_V( VmathPoint3 pnt, VmathVector3 scaleVec );

/*
 * Scalar projection of a 3-D point on a unit-length 3-D vector
 */
static inline float vmathP3Projection_V( VmathPoint3 pnt, VmathVector3 unitVec );

/*
 * Compute the square of the distance of a 3-D point from the coordinate-system origin
 */
static inline float vmathP3DistSqrFromOrigin_V( VmathPoint3 pnt );

/*
 * Compute the distance of a 3-D point from the coordinate-system origin
 */
static inline float vmathP3DistFromOrigin_V( VmathPoint3 pnt );

/*
 * Compute the square of the distance between two 3-D points
 */
static inline float vmathP3DistSqr_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Compute the distance between two 3-D points
 */
static inline float vmathP3Dist_V( VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Linear interpolation between two 3-D points
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline VmathPoint3 vmathP3Lerp_V( float t, VmathPoint3 pnt0, VmathPoint3 pnt1 );

/*
 * Conditionally select between two 3-D points
 */
static inline VmathPoint3 vmathP3Select_V( VmathPoint3 pnt0, VmathPoint3 pnt1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3-D point
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathP3Print_V( VmathPoint3 pnt );

/*
 * Print a 3-D point and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathP3Prints_V( VmathPoint3 pnt, const char *name );

#endif

#ifdef _VECTORMATH_DEBUG

/*
 * Print a quaternion
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathQPrint_V( VmathQuat quat );

/*
 * Print a quaternion and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathQPrints_V( VmathQuat quat, const char *name );

#endif

/*
 * Construct a 3x3 matrix containing the specified columns
 */
static inline VmathMatrix3 vmathM3MakeFromCols_V( VmathVector3 col0, VmathVector3 col1, VmathVector3 col2 );

/*
 * Construct a 3x3 rotation matrix from a unit-length quaternion
 */
static inline VmathMatrix3 vmathM3MakeFromQ_V( VmathQuat unitQuat );

/*
 * Set all elements of a 3x3 matrix to the same scalar value
 */
static inline VmathMatrix3 vmathM3MakeFromScalar_V( float scalar );

/*
 * Set column 0 of a 3x3 matrix
 */
static inline void vmathM3SetCol0_V( VmathMatrix3 *result, VmathVector3 col0 );

/*
 * Set column 1 of a 3x3 matrix
 */
static inline void vmathM3SetCol1_V( VmathMatrix3 *result, VmathVector3 col1 );

/*
 * Set column 2 of a 3x3 matrix
 */
static inline void vmathM3SetCol2_V( VmathMatrix3 *result, VmathVector3 col2 );

/*
 * Get column 0 of a 3x3 matrix
 */
static inline VmathVector3 vmathM3GetCol0_V( VmathMatrix3 mat );

/*
 * Get column 1 of a 3x3 matrix
 */
static inline VmathVector3 vmathM3GetCol1_V( VmathMatrix3 mat );

/*
 * Get column 2 of a 3x3 matrix
 */
static inline VmathVector3 vmathM3GetCol2_V( VmathMatrix3 mat );

/*
 * Set the column of a 3x3 matrix referred to by the specified index
 */
static inline void vmathM3SetCol_V( VmathMatrix3 *result, int col, VmathVector3 vec );

/*
 * Set the row of a 3x3 matrix referred to by the specified index
 */
static inline void vmathM3SetRow_V( VmathMatrix3 *result, int row, VmathVector3 vec );

/*
 * Get the column of a 3x3 matrix referred to by the specified index
 */
static inline VmathVector3 vmathM3GetCol_V( VmathMatrix3 mat, int col );

/*
 * Get the row of a 3x3 matrix referred to by the specified index
 */
static inline VmathVector3 vmathM3GetRow_V( VmathMatrix3 mat, int row );

/*
 * Set the element of a 3x3 matrix referred to by column and row indices
 */
static inline void vmathM3SetElem_V( VmathMatrix3 *result, int col, int row, float val );

/*
 * Get the element of a 3x3 matrix referred to by column and row indices
 */
static inline float vmathM3GetElem_V( VmathMatrix3 mat, int col, int row );

/*
 * Add two 3x3 matrices
 */
static inline VmathMatrix3 vmathM3Add_V( VmathMatrix3 mat0, VmathMatrix3 mat1 );

/*
 * Subtract a 3x3 matrix from another 3x3 matrix
 */
static inline VmathMatrix3 vmathM3Sub_V( VmathMatrix3 mat0, VmathMatrix3 mat1 );

/*
 * Negate all elements of a 3x3 matrix
 */
static inline VmathMatrix3 vmathM3Neg_V( VmathMatrix3 mat );

/*
 * Multiply a 3x3 matrix by a scalar
 */
static inline VmathMatrix3 vmathM3ScalarMul_V( VmathMatrix3 mat, float scalar );

/*
 * Multiply a 3x3 matrix by a 3-D vector
 */
static inline VmathVector3 vmathM3MulV3_V( VmathMatrix3 mat, VmathVector3 vec );

/*
 * Multiply two 3x3 matrices
 */
static inline VmathMatrix3 vmathM3Mul_V( VmathMatrix3 mat0, VmathMatrix3 mat1 );

/*
 * Construct an identity 3x3 matrix
 */
static inline VmathMatrix3 vmathM3MakeIdentity_V( );

/*
 * Construct a 3x3 matrix to rotate around the x axis
 */
static inline VmathMatrix3 vmathM3MakeRotationX_V( float radians );

/*
 * Construct a 3x3 matrix to rotate around the y axis
 */
static inline VmathMatrix3 vmathM3MakeRotationY_V( float radians );

/*
 * Construct a 3x3 matrix to rotate around the z axis
 */
static inline VmathMatrix3 vmathM3MakeRotationZ_V( float radians );

/*
 * Construct a 3x3 matrix to rotate around the x, y, and z axes
 */
static inline VmathMatrix3 vmathM3MakeRotationZYX_V( VmathVector3 radiansXYZ );

/*
 * Construct a 3x3 matrix to rotate around a unit-length 3-D vector
 */
static inline VmathMatrix3 vmathM3MakeRotationAxis_V( float radians, VmathVector3 unitVec );

/*
 * Construct a rotation matrix from a unit-length quaternion
 */
static inline VmathMatrix3 vmathM3MakeRotationQ_V( VmathQuat unitQuat );

/*
 * Construct a 3x3 matrix to perform scaling
 */
static inline VmathMatrix3 vmathM3MakeScale_V( VmathVector3 scaleVec );

/*
 * Append (post-multiply) a scale transformation to a 3x3 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline VmathMatrix3 vmathM3AppendScale_V( VmathMatrix3 mat, VmathVector3 scaleVec );

/*
 * Prepend (pre-multiply) a scale transformation to a 3x3 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline VmathMatrix3 vmathM3PrependScale_V( VmathVector3 scaleVec, VmathMatrix3 mat );

/*
 * Multiply two 3x3 matrices per element
 */
static inline VmathMatrix3 vmathM3MulPerElem_V( VmathMatrix3 mat0, VmathMatrix3 mat1 );

/*
 * Compute the absolute value of a 3x3 matrix per element
 */
static inline VmathMatrix3 vmathM3AbsPerElem_V( VmathMatrix3 mat );

/*
 * Transpose of a 3x3 matrix
 */
static inline VmathMatrix3 vmathM3Transpose_V( VmathMatrix3 mat );

/*
 * Compute the inverse of a 3x3 matrix
 * NOTE: 
 * Result is unpredictable when the determinant of mat is equal to or near 0.
 */
static inline VmathMatrix3 vmathM3Inverse_V( VmathMatrix3 mat );

/*
 * Determinant of a 3x3 matrix
 */
static inline float vmathM3Determinant_V( VmathMatrix3 mat );

/*
 * Conditionally select between two 3x3 matrices
 */
static inline VmathMatrix3 vmathM3Select_V( VmathMatrix3 mat0, VmathMatrix3 mat1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3x3 matrix
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM3Print_V( VmathMatrix3 mat );

/*
 * Print a 3x3 matrix and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM3Prints_V( VmathMatrix3 mat, const char *name );

#endif

/*
 * Construct a 4x4 matrix containing the specified columns
 */
static inline VmathMatrix4 vmathM4MakeFromCols_V( VmathVector4 col0, VmathVector4 col1, VmathVector4 col2, VmathVector4 col3 );

/*
 * Construct a 4x4 matrix from a 3x4 transformation matrix
 */
static inline VmathMatrix4 vmathM4MakeFromT3_V( VmathTransform3 mat );

/*
 * Construct a 4x4 matrix from a 3x3 matrix and a 3-D vector
 */
static inline VmathMatrix4 vmathM4MakeFromM3V3_V( VmathMatrix3 mat, VmathVector3 translateVec );

/*
 * Construct a 4x4 matrix from a unit-length quaternion and a 3-D vector
 */
static inline VmathMatrix4 vmathM4MakeFromQV3_V( VmathQuat unitQuat, VmathVector3 translateVec );

/*
 * Set all elements of a 4x4 matrix to the same scalar value
 */
static inline VmathMatrix4 vmathM4MakeFromScalar_V( float scalar );

/*
 * Set the upper-left 3x3 submatrix
 * NOTE: 
 * This function does not change the bottom row elements.
 */
static inline void vmathM4SetUpper3x3_V( VmathMatrix4 *result, VmathMatrix3 mat3 );

/*
 * Get the upper-left 3x3 submatrix of a 4x4 matrix
 */
static inline VmathMatrix3 vmathM4GetUpper3x3_V( VmathMatrix4 mat );

/*
 * Set translation component
 * NOTE: 
 * This function does not change the bottom row elements.
 */
static inline void vmathM4SetTranslation_V( VmathMatrix4 *result, VmathVector3 translateVec );

/*
 * Get the translation component of a 4x4 matrix
 */
static inline VmathVector3 vmathM4GetTranslation_V( VmathMatrix4 mat );

/*
 * Set column 0 of a 4x4 matrix
 */
static inline void vmathM4SetCol0_V( VmathMatrix4 *result, VmathVector4 col0 );

/*
 * Set column 1 of a 4x4 matrix
 */
static inline void vmathM4SetCol1_V( VmathMatrix4 *result, VmathVector4 col1 );

/*
 * Set column 2 of a 4x4 matrix
 */
static inline void vmathM4SetCol2_V( VmathMatrix4 *result, VmathVector4 col2 );

/*
 * Set column 3 of a 4x4 matrix
 */
static inline void vmathM4SetCol3_V( VmathMatrix4 *result, VmathVector4 col3 );

/*
 * Get column 0 of a 4x4 matrix
 */
static inline VmathVector4 vmathM4GetCol0_V( VmathMatrix4 mat );

/*
 * Get column 1 of a 4x4 matrix
 */
static inline VmathVector4 vmathM4GetCol1_V( VmathMatrix4 mat );

/*
 * Get column 2 of a 4x4 matrix
 */
static inline VmathVector4 vmathM4GetCol2_V( VmathMatrix4 mat );

/*
 * Get column 3 of a 4x4 matrix
 */
static inline VmathVector4 vmathM4GetCol3_V( VmathMatrix4 mat );

/*
 * Set the column of a 4x4 matrix referred to by the specified index
 */
static inline void vmathM4SetCol_V( VmathMatrix4 *result, int col, VmathVector4 vec );

/*
 * Set the row of a 4x4 matrix referred to by the specified index
 */
static inline void vmathM4SetRow_V( VmathMatrix4 *result, int row, VmathVector4 vec );

/*
 * Get the column of a 4x4 matrix referred to by the specified index
 */
static inline VmathVector4 vmathM4GetCol_V( VmathMatrix4 mat, int col );

/*
 * Get the row of a 4x4 matrix referred to by the specified index
 */
static inline VmathVector4 vmathM4GetRow_V( VmathMatrix4 mat, int row );

/*
 * Set the element of a 4x4 matrix referred to by column and row indices
 */
static inline void vmathM4SetElem_V( VmathMatrix4 *result, int col, int row, float val );

/*
 * Get the element of a 4x4 matrix referred to by column and row indices
 */
static inline float vmathM4GetElem_V( VmathMatrix4 mat, int col, int row );

/*
 * Add two 4x4 matrices
 */
static inline VmathMatrix4 vmathM4Add_V( VmathMatrix4 mat0, VmathMatrix4 mat1 );

/*
 * Subtract a 4x4 matrix from another 4x4 matrix
 */
static inline VmathMatrix4 vmathM4Sub_V( VmathMatrix4 mat0, VmathMatrix4 mat1 );

/*
 * Negate all elements of a 4x4 matrix
 */
static inline VmathMatrix4 vmathM4Neg_V( VmathMatrix4 mat );

/*
 * Multiply a 4x4 matrix by a scalar
 */
static inline VmathMatrix4 vmathM4ScalarMul_V( VmathMatrix4 mat, float scalar );

/*
 * Multiply a 4x4 matrix by a 4-D vector
 */
static inline VmathVector4 vmathM4MulV4_V( VmathMatrix4 mat, VmathVector4 vec );

/*
 * Multiply a 4x4 matrix by a 3-D vector
 */
static inline VmathVector4 vmathM4MulV3_V( VmathMatrix4 mat, VmathVector3 vec );

/*
 * Multiply a 4x4 matrix by a 3-D point
 */
static inline VmathVector4 vmathM4MulP3_V( VmathMatrix4 mat, VmathPoint3 pnt );

/*
 * Multiply two 4x4 matrices
 */
static inline VmathMatrix4 vmathM4Mul_V( VmathMatrix4 mat0, VmathMatrix4 mat1 );

/*
 * Multiply a 4x4 matrix by a 3x4 transformation matrix
 */
static inline VmathMatrix4 vmathM4MulT3_V( VmathMatrix4 mat, VmathTransform3 tfrm );

/*
 * Construct an identity 4x4 matrix
 */
static inline VmathMatrix4 vmathM4MakeIdentity_V( );

/*
 * Construct a 4x4 matrix to rotate around the x axis
 */
static inline VmathMatrix4 vmathM4MakeRotationX_V( float radians );

/*
 * Construct a 4x4 matrix to rotate around the y axis
 */
static inline VmathMatrix4 vmathM4MakeRotationY_V( float radians );

/*
 * Construct a 4x4 matrix to rotate around the z axis
 */
static inline VmathMatrix4 vmathM4MakeRotationZ_V( float radians );

/*
 * Construct a 4x4 matrix to rotate around the x, y, and z axes
 */
static inline VmathMatrix4 vmathM4MakeRotationZYX_V( VmathVector3 radiansXYZ );

/*
 * Construct a 4x4 matrix to rotate around a unit-length 3-D vector
 */
static inline VmathMatrix4 vmathM4MakeRotationAxis_V( float radians, VmathVector3 unitVec );

/*
 * Construct a rotation matrix from a unit-length quaternion
 */
static inline VmathMatrix4 vmathM4MakeRotationQ_V( VmathQuat unitQuat );

/*
 * Construct a 4x4 matrix to perform scaling
 */
static inline VmathMatrix4 vmathM4MakeScale_V( VmathVector3 scaleVec );

/*
 * Construct a 4x4 matrix to perform translation
 */
static inline VmathMatrix4 vmathM4MakeTranslation_V( VmathVector3 translateVec );

/*
 * Construct viewing matrix based on eye position, position looked at, and up direction
 */
static inline VmathMatrix4 vmathM4MakeLookAt_V( VmathPoint3 eyePos, VmathPoint3 lookAtPos, VmathVector3 upVec );

/*
 * Construct a perspective projection matrix
 */
static inline VmathMatrix4 vmathM4MakePerspective_V( float fovyRadians, float aspect, float zNear, float zFar );

/*
 * Construct a perspective projection matrix based on frustum
 */
static inline VmathMatrix4 vmathM4MakeFrustum_V( float left, float right, float bottom, float top, float zNear, float zFar );

/*
 * Construct an orthographic projection matrix
 */
static inline VmathMatrix4 vmathM4MakeOrthographic_V( float left, float right, float bottom, float top, float zNear, float zFar );

/*
 * Append (post-multiply) a scale transformation to a 4x4 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline VmathMatrix4 vmathM4AppendScale_V( VmathMatrix4 mat, VmathVector3 scaleVec );

/*
 * Prepend (pre-multiply) a scale transformation to a 4x4 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline VmathMatrix4 vmathM4PrependScale_V( VmathVector3 scaleVec, VmathMatrix4 mat );

/*
 * Multiply two 4x4 matrices per element
 */
static inline VmathMatrix4 vmathM4MulPerElem_V( VmathMatrix4 mat0, VmathMatrix4 mat1 );

/*
 * Compute the absolute value of a 4x4 matrix per element
 */
static inline VmathMatrix4 vmathM4AbsPerElem_V( VmathMatrix4 mat );

/*
 * Transpose of a 4x4 matrix
 */
static inline VmathMatrix4 vmathM4Transpose_V( VmathMatrix4 mat );

/*
 * Compute the inverse of a 4x4 matrix
 * NOTE: 
 * Result is unpredictable when the determinant of mat is equal to or near 0.
 */
static inline VmathMatrix4 vmathM4Inverse_V( VmathMatrix4 mat );

/*
 * Compute the inverse of a 4x4 matrix, which is expected to be an affine matrix
 * NOTE: 
 * This can be used to achieve better performance than a general inverse when the specified 4x4 matrix meets the given restrictions.  The result is unpredictable when the determinant of mat is equal to or near 0.
 */
static inline VmathMatrix4 vmathM4AffineInverse_V( VmathMatrix4 mat );

/*
 * Compute the inverse of a 4x4 matrix, which is expected to be an affine matrix with an orthogonal upper-left 3x3 submatrix
 * NOTE: 
 * This can be used to achieve better performance than a general inverse when the specified 4x4 matrix meets the given restrictions.
 */
static inline VmathMatrix4 vmathM4OrthoInverse_V( VmathMatrix4 mat );

/*
 * Determinant of a 4x4 matrix
 */
static inline float vmathM4Determinant_V( VmathMatrix4 mat );

/*
 * Conditionally select between two 4x4 matrices
 */
static inline VmathMatrix4 vmathM4Select_V( VmathMatrix4 mat0, VmathMatrix4 mat1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 4x4 matrix
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM4Print_V( VmathMatrix4 mat );

/*
 * Print a 4x4 matrix and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM4Prints_V( VmathMatrix4 mat, const char *name );

#endif

/*
 * Construct a 3x4 transformation matrix containing the specified columns
 */
static inline VmathTransform3 vmathT3MakeFromCols_V( VmathVector3 col0, VmathVector3 col1, VmathVector3 col2, VmathVector3 col3 );

/*
 * Construct a 3x4 transformation matrix from a 3x3 matrix and a 3-D vector
 */
static inline VmathTransform3 vmathT3MakeFromM3V3_V( VmathMatrix3 tfrm, VmathVector3 translateVec );

/*
 * Construct a 3x4 transformation matrix from a unit-length quaternion and a 3-D vector
 */
static inline VmathTransform3 vmathT3MakeFromQV3_V( VmathQuat unitQuat, VmathVector3 translateVec );

/*
 * Set all elements of a 3x4 transformation matrix to the same scalar value
 */
static inline VmathTransform3 vmathT3MakeFromScalar_V( float scalar );

/*
 * Set the upper-left 3x3 submatrix
 */
static inline void vmathT3SetUpper3x3_V( VmathTransform3 *result, VmathMatrix3 mat3 );

/*
 * Get the upper-left 3x3 submatrix of a 3x4 transformation matrix
 */
static inline VmathMatrix3 vmathT3GetUpper3x3_V( VmathTransform3 tfrm );

/*
 * Set translation component
 */
static inline void vmathT3SetTranslation_V( VmathTransform3 *result, VmathVector3 translateVec );

/*
 * Get the translation component of a 3x4 transformation matrix
 */
static inline VmathVector3 vmathT3GetTranslation_V( VmathTransform3 tfrm );

/*
 * Set column 0 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol0_V( VmathTransform3 *result, VmathVector3 col0 );

/*
 * Set column 1 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol1_V( VmathTransform3 *result, VmathVector3 col1 );

/*
 * Set column 2 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol2_V( VmathTransform3 *result, VmathVector3 col2 );

/*
 * Set column 3 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol3_V( VmathTransform3 *result, VmathVector3 col3 );

/*
 * Get column 0 of a 3x4 transformation matrix
 */
static inline VmathVector3 vmathT3GetCol0_V( VmathTransform3 tfrm );

/*
 * Get column 1 of a 3x4 transformation matrix
 */
static inline VmathVector3 vmathT3GetCol1_V( VmathTransform3 tfrm );

/*
 * Get column 2 of a 3x4 transformation matrix
 */
static inline VmathVector3 vmathT3GetCol2_V( VmathTransform3 tfrm );

/*
 * Get column 3 of a 3x4 transformation matrix
 */
static inline VmathVector3 vmathT3GetCol3_V( VmathTransform3 tfrm );

/*
 * Set the column of a 3x4 transformation matrix referred to by the specified index
 */
static inline void vmathT3SetCol_V( VmathTransform3 *result, int col, VmathVector3 vec );

/*
 * Set the row of a 3x4 transformation matrix referred to by the specified index
 */
static inline void vmathT3SetRow_V( VmathTransform3 *result, int row, VmathVector4 vec );

/*
 * Get the column of a 3x4 transformation matrix referred to by the specified index
 */
static inline VmathVector3 vmathT3GetCol_V( VmathTransform3 tfrm, int col );

/*
 * Get the row of a 3x4 transformation matrix referred to by the specified index
 */
static inline VmathVector4 vmathT3GetRow_V( VmathTransform3 tfrm, int row );

/*
 * Set the element of a 3x4 transformation matrix referred to by column and row indices
 */
static inline void vmathT3SetElem_V( VmathTransform3 *result, int col, int row, float val );

/*
 * Get the element of a 3x4 transformation matrix referred to by column and row indices
 */
static inline float vmathT3GetElem_V( VmathTransform3 tfrm, int col, int row );

/*
 * Multiply a 3x4 transformation matrix by a 3-D vector
 */
static inline VmathVector3 vmathT3MulV3_V( VmathTransform3 tfrm, VmathVector3 vec );

/*
 * Multiply a 3x4 transformation matrix by a 3-D point
 */
static inline VmathPoint3 vmathT3MulP3_V( VmathTransform3 tfrm, VmathPoint3 pnt );

/*
 * Multiply two 3x4 transformation matrices
 */
static inline VmathTransform3 vmathT3Mul_V( VmathTransform3 tfrm0, VmathTransform3 tfrm1 );

/*
 * Construct an identity 3x4 transformation matrix
 */
static inline VmathTransform3 vmathT3MakeIdentity_V( );

/*
 * Construct a 3x4 transformation matrix to rotate around the x axis
 */
static inline VmathTransform3 vmathT3MakeRotationX_V( float radians );

/*
 * Construct a 3x4 transformation matrix to rotate around the y axis
 */
static inline VmathTransform3 vmathT3MakeRotationY_V( float radians );

/*
 * Construct a 3x4 transformation matrix to rotate around the z axis
 */
static inline VmathTransform3 vmathT3MakeRotationZ_V( float radians );

/*
 * Construct a 3x4 transformation matrix to rotate around the x, y, and z axes
 */
static inline VmathTransform3 vmathT3MakeRotationZYX_V( VmathVector3 radiansXYZ );

/*
 * Construct a 3x4 transformation matrix to rotate around a unit-length 3-D vector
 */
static inline VmathTransform3 vmathT3MakeRotationAxis_V( float radians, VmathVector3 unitVec );

/*
 * Construct a rotation matrix from a unit-length quaternion
 */
static inline VmathTransform3 vmathT3MakeRotationQ_V( VmathQuat unitQuat );

/*
 * Construct a 3x4 transformation matrix to perform scaling
 */
static inline VmathTransform3 vmathT3MakeScale_V( VmathVector3 scaleVec );

/*
 * Construct a 3x4 transformation matrix to perform translation
 */
static inline VmathTransform3 vmathT3MakeTranslation_V( VmathVector3 translateVec );

/*
 * Append (post-multiply) a scale transformation to a 3x4 transformation matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline VmathTransform3 vmathT3AppendScale_V( VmathTransform3 tfrm, VmathVector3 scaleVec );

/*
 * Prepend (pre-multiply) a scale transformation to a 3x4 transformation matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline VmathTransform3 vmathT3PrependScale_V( VmathVector3 scaleVec, VmathTransform3 tfrm );

/*
 * Multiply two 3x4 transformation matrices per element
 */
static inline VmathTransform3 vmathT3MulPerElem_V( VmathTransform3 tfrm0, VmathTransform3 tfrm1 );

/*
 * Compute the absolute value of a 3x4 transformation matrix per element
 */
static inline VmathTransform3 vmathT3AbsPerElem_V( VmathTransform3 tfrm );

/*
 * Inverse of a 3x4 transformation matrix
 * NOTE: 
 * Result is unpredictable when the determinant of the left 3x3 submatrix is equal to or near 0.
 */
static inline VmathTransform3 vmathT3Inverse_V( VmathTransform3 tfrm );

/*
 * Compute the inverse of a 3x4 transformation matrix, expected to have an orthogonal upper-left 3x3 submatrix
 * NOTE: 
 * This can be used to achieve better performance than a general inverse when the specified 3x4 transformation matrix meets the given restrictions.
 */
static inline VmathTransform3 vmathT3OrthoInverse_V( VmathTransform3 tfrm );

/*
 * Conditionally select between two 3x4 transformation matrices
 */
static inline VmathTransform3 vmathT3Select_V( VmathTransform3 tfrm0, VmathTransform3 tfrm1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3x4 transformation matrix
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathT3Print_V( VmathTransform3 tfrm );

/*
 * Print a 3x4 transformation matrix and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathT3Prints_V( VmathTransform3 tfrm, const char *name );

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_AOS_C_SCALAR_H
#define _VECTORMATH_AOS_C_SCALAR_H

#ifdef __cplusplus
extern "C" {
#else

#ifdef _MSC_VER
#define inline __inline
#endif

#endif /* __cplusplus */

#ifndef _VECTORMATH_AOS_C_TYPES_H
#define _VECTORMATH_AOS_C_TYPES_H

/* A 3-D vector in array-of-structures format
 */
typedef struct _VmathVector3
{
    float x;
    float y;
    float z;
#ifndef __GNUC__
    float d;
#endif
}
#ifdef __GNUC__
__attribute__ ((aligned(16)))
#endif
VmathVector3;

/* A 4-D vector in array-of-structures format
 */
typedef struct _VmathVector4
{
    float x;
    float y;
    float z;
    float w;
}
#ifdef __GNUC__
__attribute__ ((aligned(16)))
#endif
VmathVector4;

/* A 3-D point in array-of-structures format
 */
typedef struct _VmathPoint3
{
    float x;
    float y;
    float z;
#ifndef __GNUC__
    float d;
#endif
}
#ifdef __GNUC__
__attribute__ ((aligned(16)))
#endif
VmathPoint3;

/* A quaternion in array-of-structures format
 */
typedef struct _VmathQuat
{
    float x;
    float y;
    float z;
    float w;
}
#ifdef __GNUC__
__attribute__ ((aligned(16)))
#endif
VmathQuat;

/* A 3x3 matrix in array-of-structures format
 */
typedef struct _VmathMatrix3
{
    VmathVector3 col0;
    VmathVector3 col1;
    VmathVector3 col2;
} VmathMatrix3;

/* A 4x4 matrix in array-of-structures format
 */
typedef struct _VmathMatrix4
{
    VmathVector4 col0;
    VmathVector4 col1;
    VmathVector4 col2;
    VmathVector4 col3;
} VmathMatrix4;

/* A 3x4 transformation matrix in array-of-structures format
 */
typedef struct _VmathTransform3
{
    VmathVector3 col0;
    VmathVector3 col1;
    VmathVector3 col2;
    VmathVector3 col3;
} VmathTransform3;

#endif

/*
 * Copy a 3-D vector
 */
static inline void vmathV3Copy( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Construct a 3-D vector from x, y, and z elements
 */
static inline void vmathV3MakeFromElems( VmathVector3 *result, float x, float y, float z );

/*
 * Copy elements from a 3-D point into a 3-D vector
 */
static inline void vmathV3MakeFromP3( VmathVector3 *result, const VmathPoint3 *pnt );

/*
 * Set all elements of a 3-D vector to the same scalar value
 */
static inline void vmathV3MakeFromScalar( VmathVector3 *result, float scalar );

/*
 * Set the x element of a 3-D vector
 */
static inline void vmathV3SetX( VmathVector3 *result, float x );

/*
 * Set the y element of a 3-D vector
 */
static inline void vmathV3SetY( VmathVector3 *result, float y );

/*
 * Set the z element of a 3-D vector
 */
static inline void vmathV3SetZ( VmathVector3 *result, float z );

/*
 * Get the x element of a 3-D vector
 */
static inline float vmathV3GetX( const VmathVector3 *vec );

/*
 * Get the y element of a 3-D vector
 */
static inline float vmathV3GetY( const VmathVector3 *vec );

/*
 * Get the z element of a 3-D vector
 */
static inline float vmathV3GetZ( const VmathVector3 *vec );

/*
 * Set an x, y, or z element of a 3-D vector by index
 */
static inline void vmathV3SetElem( VmathVector3 *result, int idx, float value );

/*
 * Get an x, y, or z element of a 3-D vector by index
 */
static inline float vmathV3GetElem( const VmathVector3 *vec, int idx );

/*
 * Add two 3-D vectors
 */
static inline void vmathV3Add( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Subtract a 3-D vector from another 3-D vector
 */
static inline void vmathV3Sub( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Add a 3-D vector to a 3-D point
 */
static inline void vmathV3AddP3( VmathPoint3 *result, const VmathVector3 *vec, const VmathPoint3 *pnt );

/*
 * Multiply a 3-D vector by a scalar
 */
static inline void vmathV3ScalarMul( VmathVector3 *result, const VmathVector3 *vec, float scalar );

/*
 * Divide a 3-D vector by a scalar
 */
static inline void vmathV3ScalarDiv( VmathVector3 *result, const VmathVector3 *vec, float scalar );

/*
 * Negate all elements of a 3-D vector
 */
static inline void vmathV3Neg( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Construct x axis
 */
static inline void vmathV3MakeXAxis( VmathVector3 *result );

/*
 * Construct y axis
 */
static inline void vmathV3MakeYAxis( VmathVector3 *result );

/*
 * Construct z axis
 */
static inline void vmathV3MakeZAxis( VmathVector3 *result );

/*
 * Multiply two 3-D vectors per element
 */
static inline void vmathV3MulPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Divide two 3-D vectors per element
 * NOTE: 
 * Floating-point behavior matches standard library function divf4.
 */
static inline void vmathV3DivPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Compute the reciprocal of a 3-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function recipf4.
 */
static inline void vmathV3RecipPerElem( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Compute the square root of a 3-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function sqrtf4.
 */
static inline void vmathV3SqrtPerElem( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Compute the reciprocal square root of a 3-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function rsqrtf4.
 */
static inline void vmathV3RsqrtPerElem( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Compute the absolute value of a 3-D vector per element
 */
static inline void vmathV3AbsPerElem( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Copy sign from one 3-D vector to another, per element
 */
static inline void vmathV3CopySignPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Maximum of two 3-D vectors per element
 */
static inline void vmathV3MaxPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Minimum of two 3-D vectors per element
 */
static inline void vmathV3MinPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Maximum element of a 3-D vector
 */
static inline float vmathV3MaxElem( const VmathVector3 *vec );

/*
 * Minimum element of a 3-D vector
 */
static inline float vmathV3MinElem( const VmathVector3 *vec );

/*
 * Compute the sum of all elements of a 3-D vector
 */
static inline float vmathV3Sum( const VmathVector3 *vec );

/*
 * Compute the dot product of two 3-D vectors
 */
static inline float vmathV3Dot( const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Compute the square of the length of a 3-D vector
 */
static inline float vmathV3LengthSqr( const VmathVector3 *vec );

/*
 * Compute the length of a 3-D vector
 */
static inline float vmathV3Length( const VmathVector3 *vec );

/*
 * Normalize a 3-D vector
 * NOTE: 
 * The result is unpredictable when all elements of vec are at or near zero.
 */
static inline void vmathV3Normalize( VmathVector3 *result, const VmathVector3 *vec );

/*
 * Compute cross product of two 3-D vectors
 */
static inline void vmathV3Cross( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Outer product of two 3-D vectors
 */
static inline void vmathV3Outer( VmathMatrix3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Pre-multiply a row vector by a 3x3 matrix
 */
static inline void vmathV3RowMul( VmathVector3 *result, const VmathVector3 *vec, const VmathMatrix3 *mat );

/*
 * Cross-product matrix of a 3-D vector
 */
static inline void vmathV3CrossMatrix( VmathMatrix3 *result, const VmathVector3 *vec );

/*
 * Create cross-product matrix and multiply
 * NOTE: 
 * Faster than separately creating a cross-product matrix and multiplying.
 */
static inline void vmathV3CrossMatrixMul( VmathMatrix3 *result, const VmathVector3 *vec, const VmathMatrix3 *mat );

/*
 * Linear interpolation between two 3-D vectors
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline void vmathV3Lerp( VmathVector3 *result, float t, const VmathVector3 *vec0, const VmathVector3 *vec1 );

/*
 * Spherical linear interpolation between two 3-D vectors
 * NOTE: 
 * The result is unpredictable if the vectors point in opposite directions.
 * Does not clamp t between 0 and 1.
 */
static inline void vmathV3Slerp( VmathVector3 *result, float t, const VmathVector3 *unitVec0, const VmathVector3 *unitVec1 );

/*
 * Conditionally select between two 3-D vectors
 */
static inline void vmathV3Select( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3-D vector
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV3Print( const VmathVector3 *vec );

/*
 * Print a 3-D vector and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV3Prints( const VmathVector3 *vec, const char *name );

#endif

/*
 * Copy a 4-D vector
 */
static inline void vmathV4Copy( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Construct a 4-D vector from x, y, z, and w elements
 */
static inline void vmathV4MakeFromElems( VmathVector4 *result, float x, float y, float z, float w );

/*
 * Construct a 4-D vector from a 3-D vector and a scalar
 */
static inline void vmathV4MakeFromV3Scalar( VmathVector4 *result, const VmathVector3 *xyz, float w );

/*
 * Copy x, y, and z from a 3-D vector into a 4-D vector, and set w to 0
 */
static inline void vmathV4MakeFromV3( VmathVector4 *result, const VmathVector3 *vec );

/*
 * Copy x, y, and z from a 3-D point into a 4-D vector, and set w to 1
 */
static inline void vmathV4MakeFromP3( VmathVector4 *result, const VmathPoint3 *pnt );

/*
 * Copy elements from a quaternion into a 4-D vector
 */
static inline void vmathV4MakeFromQ( VmathVector4 *result, const VmathQuat *quat );

/*
 * Set all elements of a 4-D vector to the same scalar value
 */
static inline void vmathV4MakeFromScalar( VmathVector4 *result, float scalar );

/*
 * Set the x, y, and z elements of a 4-D vector
 * NOTE: 
 * This function does not change the w element.
 */
static inline void vmathV4SetXYZ( VmathVector4 *result, const VmathVector3 *vec );

/*
 * Get the x, y, and z elements of a 4-D vector
 */
static inline void vmathV4GetXYZ( VmathVector3 *result, const VmathVector4 *vec );

/*
 * Set the x element of a 4-D vector
 */
static inline void vmathV4SetX( VmathVector4 *result, float x );

/*
 * Set the y element of a 4-D vector
 */
static inline void vmathV4SetY( VmathVector4 *result, float y );

/*
 * Set the z element of a 4-D vector
 */
static inline void vmathV4SetZ( VmathVector4 *result, float z );

/*
 * Set the w element of a 4-D vector
 */
static inline void vmathV4SetW( VmathVector4 *result, float w );

/*
 * Get the x element of a 4-D vector
 */
static inline float vmathV4GetX( const VmathVector4 *vec );

/*
 * Get the y element of a 4-D vector
 */
static inline float vmathV4GetY( const VmathVector4 *vec );

/*
 * Get the z element of a 4-D vector
 */
static inline float vmathV4GetZ( const VmathVector4 *vec );

/*
 * Get the w element of a 4-D vector
 */
static inline float vmathV4GetW( const VmathVector4 *vec );

/*
 * Set an x, y, z, or w element of a 4-D vector by index
 */
static inline void vmathV4SetElem( VmathVector4 *result, int idx, float value );

/*
 * Get an x, y, z, or w element of a 4-D vector by index
 */
static inline float vmathV4GetElem( const VmathVector4 *vec, int idx );

/*
 * Add two 4-D vectors
 */
static inline void vmathV4Add( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Subtract a 4-D vector from another 4-D vector
 */
static inline void vmathV4Sub( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Multiply a 4-D vector by a scalar
 */
static inline void vmathV4ScalarMul( VmathVector4 *result, const VmathVector4 *vec, float scalar );

/*
 * Divide a 4-D vector by a scalar
 */
static inline void vmathV4ScalarDiv( VmathVector4 *result, const VmathVector4 *vec, float scalar );

/*
 * Negate all elements of a 4-D vector
 */
static inline void vmathV4Neg( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Construct x axis
 */
static inline void vmathV4MakeXAxis( VmathVector4 *result );

/*
 * Construct y axis
 */
static inline void vmathV4MakeYAxis( VmathVector4 *result );

/*
 * Construct z axis
 */
static inline void vmathV4MakeZAxis( VmathVector4 *result );

/*
 * Construct w axis
 */
static inline void vmathV4MakeWAxis( VmathVector4 *result );

/*
 * Multiply two 4-D vectors per element
 */
static inline void vmathV4MulPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Divide two 4-D vectors per element
 * NOTE: 
 * Floating-point behavior matches standard library function divf4.
 */
static inline void vmathV4DivPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Compute the reciprocal of a 4-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function recipf4.
 */
static inline void vmathV4RecipPerElem( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Compute the square root of a 4-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function sqrtf4.
 */
static inline void vmathV4SqrtPerElem( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Compute the reciprocal square root of a 4-D vector per element
 * NOTE: 
 * Floating-point behavior matches standard library function rsqrtf4.
 */
static inline void vmathV4RsqrtPerElem( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Compute the absolute value of a 4-D vector per element
 */
static inline void vmathV4AbsPerElem( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Copy sign from one 4-D vector to another, per element
 */
static inline void vmathV4CopySignPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Maximum of two 4-D vectors per element
 */
static inline void vmathV4MaxPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Minimum of two 4-D vectors per element
 */
static inline void vmathV4MinPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Maximum element of a 4-D vector
 */
static inline float vmathV4MaxElem( const VmathVector4 *vec );

/*
 * Minimum element of a 4-D vector
 */
static inline float vmathV4MinElem( const VmathVector4 *vec );

/*
 * Compute the sum of all elements of a 4-D vector
 */
static inline float vmathV4Sum( const VmathVector4 *vec );

/*
 * Compute the dot product of two 4-D vectors
 */
static inline float vmathV4Dot( const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Compute the square of the length of a 4-D vector
 */
static inline float vmathV4LengthSqr( const VmathVector4 *vec );

/*
 * Compute the length of a 4-D vector
 */
static inline float vmathV4Length( const VmathVector4 *vec );

/*
 * Normalize a 4-D vector
 * NOTE: 
 * The result is unpredictable when all elements of vec are at or near zero.
 */
static inline void vmathV4Normalize( VmathVector4 *result, const VmathVector4 *vec );

/*
 * Outer product of two 4-D vectors
 */
static inline void vmathV4Outer( VmathMatrix4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Linear interpolation between two 4-D vectors
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline void vmathV4Lerp( VmathVector4 *result, float t, const VmathVector4 *vec0, const VmathVector4 *vec1 );

/*
 * Spherical linear interpolation between two 4-D vectors
 * NOTE: 
 * The result is unpredictable if the vectors point in opposite directions.
 * Does not clamp t between 0 and 1.
 */
static inline void vmathV4Slerp( VmathVector4 *result, float t, const VmathVector4 *unitVec0, const VmathVector4 *unitVec1 );

/*
 * Conditionally select between two 4-D vectors
 */
static inline void vmathV4Select( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 4-D vector
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV4Print( const VmathVector4 *vec );

/*
 * Print a 4-D vector and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathV4Prints( const VmathVector4 *vec, const char *name );

#endif

/*
 * Copy a 3-D point
 */
static inline void vmathP3Copy( VmathPoint3 *result, const VmathPoint3 *pnt );

/*
 * Construct a 3-D point from x, y, and z elements
 */
static inline void vmathP3MakeFromElems( VmathPoint3 *result, float x, float y, float z );

/*
 * Copy elements from a 3-D vector into a 3-D point
 */
static inline void vmathP3MakeFromV3( VmathPoint3 *result, const VmathVector3 *vec );

/*
 * Set all elements of a 3-D point to the same scalar value
 */
static inline void vmathP3MakeFromScalar( VmathPoint3 *result, float scalar );

/*
 * Set the x element of a 3-D point
 */
static inline void vmathP3SetX( VmathPoint3 *result, float x );

/*
 * Set the y element of a 3-D point
 */
static inline void vmathP3SetY( VmathPoint3 *result, float y );

/*
 * Set the z element of a 3-D point
 */
static inline void vmathP3SetZ( VmathPoint3 *result, float z );

/*
 * Get the x element of a 3-D point
 */
static inline float vmathP3GetX( const VmathPoint3 *pnt );

/*
 * Get the y element of a 3-D point
 */
static inline float vmathP3GetY( const VmathPoint3 *pnt );

/*
 * Get the z element of a 3-D point
 */
static inline float vmathP3GetZ( const VmathPoint3 *pnt );

/*
 * Set an x, y, or z element of a 3-D point by index
 */
static inline void vmathP3SetElem( VmathPoint3 *result, int idx, float value );

/*
 * Get an x, y, or z element of a 3-D point by index
 */
static inline float vmathP3GetElem( const VmathPoint3 *pnt, int idx );

/*
 * Subtract a 3-D point from another 3-D point
 */
static inline void vmathP3Sub( VmathVector3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Add a 3-D point to a 3-D vector
 */
static inline void vmathP3AddV3( VmathPoint3 *result, const VmathPoint3 *pnt, const VmathVector3 *vec );

/*
 * Subtract a 3-D vector from a 3-D point
 */
static inline void vmathP3SubV3( VmathPoint3 *result, const VmathPoint3 *pnt, const VmathVector3 *vec );

/*
 * Multiply two 3-D points per element
 */
static inline void vmathP3MulPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Divide two 3-D points per element
 * NOTE: 
 * Floating-point behavior matches standard library function divf4.
 */
static inline void vmathP3DivPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Compute the reciprocal of a 3-D point per element
 * NOTE: 
 * Floating-point behavior matches standard library function recipf4.
 */
static inline void vmathP3RecipPerElem( VmathPoint3 *result, const VmathPoint3 *pnt );

/*
 * Compute the square root of a 3-D point per element
 * NOTE: 
 * Floating-point behavior matches standard library function sqrtf4.
 */
static inline void vmathP3SqrtPerElem( VmathPoint3 *result, const VmathPoint3 *pnt );

/*
 * Compute the reciprocal square root of a 3-D point per element
 * NOTE: 
 * Floating-point behavior matches standard library function rsqrtf4.
 */
static inline void vmathP3RsqrtPerElem( VmathPoint3 *result, const VmathPoint3 *pnt );

/*
 * Compute the absolute value of a 3-D point per element
 */
static inline void vmathP3AbsPerElem( VmathPoint3 *result, const VmathPoint3 *pnt );

/*
 * Copy sign from one 3-D point to another, per element
 */
static inline void vmathP3CopySignPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Maximum of two 3-D points per element
 */
static inline void vmathP3MaxPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Minimum of two 3-D points per element
 */
static inline void vmathP3MinPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Maximum element of a 3-D point
 */
static inline float vmathP3MaxElem( const VmathPoint3 *pnt );

/*
 * Minimum element of a 3-D point
 */
static inline float vmathP3MinElem( const VmathPoint3 *pnt );

/*
 * Compute the sum of all elements of a 3-D point
 */
static inline float vmathP3Sum( const VmathPoint3 *pnt );

/*
 * Apply uniform scale to a 3-D point
 */
static inline void vmathP3Scale( VmathPoint3 *result, const VmathPoint3 *pnt, float scaleVal );

/*
 * Apply non-uniform scale to a 3-D point
 */
static inline void vmathP3NonUniformScale( VmathPoint3 *result, const VmathPoint3 *pnt, const VmathVector3 *scaleVec );

/*
 * Scalar projection of a 3-D point on a unit-length 3-D vector
 */
static inline float vmathP3Projection( const VmathPoint3 *pnt, const VmathVector3 *unitVec );

/*
 * Compute the square of the distance of a 3-D point from the coordinate-system origin
 */
static inline float vmathP3DistSqrFromOrigin( const VmathPoint3 *pnt );

/*
 * Compute the distance of a 3-D point from the coordinate-system origin
 */
static inline float vmathP3DistFromOrigin( const VmathPoint3 *pnt );

/*
 * Compute the square of the distance between two 3-D points
 */
static inline float vmathP3DistSqr( const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Compute the distance between two 3-D points
 */
static inline float vmathP3Dist( const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Linear interpolation between two 3-D points
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline void vmathP3Lerp( VmathPoint3 *result, float t, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 );

/*
 * Conditionally select between two 3-D points
 */
static inline void vmathP3Select( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3-D point
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathP3Print( const VmathPoint3 *pnt );

/*
 * Print a 3-D point and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathP3Prints( const VmathPoint3 *pnt, const char *name );

#endif

/*
 * Copy a quaternion
 */
static inline void vmathQCopy( VmathQuat *result, const VmathQuat *quat );

/*
 * Construct a quaternion from x, y, z, and w elements
 */
static inline void vmathQMakeFromElems( VmathQuat *result, float x, float y, float z, float w );

/*
 * Construct a quaternion from a 3-D vector and a scalar
 */
static inline void vmathQMakeFromV3Scalar( VmathQuat *result, const VmathVector3 *xyz, float w );

/*
 * Copy elements from a 4-D vector into a quaternion
 */
static inline void vmathQMakeFromV4( VmathQuat *result, const VmathVector4 *vec );

/*
 * Convert a rotation matrix to a unit-length quaternion
 */
static inline void vmathQMakeFromM3( VmathQuat *result, const VmathMatrix3 *rotMat );

/*
 * Set all elements of a quaternion to the same scalar value
 */
static inline void vmathQMakeFromScalar( VmathQuat *result, float scalar );

/*
 * Set the x, y, and z elements of a quaternion
 * NOTE: 
 * This function does not change the w element.
 */
static inline void vmathQSetXYZ( VmathQuat *result, const VmathVector3 *vec );

/*
 * Get the x, y, and z elements of a quaternion
 */
static inline void vmathQGetXYZ( VmathVector3 *result, const VmathQuat *quat );

/*
 * Set the x element of a quaternion
 */
static inline void vmathQSetX( VmathQuat *result, float x );

/*
 * Set the y element of a quaternion
 */
static inline void vmathQSetY( VmathQuat *result, float y );

/*
 * Set the z element of a quaternion
 */
static inline void vmathQSetZ( VmathQuat *result, float z );

/*
 * Set the w element of a quaternion
 */
static inline void vmathQSetW( VmathQuat *result, float w );

/*
 * Get the x element of a quaternion
 */
static inline float vmathQGetX( const VmathQuat *quat );

/*
 * Get the y element of a quaternion
 */
static inline float vmathQGetY( const VmathQuat *quat );

/*
 * Get the z element of a quaternion
 */
static inline float vmathQGetZ( const VmathQuat *quat );

/*
 * Get the w element of a quaternion
 */
static inline float vmathQGetW( const VmathQuat *quat );

/*
 * Set an x, y, z, or w element of a quaternion by index
 */
static inline void vmathQSetElem( VmathQuat *result, int idx, float value );

/*
 * Get an x, y, z, or w element of a quaternion by index
 */
static inline float vmathQGetElem( const VmathQuat *quat, int idx );

/*
 * Add two quaternions
 */
static inline void vmathQAdd( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1 );

/*
 * Subtract a quaternion from another quaternion
 */
static inline void vmathQSub( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1 );

/*
 * Multiply two quaternions
 */
static inline void vmathQMul( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1 );

/*
 * Multiply a quaternion by a scalar
 */
static inline void vmathQScalarMul( VmathQuat *result, const VmathQuat *quat, float scalar );

/*
 * Divide a quaternion by a scalar
 */
static inline void vmathQScalarDiv( VmathQuat *result, const VmathQuat *quat, float scalar );

/*
 * Negate all elements of a quaternion
 */
static inline void vmathQNeg( VmathQuat *result, const VmathQuat *quat );

/*
 * Construct an identity quaternion
 */
static inline void vmathQMakeIdentity( VmathQuat *result );

/*
 * Construct a quaternion to rotate between two unit-length 3-D vectors
 * NOTE: 
 * The result is unpredictable if unitVec0 and unitVec1 point in opposite directions.
 */
static inline void vmathQMakeRotationArc( VmathQuat *result, const VmathVector3 *unitVec0, const VmathVector3 *unitVec1 );

/*
 * Construct a quaternion to rotate around a unit-length 3-D vector
 */
static inline void vmathQMakeRotationAxis( VmathQuat *result, float radians, const VmathVector3 *unitVec );

/*
 * Construct a quaternion to rotate around the x axis
 */
static inline void vmathQMakeRotationX( VmathQuat *result, float radians );

/*
 * Construct a quaternion to rotate around the y axis
 */
static inline void vmathQMakeRotationY( VmathQuat *result, float radians );

/*
 * Construct a quaternion to rotate around the z axis
 */
static inline void vmathQMakeRotationZ( VmathQuat *result, float radians );

/*
 * Compute the conjugate of a quaternion
 */
static inline void vmathQConj( VmathQuat *result, const VmathQuat *quat );

/*
 * Use a unit-length quaternion to rotate a 3-D vector
 */
static inline void vmathQRotate( VmathVector3 *result, const VmathQuat *unitQuat, const VmathVector3 *vec );

/*
 * Compute the dot product of two quaternions
 */
static inline float vmathQDot( const VmathQuat *quat0, const VmathQuat *quat1 );

/*
 * Compute the norm of a quaternion
 */
static inline float vmathQNorm( const VmathQuat *quat );

/*
 * Compute the length of a quaternion
 */
static inline float vmathQLength( const VmathQuat *quat );

/*
 * Normalize a quaternion
 * NOTE: 
 * The result is unpredictable when all elements of quat are at or near zero.
 */
static inline void vmathQNormalize( VmathQuat *result, const VmathQuat *quat );

/*
 * Linear interpolation between two quaternions
 * NOTE: 
 * Does not clamp t between 0 and 1.
 */
static inline void vmathQLerp( VmathQuat *result, float t, const VmathQuat *quat0, const VmathQuat *quat1 );

/*
 * Spherical linear interpolation between two quaternions
 * NOTE: 
 * Interpolates along the shortest path between orientations.
 * Does not clamp t between 0 and 1.
 */
static inline void vmathQSlerp( VmathQuat *result, float t, const VmathQuat *unitQuat0, const VmathQuat *unitQuat1 );

/*
 * Spherical quadrangle interpolation
 */
static inline void vmathQSquad( VmathQuat *result, float t, const VmathQuat *unitQuat0, const VmathQuat *unitQuat1, const VmathQuat *unitQuat2, const VmathQuat *unitQuat3 );

/*
 * Conditionally select between two quaternions
 */
static inline void vmathQSelect( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a quaternion
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathQPrint( const VmathQuat *quat );

/*
 * Print a quaternion and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathQPrints( const VmathQuat *quat, const char *name );

#endif

/*
 * Copy a 3x3 matrix
 */
static inline void vmathM3Copy( VmathMatrix3 *result, const VmathMatrix3 *mat );

/*
 * Construct a 3x3 matrix containing the specified columns
 */
static inline void vmathM3MakeFromCols( VmathMatrix3 *result, const VmathVector3 *col0, const VmathVector3 *col1, const VmathVector3 *col2 );

/*
 * Construct a 3x3 rotation matrix from a unit-length quaternion
 */
static inline void vmathM3MakeFromQ( VmathMatrix3 *result, const VmathQuat *unitQuat );

/*
 * Set all elements of a 3x3 matrix to the same scalar value
 */
static inline void vmathM3MakeFromScalar( VmathMatrix3 *result, float scalar );

/*
 * Set column 0 of a 3x3 matrix
 */
static inline void vmathM3SetCol0( VmathMatrix3 *result, const VmathVector3 *col0 );

/*
 * Set column 1 of a 3x3 matrix
 */
static inline void vmathM3SetCol1( VmathMatrix3 *result, const VmathVector3 *col1 );

/*
 * Set column 2 of a 3x3 matrix
 */
static inline void vmathM3SetCol2( VmathMatrix3 *result, const VmathVector3 *col2 );

/*
 * Get column 0 of a 3x3 matrix
 */
static inline void vmathM3GetCol0( VmathVector3 *result, const VmathMatrix3 *mat );

/*
 * Get column 1 of a 3x3 matrix
 */
static inline void vmathM3GetCol1( VmathVector3 *result, const VmathMatrix3 *mat );

/*
 * Get column 2 of a 3x3 matrix
 */
static inline void vmathM3GetCol2( VmathVector3 *result, const VmathMatrix3 *mat );

/*
 * Set the column of a 3x3 matrix referred to by the specified index
 */
static inline void vmathM3SetCol( VmathMatrix3 *result, int col, const VmathVector3 *vec );

/*
 * Set the row of a 3x3 matrix referred to by the specified index
 */
static inline void vmathM3SetRow( VmathMatrix3 *result, int row, const VmathVector3 *vec );

/*
 * Get the column of a 3x3 matrix referred to by the specified index
 */
static inline void vmathM3GetCol( VmathVector3 *result, const VmathMatrix3 *mat, int col );

/*
 * Get the row of a 3x3 matrix referred to by the specified index
 */
static inline void vmathM3GetRow( VmathVector3 *result, const VmathMatrix3 *mat, int row );

/*
 * Set the element of a 3x3 matrix referred to by column and row indices
 */
static inline void vmathM3SetElem( VmathMatrix3 *result, int col, int row, float val );

/*
 * Get the element of a 3x3 matrix referred to by column and row indices
 */
static inline float vmathM3GetElem( const VmathMatrix3 *mat, int col, int row );

/*
 * Add two 3x3 matrices
 */
static inline void vmathM3Add( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 );

/*
 * Subtract a 3x3 matrix from another 3x3 matrix
 */
static inline void vmathM3Sub( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 );

/*
 * Negate all elements of a 3x3 matrix
 */
static inline void vmathM3Neg( VmathMatrix3 *result, const VmathMatrix3 *mat );

/*
 * Multiply a 3x3 matrix by a scalar
 */
static inline void vmathM3ScalarMul( VmathMatrix3 *result, const VmathMatrix3 *mat, float scalar );

/*
 * Multiply a 3x3 matrix by a 3-D vector
 */
static inline void vmathM3MulV3( VmathVector3 *result, const VmathMatrix3 *mat, const VmathVector3 *vec );

/*
 * Multiply two 3x3 matrices
 */
static inline void vmathM3Mul( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 );

/*
 * Construct an identity 3x3 matrix
 */
static inline void vmathM3MakeIdentity( VmathMatrix3 *result );

/*
 * Construct a 3x3 matrix to rotate around the x axis
 */
static inline void vmathM3MakeRotationX( VmathMatrix3 *result, float radians );

/*
 * Construct a 3x3 matrix to rotate around the y axis
 */
static inline void vmathM3MakeRotationY( VmathMatrix3 *result, float radians );

/*
 * Construct a 3x3 matrix to rotate around the z axis
 */
static inline void vmathM3MakeRotationZ( VmathMatrix3 *result, float radians );

/*
 * Construct a 3x3 matrix to rotate around the x, y, and z axes
 */
static inline void vmathM3MakeRotationZYX( VmathMatrix3 *result, const VmathVector3 *radiansXYZ );

/*
 * Construct a 3x3 matrix to rotate around a unit-length 3-D vector
 */
static inline void vmathM3MakeRotationAxis( VmathMatrix3 *result, float radians, const VmathVector3 *unitVec );

/*
 * Construct a rotation matrix from a unit-length quaternion
 */
static inline void vmathM3MakeRotationQ( VmathMatrix3 *result, const VmathQuat *unitQuat );

/*
 * Construct a 3x3 matrix to perform scaling
 */
static inline void vmathM3MakeScale( VmathMatrix3 *result, const VmathVector3 *scaleVec );

/*
 * Append (post-multiply) a scale transformation to a 3x3 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline void vmathM3AppendScale( VmathMatrix3 *result, const VmathMatrix3 *mat, const VmathVector3 *scaleVec );

/*
 * Prepend (pre-multiply) a scale transformation to a 3x3 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline void vmathM3PrependScale( VmathMatrix3 *result, const VmathVector3 *scaleVec, const VmathMatrix3 *mat );

/*
 * Multiply two 3x3 matrices per element
 */
static inline void vmathM3MulPerElem( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 );

/*
 * Compute the absolute value of a 3x3 matrix per element
 */
static inline void vmathM3AbsPerElem( VmathMatrix3 *result, const VmathMatrix3 *mat );

/*
 * Transpose of a 3x3 matrix
 */
static inline void vmathM3Transpose( VmathMatrix3 *result, const VmathMatrix3 *mat );

/*
 * Compute the inverse of a 3x3 matrix
 * NOTE: 
 * Result is unpredictable when the determinant of mat is equal to or near 0.
 */
static inline void vmathM3Inverse( VmathMatrix3 *result, const VmathMatrix3 *mat );

/*
 * Determinant of a 3x3 matrix
 */
static inline float vmathM3Determinant( const VmathMatrix3 *mat );

/*
 * Conditionally select between two 3x3 matrices
 */
static inline void vmathM3Select( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3x3 matrix
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM3Print( const VmathMatrix3 *mat );

/*
 * Print a 3x3 matrix and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM3Prints( const VmathMatrix3 *mat, const char *name );

#endif

/*
 * Copy a 4x4 matrix
 */
static inline void vmathM4Copy( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Construct a 4x4 matrix containing the specified columns
 */
static inline void vmathM4MakeFromCols( VmathMatrix4 *result, const VmathVector4 *col0, const VmathVector4 *col1, const VmathVector4 *col2, const VmathVector4 *col3 );

/*
 * Construct a 4x4 matrix from a 3x4 transformation matrix
 */
static inline void vmathM4MakeFromT3( VmathMatrix4 *result, const VmathTransform3 *mat );

/*
 * Construct a 4x4 matrix from a 3x3 matrix and a 3-D vector
 */
static inline void vmathM4MakeFromM3V3( VmathMatrix4 *result, const VmathMatrix3 *mat, const VmathVector3 *translateVec );

/*
 * Construct a 4x4 matrix from a unit-length quaternion and a 3-D vector
 */
static inline void vmathM4MakeFromQV3( VmathMatrix4 *result, const VmathQuat *unitQuat, const VmathVector3 *translateVec );

/*
 * Set all elements of a 4x4 matrix to the same scalar value
 */
static inline void vmathM4MakeFromScalar( VmathMatrix4 *result, float scalar );

/*
 * Set the upper-left 3x3 submatrix
 * NOTE: 
 * This function does not change the bottom row elements.
 */
static inline void vmathM4SetUpper3x3( VmathMatrix4 *result, const VmathMatrix3 *mat3 );

/*
 * Get the upper-left 3x3 submatrix of a 4x4 matrix
 */
static inline void vmathM4GetUpper3x3( VmathMatrix3 *result, const VmathMatrix4 *mat );

/*
 * Set translation component
 * NOTE: 
 * This function does not change the bottom row elements.
 */
static inline void vmathM4SetTranslation( VmathMatrix4 *result, const VmathVector3 *translateVec );

/*
 * Get the translation component of a 4x4 matrix
 */
static inline void vmathM4GetTranslation( VmathVector3 *result, const VmathMatrix4 *mat );

/*
 * Set column 0 of a 4x4 matrix
 */
static inline void vmathM4SetCol0( VmathMatrix4 *result, const VmathVector4 *col0 );

/*
 * Set column 1 of a 4x4 matrix
 */
static inline void vmathM4SetCol1( VmathMatrix4 *result, const VmathVector4 *col1 );

/*
 * Set column 2 of a 4x4 matrix
 */
static inline void vmathM4SetCol2( VmathMatrix4 *result, const VmathVector4 *col2 );

/*
 * Set column 3 of a 4x4 matrix
 */
static inline void vmathM4SetCol3( VmathMatrix4 *result, const VmathVector4 *col3 );

/*
 * Get column 0 of a 4x4 matrix
 */
static inline void vmathM4GetCol0( VmathVector4 *result, const VmathMatrix4 *mat );

/*
 * Get column 1 of a 4x4 matrix
 */
static inline void vmathM4GetCol1( VmathVector4 *result, const VmathMatrix4 *mat );

/*
 * Get column 2 of a 4x4 matrix
 */
static inline void vmathM4GetCol2( VmathVector4 *result, const VmathMatrix4 *mat );

/*
 * Get column 3 of a 4x4 matrix
 */
static inline void vmathM4GetCol3( VmathVector4 *result, const VmathMatrix4 *mat );

/*
 * Set the column of a 4x4 matrix referred to by the specified index
 */
static inline void vmathM4SetCol( VmathMatrix4 *result, int col, const VmathVector4 *vec );

/*
 * Set the row of a 4x4 matrix referred to by the specified index
 */
static inline void vmathM4SetRow( VmathMatrix4 *result, int row, const VmathVector4 *vec );

/*
 * Get the column of a 4x4 matrix referred to by the specified index
 */
static inline void vmathM4GetCol( VmathVector4 *result, const VmathMatrix4 *mat, int col );

/*
 * Get the row of a 4x4 matrix referred to by the specified index
 */
static inline void vmathM4GetRow( VmathVector4 *result, const VmathMatrix4 *mat, int row );

/*
 * Set the element of a 4x4 matrix referred to by column and row indices
 */
static inline void vmathM4SetElem( VmathMatrix4 *result, int col, int row, float val );

/*
 * Get the element of a 4x4 matrix referred to by column and row indices
 */
static inline float vmathM4GetElem( const VmathMatrix4 *mat, int col, int row );

/*
 * Add two 4x4 matrices
 */
static inline void vmathM4Add( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 );

/*
 * Subtract a 4x4 matrix from another 4x4 matrix
 */
static inline void vmathM4Sub( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 );

/*
 * Negate all elements of a 4x4 matrix
 */
static inline void vmathM4Neg( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Multiply a 4x4 matrix by a scalar
 */
static inline void vmathM4ScalarMul( VmathMatrix4 *result, const VmathMatrix4 *mat, float scalar );

/*
 * Multiply a 4x4 matrix by a 4-D vector
 */
static inline void vmathM4MulV4( VmathVector4 *result, const VmathMatrix4 *mat, const VmathVector4 *vec );

/*
 * Multiply a 4x4 matrix by a 3-D vector
 */
static inline void vmathM4MulV3( VmathVector4 *result, const VmathMatrix4 *mat, const VmathVector3 *vec );

/*
 * Multiply a 4x4 matrix by a 3-D point
 */
static inline void vmathM4MulP3( VmathVector4 *result, const VmathMatrix4 *mat, const VmathPoint3 *pnt );

/*
 * Multiply two 4x4 matrices
 */
static inline void vmathM4Mul( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 );

/*
 * Multiply a 4x4 matrix by a 3x4 transformation matrix
 */
static inline void vmathM4MulT3( VmathMatrix4 *result, const VmathMatrix4 *mat, const VmathTransform3 *tfrm );

/*
 * Construct an identity 4x4 matrix
 */
static inline void vmathM4MakeIdentity( VmathMatrix4 *result );

/*
 * Construct a 4x4 matrix to rotate around the x axis
 */
static inline void vmathM4MakeRotationX( VmathMatrix4 *result, float radians );

/*
 * Construct a 4x4 matrix to rotate around the y axis
 */
static inline void vmathM4MakeRotationY( VmathMatrix4 *result, float radians );

/*
 * Construct a 4x4 matrix to rotate around the z axis
 */
static inline void vmathM4MakeRotationZ( VmathMatrix4 *result, float radians );

/*
 * Construct a 4x4 matrix to rotate around the x, y, and z axes
 */
static inline void vmathM4MakeRotationZYX( VmathMatrix4 *result, const VmathVector3 *radiansXYZ );

/*
 * Construct a 4x4 matrix to rotate around a unit-length 3-D vector
 */
static inline void vmathM4MakeRotationAxis( VmathMatrix4 *result, float radians, const VmathVector3 *unitVec );

/*
 * Construct a rotation matrix from a unit-length quaternion
 */
static inline void vmathM4MakeRotationQ( VmathMatrix4 *result, const VmathQuat *unitQuat );

/*
 * Construct a 4x4 matrix to perform scaling
 */
static inline void vmathM4MakeScale( VmathMatrix4 *result, const VmathVector3 *scaleVec );

/*
 * Construct a 4x4 matrix to perform translation
 */
static inline void vmathM4MakeTranslation( VmathMatrix4 *result, const VmathVector3 *translateVec );

/*
 * Construct viewing matrix based on eye position, position looked at, and up direction
 */
static inline void vmathM4MakeLookAt( VmathMatrix4 *result, const VmathPoint3 *eyePos, const VmathPoint3 *lookAtPos, const VmathVector3 *upVec );

/*
 * Construct a perspective projection matrix
 */
static inline void vmathM4MakePerspective( VmathMatrix4 *result, float fovyRadians, float aspect, float zNear, float zFar );

/*
 * Construct a perspective projection matrix based on frustum
 */
static inline void vmathM4MakeFrustum( VmathMatrix4 *result, float left, float right, float bottom, float top, float zNear, float zFar );

/*
 * Construct an orthographic projection matrix
 */
static inline void vmathM4MakeOrthographic( VmathMatrix4 *result, float left, float right, float bottom, float top, float zNear, float zFar );

/*
 * Append (post-multiply) a scale transformation to a 4x4 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline void vmathM4AppendScale( VmathMatrix4 *result, const VmathMatrix4 *mat, const VmathVector3 *scaleVec );

/*
 * Prepend (pre-multiply) a scale transformation to a 4x4 matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline void vmathM4PrependScale( VmathMatrix4 *result, const VmathVector3 *scaleVec, const VmathMatrix4 *mat );

/*
 * Multiply two 4x4 matrices per element
 */
static inline void vmathM4MulPerElem( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 );

/*
 * Compute the absolute value of a 4x4 matrix per element
 */
static inline void vmathM4AbsPerElem( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Transpose of a 4x4 matrix
 */
static inline void vmathM4Transpose( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Compute the inverse of a 4x4 matrix
 * NOTE: 
 * Result is unpredictable when the determinant of mat is equal to or near 0.
 */
static inline void vmathM4Inverse( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Compute the inverse of a 4x4 matrix, which is expected to be an affine matrix
 * NOTE: 
 * This can be used to achieve better performance than a general inverse when the specified 4x4 matrix meets the given restrictions.  The result is unpredictable when the determinant of mat is equal to or near 0.
 */
static inline void vmathM4AffineInverse( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Compute the inverse of a 4x4 matrix, which is expected to be an affine matrix with an orthogonal upper-left 3x3 submatrix
 * NOTE: 
 * This can be used to achieve better performance than a general inverse when the specified 4x4 matrix meets the given restrictions.
 */
static inline void vmathM4OrthoInverse( VmathMatrix4 *result, const VmathMatrix4 *mat );

/*
 * Determinant of a 4x4 matrix
 */
static inline float vmathM4Determinant( const VmathMatrix4 *mat );

/*
 * Conditionally select between two 4x4 matrices
 */
static inline void vmathM4Select( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 4x4 matrix
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM4Print( const VmathMatrix4 *mat );

/*
 * Print a 4x4 matrix and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathM4Prints( const VmathMatrix4 *mat, const char *name );

#endif

/*
 * Copy a 3x4 transformation matrix
 */
static inline void vmathT3Copy( VmathTransform3 *result, const VmathTransform3 *tfrm );

/*
 * Construct a 3x4 transformation matrix containing the specified columns
 */
static inline void vmathT3MakeFromCols( VmathTransform3 *result, const VmathVector3 *col0, const VmathVector3 *col1, const VmathVector3 *col2, const VmathVector3 *col3 );

/*
 * Construct a 3x4 transformation matrix from a 3x3 matrix and a 3-D vector
 */
static inline void vmathT3MakeFromM3V3( VmathTransform3 *result, const VmathMatrix3 *tfrm, const VmathVector3 *translateVec );

/*
 * Construct a 3x4 transformation matrix from a unit-length quaternion and a 3-D vector
 */
static inline void vmathT3MakeFromQV3( VmathTransform3 *result, const VmathQuat *unitQuat, const VmathVector3 *translateVec );

/*
 * Set all elements of a 3x4 transformation matrix to the same scalar value
 */
static inline void vmathT3MakeFromScalar( VmathTransform3 *result, float scalar );

/*
 * Set the upper-left 3x3 submatrix
 */
static inline void vmathT3SetUpper3x3( VmathTransform3 *result, const VmathMatrix3 *mat3 );

/*
 * Get the upper-left 3x3 submatrix of a 3x4 transformation matrix
 */
static inline void vmathT3GetUpper3x3( VmathMatrix3 *result, const VmathTransform3 *tfrm );

/*
 * Set translation component
 */
static inline void vmathT3SetTranslation( VmathTransform3 *result, const VmathVector3 *translateVec );

/*
 * Get the translation component of a 3x4 transformation matrix
 */
static inline void vmathT3GetTranslation( VmathVector3 *result, const VmathTransform3 *tfrm );

/*
 * Set column 0 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol0( VmathTransform3 *result, const VmathVector3 *col0 );

/*
 * Set column 1 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol1( VmathTransform3 *result, const VmathVector3 *col1 );

/*
 * Set column 2 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol2( VmathTransform3 *result, const VmathVector3 *col2 );

/*
 * Set column 3 of a 3x4 transformation matrix
 */
static inline void vmathT3SetCol3( VmathTransform3 *result, const VmathVector3 *col3 );

/*
 * Get column 0 of a 3x4 transformation matrix
 */
static inline void vmathT3GetCol0( VmathVector3 *result, const VmathTransform3 *tfrm );

/*
 * Get column 1 of a 3x4 transformation matrix
 */
static inline void vmathT3GetCol1( VmathVector3 *result, const VmathTransform3 *tfrm );

/*
 * Get column 2 of a 3x4 transformation matrix
 */
static inline void vmathT3GetCol2( VmathVector3 *result, const VmathTransform3 *tfrm );

/*
 * Get column 3 of a 3x4 transformation matrix
 */
static inline void vmathT3GetCol3( VmathVector3 *result, const VmathTransform3 *tfrm );

/*
 * Set the column of a 3x4 transformation matrix referred to by the specified index
 */
static inline void vmathT3SetCol( VmathTransform3 *result, int col, const VmathVector3 *vec );

/*
 * Set the row of a 3x4 transformation matrix referred to by the specified index
 */
static inline void vmathT3SetRow( VmathTransform3 *result, int row, const VmathVector4 *vec );

/*
 * Get the column of a 3x4 transformation matrix referred to by the specified index
 */
static inline void vmathT3GetCol( VmathVector3 *result, const VmathTransform3 *tfrm, int col );

/*
 * Get the row of a 3x4 transformation matrix referred to by the specified index
 */
static inline void vmathT3GetRow( VmathVector4 *result, const VmathTransform3 *tfrm, int row );

/*
 * Set the element of a 3x4 transformation matrix referred to by column and row indices
 */
static inline void vmathT3SetElem( VmathTransform3 *result, int col, int row, float val );

/*
 * Get the element of a 3x4 transformation matrix referred to by column and row indices
 */
static inline float vmathT3GetElem( const VmathTransform3 *tfrm, int col, int row );

/*
 * Multiply a 3x4 transformation matrix by a 3-D vector
 */
static inline void vmathT3MulV3( VmathVector3 *result, const VmathTransform3 *tfrm, const VmathVector3 *vec );

/*
 * Multiply a 3x4 transformation matrix by a 3-D point
 */
static inline void vmathT3MulP3( VmathPoint3 *result, const VmathTransform3 *tfrm, const VmathPoint3 *pnt );

/*
 * Multiply two 3x4 transformation matrices
 */
static inline void vmathT3Mul( VmathTransform3 *result, const VmathTransform3 *tfrm0, const VmathTransform3 *tfrm1 );

/*
 * Construct an identity 3x4 transformation matrix
 */
static inline void vmathT3MakeIdentity( VmathTransform3 *result );

/*
 * Construct a 3x4 transformation matrix to rotate around the x axis
 */
static inline void vmathT3MakeRotationX( VmathTransform3 *result, float radians );

/*
 * Construct a 3x4 transformation matrix to rotate around the y axis
 */
static inline void vmathT3MakeRotationY( VmathTransform3 *result, float radians );

/*
 * Construct a 3x4 transformation matrix to rotate around the z axis
 */
static inline void vmathT3MakeRotationZ( VmathTransform3 *result, float radians );

/*
 * Construct a 3x4 transformation matrix to rotate around the x, y, and z axes
 */
static inline void vmathT3MakeRotationZYX( VmathTransform3 *result, const VmathVector3 *radiansXYZ );

/*
 * Construct a 3x4 transformation matrix to rotate around a unit-length 3-D vector
 */
static inline void vmathT3MakeRotationAxis( VmathTransform3 *result, float radians, const VmathVector3 *unitVec );

/*
 * Construct a rotation matrix from a unit-length quaternion
 */
static inline void vmathT3MakeRotationQ( VmathTransform3 *result, const VmathQuat *unitQuat );

/*
 * Construct a 3x4 transformation matrix to perform scaling
 */
static inline void vmathT3MakeScale( VmathTransform3 *result, const VmathVector3 *scaleVec );

/*
 * Construct a 3x4 transformation matrix to perform translation
 */
static inline void vmathT3MakeTranslation( VmathTransform3 *result, const VmathVector3 *translateVec );

/*
 * Append (post-multiply) a scale transformation to a 3x4 transformation matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline void vmathT3AppendScale( VmathTransform3 *result, const VmathTransform3 *tfrm, const VmathVector3 *scaleVec );

/*
 * Prepend (pre-multiply) a scale transformation to a 3x4 transformation matrix
 * NOTE: 
 * Faster than creating and multiplying a scale transformation matrix.
 */
static inline void vmathT3PrependScale( VmathTransform3 *result, const VmathVector3 *scaleVec, const VmathTransform3 *tfrm );

/*
 * Multiply two 3x4 transformation matrices per element
 */
static inline void vmathT3MulPerElem( VmathTransform3 *result, const VmathTransform3 *tfrm0, const VmathTransform3 *tfrm1 );

/*
 * Compute the absolute value of a 3x4 transformation matrix per element
 */
static inline void vmathT3AbsPerElem( VmathTransform3 *result, const VmathTransform3 *tfrm );

/*
 * Inverse of a 3x4 transformation matrix
 * NOTE: 
 * Result is unpredictable when the determinant of the left 3x3 submatrix is equal to or near 0.
 */
static inline void vmathT3Inverse( VmathTransform3 *result, const VmathTransform3 *tfrm );

/*
 * Compute the inverse of a 3x4 transformation matrix, expected to have an orthogonal upper-left 3x3 submatrix
 * NOTE: 
 * This can be used to achieve better performance than a general inverse when the specified 3x4 transformation matrix meets the given restrictions.
 */
static inline void vmathT3OrthoInverse( VmathTransform3 *result, const VmathTransform3 *tfrm );

/*
 * Conditionally select between two 3x4 transformation matrices
 */
static inline void vmathT3Select( VmathTransform3 *result, const VmathTransform3 *tfrm0, const VmathTransform3 *tfrm1, unsigned int select1 );

#ifdef _VECTORMATH_DEBUG

/*
 * Print a 3x4 transformation matrix
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathT3Print( const VmathTransform3 *tfrm );

/*
 * Print a 3x4 transformation matrix and an associated string identifier
 * NOTE: 
 * Function is only defined when _VECTORMATH_DEBUG is defined.
 */
static inline void vmathT3Prints( const VmathTransform3 *tfrm, const char *name );

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_VEC_AOS_C_H
#define _VECTORMATH_VEC_AOS_C_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
 * Constants
 */
#define _VECTORMATH_SLERP_TOL 0.999f

/*-----------------------------------------------------------------------------
 * Definitions
 */
#ifndef _VECTORMATH_INTERNAL_FUNCTIONS
#define _VECTORMATH_INTERNAL_FUNCTIONS

#endif

static inline void vmathV3Copy( VmathVector3 *result, const VmathVector3 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
}

static inline void vmathV3MakeFromElems( VmathVector3 *result, float _x, float _y, float _z )
{
    result->x = _x;
    result->y = _y;
    result->z = _z;
}

static inline void vmathV3MakeFromP3( VmathVector3 *result, const VmathPoint3 *pnt )
{
    result->x = pnt->x;
    result->y = pnt->y;
    result->z = pnt->z;
}

static inline void vmathV3MakeFromScalar( VmathVector3 *result, float scalar )
{
    result->x = scalar;
    result->y = scalar;
    result->z = scalar;
}

static inline void vmathV3MakeXAxis( VmathVector3 *result )
{
    vmathV3MakeFromElems( result, 1.0f, 0.0f, 0.0f );
}

static inline void vmathV3MakeYAxis( VmathVector3 *result )
{
    vmathV3MakeFromElems( result, 0.0f, 1.0f, 0.0f );
}

static inline void vmathV3MakeZAxis( VmathVector3 *result )
{
    vmathV3MakeFromElems( result, 0.0f, 0.0f, 1.0f );
}

static inline void vmathV3Lerp( VmathVector3 *result, float t, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    VmathVector3 tmpV3_0, tmpV3_1;
    vmathV3Sub( &tmpV3_0, vec1, vec0 );
    vmathV3ScalarMul( &tmpV3_1, &tmpV3_0, t );
    vmathV3Add( result, vec0, &tmpV3_1 );
}

static inline void vmathV3Slerp( VmathVector3 *result, float t, const VmathVector3 *unitVec0, const VmathVector3 *unitVec1 )
{
    VmathVector3 tmpV3_0, tmpV3_1;
    float recipSinAngle, scale0, scale1, cosAngle, angle;
    cosAngle = vmathV3Dot( unitVec0, unitVec1 );
    if ( cosAngle < _VECTORMATH_SLERP_TOL ) {
        angle = acosf( cosAngle );
        recipSinAngle = ( 1.0f / sinf( angle ) );
        scale0 = ( sinf( ( ( 1.0f - t ) * angle ) ) * recipSinAngle );
        scale1 = ( sinf( ( t * angle ) ) * recipSinAngle );
    } else {
        scale0 = ( 1.0f - t );
        scale1 = t;
    }
    vmathV3ScalarMul( &tmpV3_0, unitVec0, scale0 );
    vmathV3ScalarMul( &tmpV3_1, unitVec1, scale1 );
    vmathV3Add( result, &tmpV3_0, &tmpV3_1 );
}

static inline void vmathV3SetX( VmathVector3 *result, float _x )
{
    result->x = _x;
}

static inline float vmathV3GetX( const VmathVector3 *vec )
{
    return vec->x;
}

static inline void vmathV3SetY( VmathVector3 *result, float _y )
{
    result->y = _y;
}

static inline float vmathV3GetY( const VmathVector3 *vec )
{
    return vec->y;
}

static inline void vmathV3SetZ( VmathVector3 *result, float _z )
{
    result->z = _z;
}

static inline float vmathV3GetZ( const VmathVector3 *vec )
{
    return vec->z;
}

static inline void vmathV3SetElem( VmathVector3 *result, int idx, float value )
{
    *(&result->x + idx) = value;
}

static inline float vmathV3GetElem( const VmathVector3 *vec, int idx )
{
    return *(&vec->x + idx);
}

static inline void vmathV3Add( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = ( vec0->x + vec1->x );
    result->y = ( vec0->y + vec1->y );
    result->z = ( vec0->z + vec1->z );
}

static inline void vmathV3Sub( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = ( vec0->x - vec1->x );
    result->y = ( vec0->y - vec1->y );
    result->z = ( vec0->z - vec1->z );
}

static inline void vmathV3AddP3( VmathPoint3 *result, const VmathVector3 *vec, const VmathPoint3 *pnt1 )
{
    result->x = ( vec->x + pnt1->x );
    result->y = ( vec->y + pnt1->y );
    result->z = ( vec->z + pnt1->z );
}

static inline void vmathV3ScalarMul( VmathVector3 *result, const VmathVector3 *vec, float scalar )
{
    result->x = ( vec->x * scalar );
    result->y = ( vec->y * scalar );
    result->z = ( vec->z * scalar );
}

static inline void vmathV3ScalarDiv( VmathVector3 *result, const VmathVector3 *vec, float scalar )
{
    result->x = ( vec->x / scalar );
    result->y = ( vec->y / scalar );
    result->z = ( vec->z / scalar );
}

static inline void vmathV3Neg( VmathVector3 *result, const VmathVector3 *vec )
{
    result->x = -vec->x;
    result->y = -vec->y;
    result->z = -vec->z;
}

static inline void vmathV3MulPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = ( vec0->x * vec1->x );
    result->y = ( vec0->y * vec1->y );
    result->z = ( vec0->z * vec1->z );
}

static inline void vmathV3DivPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = ( vec0->x / vec1->x );
    result->y = ( vec0->y / vec1->y );
    result->z = ( vec0->z / vec1->z );
}

static inline void vmathV3RecipPerElem( VmathVector3 *result, const VmathVector3 *vec )
{
    result->x = ( 1.0f / vec->x );
    result->y = ( 1.0f / vec->y );
    result->z = ( 1.0f / vec->z );
}

static inline void vmathV3SqrtPerElem( VmathVector3 *result, const VmathVector3 *vec )
{
    result->x = sqrtf( vec->x );
    result->y = sqrtf( vec->y );
    result->z = sqrtf( vec->z );
}

static inline void vmathV3RsqrtPerElem( VmathVector3 *result, const VmathVector3 *vec )
{
    result->x = ( 1.0f / sqrtf( vec->x ) );
    result->y = ( 1.0f / sqrtf( vec->y ) );
    result->z = ( 1.0f / sqrtf( vec->z ) );
}

static inline void vmathV3AbsPerElem( VmathVector3 *result, const VmathVector3 *vec )
{
    result->x = fabsf( vec->x );
    result->y = fabsf( vec->y );
    result->z = fabsf( vec->z );
}

static inline void vmathV3CopySignPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = ( vec1->x < 0.0f )? -fabsf( vec0->x ) : fabsf( vec0->x );
    result->y = ( vec1->y < 0.0f )? -fabsf( vec0->y ) : fabsf( vec0->y );
    result->z = ( vec1->z < 0.0f )? -fabsf( vec0->z ) : fabsf( vec0->z );
}

static inline void vmathV3MaxPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = (vec0->x > vec1->x)? vec0->x : vec1->x;
    result->y = (vec0->y > vec1->y)? vec0->y : vec1->y;
    result->z = (vec0->z > vec1->z)? vec0->z : vec1->z;
}

static inline float vmathV3MaxElem( const VmathVector3 *vec )
{
    float result;
    result = (vec->x > vec->y)? vec->x : vec->y;
    result = (vec->z > result)? vec->z : result;
    return result;
}

static inline void vmathV3MinPerElem( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    result->x = (vec0->x < vec1->x)? vec0->x : vec1->x;
    result->y = (vec0->y < vec1->y)? vec0->y : vec1->y;
    result->z = (vec0->z < vec1->z)? vec0->z : vec1->z;
}

static inline float vmathV3MinElem( const VmathVector3 *vec )
{
    float result;
    result = (vec->x < vec->y)? vec->x : vec->y;
    result = (vec->z < result)? vec->z : result;
    return result;
}

static inline float vmathV3Sum( const VmathVector3 *vec )
{
    float result;
    result = ( vec->x + vec->y );
    result = ( result + vec->z );
    return result;
}

static inline float vmathV3Dot( const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    float result;
    result = ( vec0->x * vec1->x );
    result = ( result + ( vec0->y * vec1->y ) );
    result = ( result + ( vec0->z * vec1->z ) );
    return result;
}

static inline float vmathV3LengthSqr( const VmathVector3 *vec )
{
    float result;
    result = ( vec->x * vec->x );
    result = ( result + ( vec->y * vec->y ) );
    result = ( result + ( vec->z * vec->z ) );
    return result;
}

static inline float vmathV3Length( const VmathVector3 *vec )
{
    return sqrtf( vmathV3LengthSqr( vec ) );
}

static inline void vmathV3Normalize( VmathVector3 *result, const VmathVector3 *vec )
{
    float lenSqr, lenInv;
    lenSqr = vmathV3LengthSqr( vec );
    lenInv = ( 1.0f / sqrtf( lenSqr ) );
    result->x = ( vec->x * lenInv );
    result->y = ( vec->y * lenInv );
    result->z = ( vec->z * lenInv );
}

static inline void vmathV3Cross( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1 )
{
    float tmpX, tmpY, tmpZ;
    tmpX = ( ( vec0->y * vec1->z ) - ( vec0->z * vec1->y ) );
    tmpY = ( ( vec0->z * vec1->x ) - ( vec0->x * vec1->z ) );
    tmpZ = ( ( vec0->x * vec1->y ) - ( vec0->y * vec1->x ) );
    vmathV3MakeFromElems( result, tmpX, tmpY, tmpZ );
}

static inline void vmathV3Select( VmathVector3 *result, const VmathVector3 *vec0, const VmathVector3 *vec1, unsigned int select1 )
{
    result->x = ( select1 )? vec1->x : vec0->x;
    result->y = ( select1 )? vec1->y : vec0->y;
    result->z = ( select1 )? vec1->z : vec0->z;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathV3Print( const VmathVector3 *vec )
{
    printf( "( %f %f %f )\n", vec->x, vec->y, vec->z );
}

static inline void vmathV3Prints( const VmathVector3 *vec, const char *name )
{
    printf( "%s: ( %f %f %f )\n", name, vec->x, vec->y, vec->z );
}

#endif

static inline void vmathV4Copy( VmathVector4 *result, const VmathVector4 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
    result->w = vec->w;
}

static inline void vmathV4MakeFromElems( VmathVector4 *result, float _x, float _y, float _z, float _w )
{
    result->x = _x;
    result->y = _y;
    result->z = _z;
    result->w = _w;
}

static inline void vmathV4MakeFromV3Scalar( VmathVector4 *result, const VmathVector3 *xyz, float _w )
{
    vmathV4SetXYZ( result, xyz );
    vmathV4SetW( result, _w );
}

static inline void vmathV4MakeFromV3( VmathVector4 *result, const VmathVector3 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
    result->w = 0.0f;
}

static inline void vmathV4MakeFromP3( VmathVector4 *result, const VmathPoint3 *pnt )
{
    result->x = pnt->x;
    result->y = pnt->y;
    result->z = pnt->z;
    result->w = 1.0f;
}

static inline void vmathV4MakeFromQ( VmathVector4 *result, const VmathQuat *quat )
{
    result->x = quat->x;
    result->y = quat->y;
    result->z = quat->z;
    result->w = quat->w;
}

static inline void vmathV4MakeFromScalar( VmathVector4 *result, float scalar )
{
    result->x = scalar;
    result->y = scalar;
    result->z = scalar;
    result->w = scalar;
}

static inline void vmathV4MakeXAxis( VmathVector4 *result )
{
    vmathV4MakeFromElems( result, 1.0f, 0.0f, 0.0f, 0.0f );
}

static inline void vmathV4MakeYAxis( VmathVector4 *result )
{
    vmathV4MakeFromElems( result, 0.0f, 1.0f, 0.0f, 0.0f );
}

static inline void vmathV4MakeZAxis( VmathVector4 *result )
{
    vmathV4MakeFromElems( result, 0.0f, 0.0f, 1.0f, 0.0f );
}

static inline void vmathV4MakeWAxis( VmathVector4 *result )
{
    vmathV4MakeFromElems( result, 0.0f, 0.0f, 0.0f, 1.0f );
}

static inline void vmathV4Lerp( VmathVector4 *result, float t, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    VmathVector4 tmpV4_0, tmpV4_1;
    vmathV4Sub( &tmpV4_0, vec1, vec0 );
    vmathV4ScalarMul( &tmpV4_1, &tmpV4_0, t );
    vmathV4Add( result, vec0, &tmpV4_1 );
}

static inline void vmathV4Slerp( VmathVector4 *result, float t, const VmathVector4 *unitVec0, const VmathVector4 *unitVec1 )
{
    VmathVector4 tmpV4_0, tmpV4_1;
    float recipSinAngle, scale0, scale1, cosAngle, angle;
    cosAngle = vmathV4Dot( unitVec0, unitVec1 );
    if ( cosAngle < _VECTORMATH_SLERP_TOL ) {
        angle = acosf( cosAngle );
        recipSinAngle = ( 1.0f / sinf( angle ) );
        scale0 = ( sinf( ( ( 1.0f - t ) * angle ) ) * recipSinAngle );
        scale1 = ( sinf( ( t * angle ) ) * recipSinAngle );
    } else {
        scale0 = ( 1.0f - t );
        scale1 = t;
    }
    vmathV4ScalarMul( &tmpV4_0, unitVec0, scale0 );
    vmathV4ScalarMul( &tmpV4_1, unitVec1, scale1 );
    vmathV4Add( result, &tmpV4_0, &tmpV4_1 );
}

static inline void vmathV4SetXYZ( VmathVector4 *result, const VmathVector3 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
}

static inline void vmathV4GetXYZ( VmathVector3 *result, const VmathVector4 *vec )
{
    vmathV3MakeFromElems( result, vec->x, vec->y, vec->z );
}

static inline void vmathV4SetX( VmathVector4 *result, float _x )
{
    result->x = _x;
}

static inline float vmathV4GetX( const VmathVector4 *vec )
{
    return vec->x;
}

static inline void vmathV4SetY( VmathVector4 *result, float _y )
{
    result->y = _y;
}

static inline float vmathV4GetY( const VmathVector4 *vec )
{
    return vec->y;
}

static inline void vmathV4SetZ( VmathVector4 *result, float _z )
{
    result->z = _z;
}

static inline float vmathV4GetZ( const VmathVector4 *vec )
{
    return vec->z;
}

static inline void vmathV4SetW( VmathVector4 *result, float _w )
{
    result->w = _w;
}

static inline float vmathV4GetW( const VmathVector4 *vec )
{
    return vec->w;
}

static inline void vmathV4SetElem( VmathVector4 *result, int idx, float value )
{
    *(&result->x + idx) = value;
}

static inline float vmathV4GetElem( const VmathVector4 *vec, int idx )
{
    return *(&vec->x + idx);
}

static inline void vmathV4Add( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = ( vec0->x + vec1->x );
    result->y = ( vec0->y + vec1->y );
    result->z = ( vec0->z + vec1->z );
    result->w = ( vec0->w + vec1->w );
}

static inline void vmathV4Sub( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = ( vec0->x - vec1->x );
    result->y = ( vec0->y - vec1->y );
    result->z = ( vec0->z - vec1->z );
    result->w = ( vec0->w - vec1->w );
}

static inline void vmathV4ScalarMul( VmathVector4 *result, const VmathVector4 *vec, float scalar )
{
    result->x = ( vec->x * scalar );
    result->y = ( vec->y * scalar );
    result->z = ( vec->z * scalar );
    result->w = ( vec->w * scalar );
}

static inline void vmathV4ScalarDiv( VmathVector4 *result, const VmathVector4 *vec, float scalar )
{
    result->x = ( vec->x / scalar );
    result->y = ( vec->y / scalar );
    result->z = ( vec->z / scalar );
    result->w = ( vec->w / scalar );
}

static inline void vmathV4Neg( VmathVector4 *result, const VmathVector4 *vec )
{
    result->x = -vec->x;
    result->y = -vec->y;
    result->z = -vec->z;
    result->w = -vec->w;
}

static inline void vmathV4MulPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = ( vec0->x * vec1->x );
    result->y = ( vec0->y * vec1->y );
    result->z = ( vec0->z * vec1->z );
    result->w = ( vec0->w * vec1->w );
}

static inline void vmathV4DivPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = ( vec0->x / vec1->x );
    result->y = ( vec0->y / vec1->y );
    result->z = ( vec0->z / vec1->z );
    result->w = ( vec0->w / vec1->w );
}

static inline void vmathV4RecipPerElem( VmathVector4 *result, const VmathVector4 *vec )
{
    result->x = ( 1.0f / vec->x );
    result->y = ( 1.0f / vec->y );
    result->z = ( 1.0f / vec->z );
    result->w = ( 1.0f / vec->w );
}

static inline void vmathV4SqrtPerElem( VmathVector4 *result, const VmathVector4 *vec )
{
    result->x = sqrtf( vec->x );
    result->y = sqrtf( vec->y );
    result->z = sqrtf( vec->z );
    result->w = sqrtf( vec->w );
}

static inline void vmathV4RsqrtPerElem( VmathVector4 *result, const VmathVector4 *vec )
{
    result->x = ( 1.0f / sqrtf( vec->x ) );
    result->y = ( 1.0f / sqrtf( vec->y ) );
    result->z = ( 1.0f / sqrtf( vec->z ) );
    result->w = ( 1.0f / sqrtf( vec->w ) );
}

static inline void vmathV4AbsPerElem( VmathVector4 *result, const VmathVector4 *vec )
{
    result->x = fabsf( vec->x );
    result->y = fabsf( vec->y );
    result->z = fabsf( vec->z );
    result->w = fabsf( vec->w );
}

static inline void vmathV4CopySignPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = ( vec1->x < 0.0f )? -fabsf( vec0->x ) : fabsf( vec0->x );
    result->y = ( vec1->y < 0.0f )? -fabsf( vec0->y ) : fabsf( vec0->y );
    result->z = ( vec1->z < 0.0f )? -fabsf( vec0->z ) : fabsf( vec0->z );
    result->w = ( vec1->w < 0.0f )? -fabsf( vec0->w ) : fabsf( vec0->w );
}

static inline void vmathV4MaxPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = (vec0->x > vec1->x)? vec0->x : vec1->x;
    result->y = (vec0->y > vec1->y)? vec0->y : vec1->y;
    result->z = (vec0->z > vec1->z)? vec0->z : vec1->z;
    result->w = (vec0->w > vec1->w)? vec0->w : vec1->w;
}

static inline float vmathV4MaxElem( const VmathVector4 *vec )
{
    float result;
    result = (vec->x > vec->y)? vec->x : vec->y;
    result = (vec->z > result)? vec->z : result;
    result = (vec->w > result)? vec->w : result;
    return result;
}

static inline void vmathV4MinPerElem( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    result->x = (vec0->x < vec1->x)? vec0->x : vec1->x;
    result->y = (vec0->y < vec1->y)? vec0->y : vec1->y;
    result->z = (vec0->z < vec1->z)? vec0->z : vec1->z;
    result->w = (vec0->w < vec1->w)? vec0->w : vec1->w;
}

static inline float vmathV4MinElem( const VmathVector4 *vec )
{
    float result;
    result = (vec->x < vec->y)? vec->x : vec->y;
    result = (vec->z < result)? vec->z : result;
    result = (vec->w < result)? vec->w : result;
    return result;
}

static inline float vmathV4Sum( const VmathVector4 *vec )
{
    float result;
    result = ( vec->x + vec->y );
    result = ( result + vec->z );
    result = ( result + vec->w );
    return result;
}

static inline float vmathV4Dot( const VmathVector4 *vec0, const VmathVector4 *vec1 )
{
    float result;
    result = ( vec0->x * vec1->x );
    result = ( result + ( vec0->y * vec1->y ) );
    result = ( result + ( vec0->z * vec1->z ) );
    result = ( result + ( vec0->w * vec1->w ) );
    return result;
}

static inline float vmathV4LengthSqr( const VmathVector4 *vec )
{
    float result;
    result = ( vec->x * vec->x );
    result = ( result + ( vec->y * vec->y ) );
    result = ( result + ( vec->z * vec->z ) );
    result = ( result + ( vec->w * vec->w ) );
    return result;
}

static inline float vmathV4Length( const VmathVector4 *vec )
{
    return sqrtf( vmathV4LengthSqr( vec ) );
}

static inline void vmathV4Normalize( VmathVector4 *result, const VmathVector4 *vec )
{
    float lenSqr, lenInv;
    lenSqr = vmathV4LengthSqr( vec );
    lenInv = ( 1.0f / sqrtf( lenSqr ) );
    result->x = ( vec->x * lenInv );
    result->y = ( vec->y * lenInv );
    result->z = ( vec->z * lenInv );
    result->w = ( vec->w * lenInv );
}

static inline void vmathV4Select( VmathVector4 *result, const VmathVector4 *vec0, const VmathVector4 *vec1, unsigned int select1 )
{
    result->x = ( select1 )? vec1->x : vec0->x;
    result->y = ( select1 )? vec1->y : vec0->y;
    result->z = ( select1 )? vec1->z : vec0->z;
    result->w = ( select1 )? vec1->w : vec0->w;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathV4Print( const VmathVector4 *vec )
{
    printf( "( %f %f %f %f )\n", vec->x, vec->y, vec->z, vec->w );
}

static inline void vmathV4Prints( const VmathVector4 *vec, const char *name )
{
    printf( "%s: ( %f %f %f %f )\n", name, vec->x, vec->y, vec->z, vec->w );
}

#endif

static inline void vmathP3Copy( VmathPoint3 *result, const VmathPoint3 *pnt )
{
    result->x = pnt->x;
    result->y = pnt->y;
    result->z = pnt->z;
}

static inline void vmathP3MakeFromElems( VmathPoint3 *result, float _x, float _y, float _z )
{
    result->x = _x;
    result->y = _y;
    result->z = _z;
}

static inline void vmathP3MakeFromV3( VmathPoint3 *result, const VmathVector3 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
}

static inline void vmathP3MakeFromScalar( VmathPoint3 *result, float scalar )
{
    result->x = scalar;
    result->y = scalar;
    result->z = scalar;
}

static inline void vmathP3Lerp( VmathPoint3 *result, float t, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    VmathVector3 tmpV3_0, tmpV3_1;
    vmathP3Sub( &tmpV3_0, pnt1, pnt0 );
    vmathV3ScalarMul( &tmpV3_1, &tmpV3_0, t );
    vmathP3AddV3( result, pnt0, &tmpV3_1 );
}

static inline void vmathP3SetX( VmathPoint3 *result, float _x )
{
    result->x = _x;
}

static inline float vmathP3GetX( const VmathPoint3 *pnt )
{
    return pnt->x;
}

static inline void vmathP3SetY( VmathPoint3 *result, float _y )
{
    result->y = _y;
}

static inline float vmathP3GetY( const VmathPoint3 *pnt )
{
    return pnt->y;
}

static inline void vmathP3SetZ( VmathPoint3 *result, float _z )
{
    result->z = _z;
}

static inline float vmathP3GetZ( const VmathPoint3 *pnt )
{
    return pnt->z;
}

static inline void vmathP3SetElem( VmathPoint3 *result, int idx, float value )
{
    *(&result->x + idx) = value;
}

static inline float vmathP3GetElem( const VmathPoint3 *pnt, int idx )
{
    return *(&pnt->x + idx);
}

static inline void vmathP3Sub( VmathVector3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    result->x = ( pnt0->x - pnt1->x );
    result->y = ( pnt0->y - pnt1->y );
    result->z = ( pnt0->z - pnt1->z );
}

static inline void vmathP3AddV3( VmathPoint3 *result, const VmathPoint3 *pnt, const VmathVector3 *vec1 )
{
    result->x = ( pnt->x + vec1->x );
    result->y = ( pnt->y + vec1->y );
    result->z = ( pnt->z + vec1->z );
}

static inline void vmathP3SubV3( VmathPoint3 *result, const VmathPoint3 *pnt, const VmathVector3 *vec1 )
{
    result->x = ( pnt->x - vec1->x );
    result->y = ( pnt->y - vec1->y );
    result->z = ( pnt->z - vec1->z );
}

static inline void vmathP3MulPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    result->x = ( pnt0->x * pnt1->x );
    result->y = ( pnt0->y * pnt1->y );
    result->z = ( pnt0->z * pnt1->z );
}

static inline void vmathP3DivPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    result->x = ( pnt0->x / pnt1->x );
    result->y = ( pnt0->y / pnt1->y );
    result->z = ( pnt0->z / pnt1->z );
}

static inline void vmathP3RecipPerElem( VmathPoint3 *result, const VmathPoint3 *pnt )
{
    result->x = ( 1.0f / pnt->x );
    result->y = ( 1.0f / pnt->y );
    result->z = ( 1.0f / pnt->z );
}

static inline void vmathP3SqrtPerElem( VmathPoint3 *result, const VmathPoint3 *pnt )
{
    result->x = sqrtf( pnt->x );
    result->y = sqrtf( pnt->y );
    result->z = sqrtf( pnt->z );
}

static inline void vmathP3RsqrtPerElem( VmathPoint3 *result, const VmathPoint3 *pnt )
{
    result->x = ( 1.0f / sqrtf( pnt->x ) );
    result->y = ( 1.0f / sqrtf( pnt->y ) );
    result->z = ( 1.0f / sqrtf( pnt->z ) );
}

static inline void vmathP3AbsPerElem( VmathPoint3 *result, const VmathPoint3 *pnt )
{
    result->x = fabsf( pnt->x );
    result->y = fabsf( pnt->y );
    result->z = fabsf( pnt->z );
}

static inline void vmathP3CopySignPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    result->x = ( pnt1->x < 0.0f )? -fabsf( pnt0->x ) : fabsf( pnt0->x );
    result->y = ( pnt1->y < 0.0f )? -fabsf( pnt0->y ) : fabsf( pnt0->y );
    result->z = ( pnt1->z < 0.0f )? -fabsf( pnt0->z ) : fabsf( pnt0->z );
}

static inline void vmathP3MaxPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    result->x = (pnt0->x > pnt1->x)? pnt0->x : pnt1->x;
    result->y = (pnt0->y > pnt1->y)? pnt0->y : pnt1->y;
    result->z = (pnt0->z > pnt1->z)? pnt0->z : pnt1->z;
}

static inline float vmathP3MaxElem( const VmathPoint3 *pnt )
{
    float result;
    result = (pnt->x > pnt->y)? pnt->x : pnt->y;
    result = (pnt->z > result)? pnt->z : result;
    return result;
}

static inline void vmathP3MinPerElem( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    result->x = (pnt0->x < pnt1->x)? pnt0->x : pnt1->x;
    result->y = (pnt0->y < pnt1->y)? pnt0->y : pnt1->y;
    result->z = (pnt0->z < pnt1->z)? pnt0->z : pnt1->z;
}

static inline float vmathP3MinElem( const VmathPoint3 *pnt )
{
    float result;
    result = (pnt->x < pnt->y)? pnt->x : pnt->y;
    result = (pnt->z < result)? pnt->z : result;
    return result;
}

static inline float vmathP3Sum( const VmathPoint3 *pnt )
{
    float result;
    result = ( pnt->x + pnt->y );
    result = ( result + pnt->z );
    return result;
}

static inline void vmathP3Scale( VmathPoint3 *result, const VmathPoint3 *pnt, float scaleVal )
{
    VmathPoint3 tmpP3_0;
    vmathP3MakeFromScalar( &tmpP3_0, scaleVal );
    vmathP3MulPerElem( result, pnt, &tmpP3_0 );
}

static inline void vmathP3NonUniformScale( VmathPoint3 *result, const VmathPoint3 *pnt, const VmathVector3 *scaleVec )
{
    VmathPoint3 tmpP3_0;
    vmathP3MakeFromV3( &tmpP3_0, scaleVec );
    vmathP3MulPerElem( result, pnt, &tmpP3_0 );
}

static inline float vmathP3Projection( const VmathPoint3 *pnt, const VmathVector3 *unitVec )
{
    float result;
    result = ( pnt->x * unitVec->x );
    result = ( result + ( pnt->y * unitVec->y ) );
    result = ( result + ( pnt->z * unitVec->z ) );
    return result;
}

static inline float vmathP3DistSqrFromOrigin( const VmathPoint3 *pnt )
{
    VmathVector3 tmpV3_0;
    vmathV3MakeFromP3( &tmpV3_0, pnt );
    return vmathV3LengthSqr( &tmpV3_0 );
}

static inline float vmathP3DistFromOrigin( const VmathPoint3 *pnt )
{
    VmathVector3 tmpV3_0;
    vmathV3MakeFromP3( &tmpV3_0, pnt );
    return vmathV3Length( &tmpV3_0 );
}

static inline float vmathP3DistSqr( const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    VmathVector3 tmpV3_0;
    vmathP3Sub( &tmpV3_0, pnt1, pnt0 );
    return vmathV3LengthSqr( &tmpV3_0 );
}

static inline float vmathP3Dist( const VmathPoint3 *pnt0, const VmathPoint3 *pnt1 )
{
    VmathVector3 tmpV3_0;
    vmathP3Sub( &tmpV3_0, pnt1, pnt0 );
    return vmathV3Length( &tmpV3_0 );
}

static inline void vmathP3Select( VmathPoint3 *result, const VmathPoint3 *pnt0, const VmathPoint3 *pnt1, unsigned int select1 )
{
    result->x = ( select1 )? pnt1->x : pnt0->x;
    result->y = ( select1 )? pnt1->y : pnt0->y;
    result->z = ( select1 )? pnt1->z : pnt0->z;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathP3Print( const VmathPoint3 *pnt )
{
    printf( "( %f %f %f )\n", pnt->x, pnt->y, pnt->z );
}

static inline void vmathP3Prints( const VmathPoint3 *pnt, const char *name )
{
    printf( "%s: ( %f %f %f )\n", name, pnt->x, pnt->y, pnt->z );
}

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_QUAT_AOS_C_H
#define _VECTORMATH_QUAT_AOS_C_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
 * Definitions
 */
#ifndef _VECTORMATH_INTERNAL_FUNCTIONS
#define _VECTORMATH_INTERNAL_FUNCTIONS

#endif

static inline void vmathQCopy( VmathQuat *result, const VmathQuat *quat )
{
    result->x = quat->x;
    result->y = quat->y;
    result->z = quat->z;
    result->w = quat->w;
}

static inline void vmathQMakeFromElems( VmathQuat *result, float _x, float _y, float _z, float _w )
{
    result->x = _x;
    result->y = _y;
    result->z = _z;
    result->w = _w;
}

static inline void vmathQMakeFromV3Scalar( VmathQuat *result, const VmathVector3 *xyz, float _w )
{
    vmathQSetXYZ( result, xyz );
    vmathQSetW( result, _w );
}

static inline void vmathQMakeFromV4( VmathQuat *result, const VmathVector4 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
    result->w = vec->w;
}

static inline void vmathQMakeFromScalar( VmathQuat *result, float scalar )
{
    result->x = scalar;
    result->y = scalar;
    result->z = scalar;
    result->w = scalar;
}

static inline void vmathQMakeIdentity( VmathQuat *result )
{
    vmathQMakeFromElems( result, 0.0f, 0.0f, 0.0f, 1.0f );
}

static inline void vmathQLerp( VmathQuat *result, float t, const VmathQuat *quat0, const VmathQuat *quat1 )
{
    VmathQuat tmpQ_0, tmpQ_1;
    vmathQSub( &tmpQ_0, quat1, quat0 );
    vmathQScalarMul( &tmpQ_1, &tmpQ_0, t );
    vmathQAdd( result, quat0, &tmpQ_1 );
}

static inline void vmathQSlerp( VmathQuat *result, float t, const VmathQuat *unitQuat0, const VmathQuat *unitQuat1 )
{
    VmathQuat start, tmpQ_0, tmpQ_1;
    float recipSinAngle, scale0, scale1, cosAngle, angle;
    cosAngle = vmathQDot( unitQuat0, unitQuat1 );
    if ( cosAngle < 0.0f ) {
        cosAngle = -cosAngle;
        vmathQNeg( &start, unitQuat0 );
    } else {
        vmathQCopy( &start, unitQuat0 );
    }
    if ( cosAngle < _VECTORMATH_SLERP_TOL ) {
        angle = acosf( cosAngle );
        recipSinAngle = ( 1.0f / sinf( angle ) );
        scale0 = ( sinf( ( ( 1.0f - t ) * angle ) ) * recipSinAngle );
        scale1 = ( sinf( ( t * angle ) ) * recipSinAngle );
    } else {
        scale0 = ( 1.0f - t );
        scale1 = t;
    }
    vmathQScalarMul( &tmpQ_0, &start, scale0 );
    vmathQScalarMul( &tmpQ_1, unitQuat1, scale1 );
    vmathQAdd( result, &tmpQ_0, &tmpQ_1 );
}

static inline void vmathQSquad( VmathQuat *result, float t, const VmathQuat *unitQuat0, const VmathQuat *unitQuat1, const VmathQuat *unitQuat2, const VmathQuat *unitQuat3 )
{
    VmathQuat tmp0, tmp1;
    vmathQSlerp( &tmp0, t, unitQuat0, unitQuat3 );
    vmathQSlerp( &tmp1, t, unitQuat1, unitQuat2 );
    vmathQSlerp( result, ( ( 2.0f * t ) * ( 1.0f - t ) ), &tmp0, &tmp1 );
}

static inline void vmathQSetXYZ( VmathQuat *result, const VmathVector3 *vec )
{
    result->x = vec->x;
    result->y = vec->y;
    result->z = vec->z;
}

static inline void vmathQGetXYZ( VmathVector3 *result, const VmathQuat *quat )
{
    vmathV3MakeFromElems( result, quat->x, quat->y, quat->z );
}

static inline void vmathQSetX( VmathQuat *result, float _x )
{
    result->x = _x;
}

static inline float vmathQGetX( const VmathQuat *quat )
{
    return quat->x;
}

static inline void vmathQSetY( VmathQuat *result, float _y )
{
    result->y = _y;
}

static inline float vmathQGetY( const VmathQuat *quat )
{
    return quat->y;
}

static inline void vmathQSetZ( VmathQuat *result, float _z )
{
    result->z = _z;
}

static inline float vmathQGetZ( const VmathQuat *quat )
{
    return quat->z;
}

static inline void vmathQSetW( VmathQuat *result, float _w )
{
    result->w = _w;
}

static inline float vmathQGetW( const VmathQuat *quat )
{
    return quat->w;
}

static inline void vmathQSetElem( VmathQuat *result, int idx, float value )
{
    *(&result->x + idx) = value;
}

static inline float vmathQGetElem( const VmathQuat *quat, int idx )
{
    return *(&quat->x + idx);
}

static inline void vmathQAdd( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1 )
{
    result->x = ( quat0->x + quat1->x );
    result->y = ( quat0->y + quat1->y );
    result->z = ( quat0->z + quat1->z );
    result->w = ( quat0->w + quat1->w );
}

static inline void vmathQSub( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1 )
{
    result->x = ( quat0->x - quat1->x );
    result->y = ( quat0->y - quat1->y );
    result->z = ( quat0->z - quat1->z );
    result->w = ( quat0->w - quat1->w );
}

static inline void vmathQScalarMul( VmathQuat *result, const VmathQuat *quat, float scalar )
{
    result->x = ( quat->x * scalar );
    result->y = ( quat->y * scalar );
    result->z = ( quat->z * scalar );
    result->w = ( quat->w * scalar );
}

static inline void vmathQScalarDiv( VmathQuat *result, const VmathQuat *quat, float scalar )
{
    result->x = ( quat->x / scalar );
    result->y = ( quat->y / scalar );
    result->z = ( quat->z / scalar );
    result->w = ( quat->w / scalar );
}

static inline void vmathQNeg( VmathQuat *result, const VmathQuat *quat )
{
    result->x = -quat->x;
    result->y = -quat->y;
    result->z = -quat->z;
    result->w = -quat->w;
}

static inline float vmathQDot( const VmathQuat *quat0, const VmathQuat *quat1 )
{
    float result;
    result = ( quat0->x * quat1->x );
    result = ( result + ( quat0->y * quat1->y ) );
    result = ( result + ( quat0->z * quat1->z ) );
    result = ( result + ( quat0->w * quat1->w ) );
    return result;
}

static inline float vmathQNorm( const VmathQuat *quat )
{
    float result;
    result = ( quat->x * quat->x );
    result = ( result + ( quat->y * quat->y ) );
    result = ( result + ( quat->z * quat->z ) );
    result = ( result + ( quat->w * quat->w ) );
    return result;
}

static inline float vmathQLength( const VmathQuat *quat )
{
    return sqrtf( vmathQNorm( quat ) );
}

static inline void vmathQNormalize( VmathQuat *result, const VmathQuat *quat )
{
    float lenSqr, lenInv;
    lenSqr = vmathQNorm( quat );
    lenInv = ( 1.0f / sqrtf( lenSqr ) );
    result->x = ( quat->x * lenInv );
    result->y = ( quat->y * lenInv );
    result->z = ( quat->z * lenInv );
    result->w = ( quat->w * lenInv );
}

static inline void vmathQMakeRotationArc( VmathQuat *result, const VmathVector3 *unitVec0, const VmathVector3 *unitVec1 )
{
    VmathVector3 tmpV3_0, tmpV3_1;
    float cosHalfAngleX2, recipCosHalfAngleX2;
    cosHalfAngleX2 = sqrtf( ( 2.0f * ( 1.0f + vmathV3Dot( unitVec0, unitVec1 ) ) ) );
    recipCosHalfAngleX2 = ( 1.0f / cosHalfAngleX2 );
    vmathV3Cross( &tmpV3_0, unitVec0, unitVec1 );
    vmathV3ScalarMul( &tmpV3_1, &tmpV3_0, recipCosHalfAngleX2 );
    vmathQMakeFromV3Scalar( result, &tmpV3_1, ( cosHalfAngleX2 * 0.5f ) );
}

static inline void vmathQMakeRotationAxis( VmathQuat *result, float radians, const VmathVector3 *unitVec )
{
    VmathVector3 tmpV3_0;
    float s, c, angle;
    angle = ( radians * 0.5f );
    s = sinf( angle );
    c = cosf( angle );
    vmathV3ScalarMul( &tmpV3_0, unitVec, s );
    vmathQMakeFromV3Scalar( result, &tmpV3_0, c );
}

static inline void vmathQMakeRotationX( VmathQuat *result, float radians )
{
    float s, c, angle;
    angle = ( radians * 0.5f );
    s = sinf( angle );
    c = cosf( angle );
    vmathQMakeFromElems( result, s, 0.0f, 0.0f, c );
}

static inline void vmathQMakeRotationY( VmathQuat *result, float radians )
{
    float s, c, angle;
    angle = ( radians * 0.5f );
    s = sinf( angle );
    c = cosf( angle );
    vmathQMakeFromElems( result, 0.0f, s, 0.0f, c );
}

static inline void vmathQMakeRotationZ( VmathQuat *result, float radians )
{
    float s, c, angle;
    angle = ( radians * 0.5f );
    s = sinf( angle );
    c = cosf( angle );
    vmathQMakeFromElems( result, 0.0f, 0.0f, s, c );
}

static inline void vmathQMul( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1 )
{
    float tmpX, tmpY, tmpZ, tmpW;
    tmpX = ( ( ( ( quat0->w * quat1->x ) + ( quat0->x * quat1->w ) ) + ( quat0->y * quat1->z ) ) - ( quat0->z * quat1->y ) );
    tmpY = ( ( ( ( quat0->w * quat1->y ) + ( quat0->y * quat1->w ) ) + ( quat0->z * quat1->x ) ) - ( quat0->x * quat1->z ) );
    tmpZ = ( ( ( ( quat0->w * quat1->z ) + ( quat0->z * quat1->w ) ) + ( quat0->x * quat1->y ) ) - ( quat0->y * quat1->x ) );
    tmpW = ( ( ( ( quat0->w * quat1->w ) - ( quat0->x * quat1->x ) ) - ( quat0->y * quat1->y ) ) - ( quat0->z * quat1->z ) );
    vmathQMakeFromElems( result, tmpX, tmpY, tmpZ, tmpW );
}

static inline void vmathQRotate( VmathVector3 *result, const VmathQuat *quat, const VmathVector3 *vec )
{
    float tmpX, tmpY, tmpZ, tmpW;
    tmpX = ( ( ( quat->w * vec->x ) + ( quat->y * vec->z ) ) - ( quat->z * vec->y ) );
    tmpY = ( ( ( quat->w * vec->y ) + ( quat->z * vec->x ) ) - ( quat->x * vec->z ) );
    tmpZ = ( ( ( quat->w * vec->z ) + ( quat->x * vec->y ) ) - ( quat->y * vec->x ) );
    tmpW = ( ( ( quat->x * vec->x ) + ( quat->y * vec->y ) ) + ( quat->z * vec->z ) );
    result->x = ( ( ( ( tmpW * quat->x ) + ( tmpX * quat->w ) ) - ( tmpY * quat->z ) ) + ( tmpZ * quat->y ) );
    result->y = ( ( ( ( tmpW * quat->y ) + ( tmpY * quat->w ) ) - ( tmpZ * quat->x ) ) + ( tmpX * quat->z ) );
    result->z = ( ( ( ( tmpW * quat->z ) + ( tmpZ * quat->w ) ) - ( tmpX * quat->y ) ) + ( tmpY * quat->x ) );
}

static inline void vmathQConj( VmathQuat *result, const VmathQuat *quat )
{
    vmathQMakeFromElems( result, -quat->x, -quat->y, -quat->z, quat->w );
}

static inline void vmathQSelect( VmathQuat *result, const VmathQuat *quat0, const VmathQuat *quat1, unsigned int select1 )
{
    result->x = ( select1 )? quat1->x : quat0->x;
    result->y = ( select1 )? quat1->y : quat0->y;
    result->z = ( select1 )? quat1->z : quat0->z;
    result->w = ( select1 )? quat1->w : quat0->w;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathQPrint( const VmathQuat *quat )
{
    printf( "( %f %f %f %f )\n", quat->x, quat->y, quat->z, quat->w );
}

static inline void vmathQPrints( const VmathQuat *quat, const char *name )
{
    printf( "%s: ( %f %f %f %f )\n", name, quat->x, quat->y, quat->z, quat->w );
}

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_MAT_AOS_C_H
#define _VECTORMATH_MAT_AOS_C_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
 * Constants
 */
#define _VECTORMATH_PI_OVER_2 1.570796327f

/*-----------------------------------------------------------------------------
 * Definitions
 */
static inline void vmathM3Copy( VmathMatrix3 *result, const VmathMatrix3 *mat )
{
    vmathV3Copy( &result->col0, &mat->col0 );
    vmathV3Copy( &result->col1, &mat->col1 );
    vmathV3Copy( &result->col2, &mat->col2 );
}

static inline void vmathM3MakeFromScalar( VmathMatrix3 *result, float scalar )
{
    vmathV3MakeFromScalar( &result->col0, scalar );
    vmathV3MakeFromScalar( &result->col1, scalar );
    vmathV3MakeFromScalar( &result->col2, scalar );
}

static inline void vmathM3MakeFromQ( VmathMatrix3 *result, const VmathQuat *unitQuat )
{
    float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
    qx = unitQuat->x;
    qy = unitQuat->y;
    qz = unitQuat->z;
    qw = unitQuat->w;
    qx2 = ( qx + qx );
    qy2 = ( qy + qy );
    qz2 = ( qz + qz );
    qxqx2 = ( qx * qx2 );
    qxqy2 = ( qx * qy2 );
    qxqz2 = ( qx * qz2 );
    qxqw2 = ( qw * qx2 );
    qyqy2 = ( qy * qy2 );
    qyqz2 = ( qy * qz2 );
    qyqw2 = ( qw * qy2 );
    qzqz2 = ( qz * qz2 );
    qzqw2 = ( qw * qz2 );
    vmathV3MakeFromElems( &result->col0, ( ( 1.0f - qyqy2 ) - qzqz2 ), ( qxqy2 + qzqw2 ), ( qxqz2 - qyqw2 ) );
    vmathV3MakeFromElems( &result->col1, ( qxqy2 - qzqw2 ), ( ( 1.0f - qxqx2 ) - qzqz2 ), ( qyqz2 + qxqw2 ) );
    vmathV3MakeFromElems( &result->col2, ( qxqz2 + qyqw2 ), ( qyqz2 - qxqw2 ), ( ( 1.0f - qxqx2 ) - qyqy2 ) );
}

static inline void vmathM3MakeFromCols( VmathMatrix3 *result, const VmathVector3 *_col0, const VmathVector3 *_col1, const VmathVector3 *_col2 )
{
    vmathV3Copy( &result->col0, _col0 );
    vmathV3Copy( &result->col1, _col1 );
    vmathV3Copy( &result->col2, _col2 );
}

static inline void vmathM3SetCol0( VmathMatrix3 *result, const VmathVector3 *_col0 )
{
    vmathV3Copy( &result->col0, _col0 );
}

static inline void vmathM3SetCol1( VmathMatrix3 *result, const VmathVector3 *_col1 )
{
    vmathV3Copy( &result->col1, _col1 );
}

static inline void vmathM3SetCol2( VmathMatrix3 *result, const VmathVector3 *_col2 )
{
    vmathV3Copy( &result->col2, _col2 );
}

static inline void vmathM3SetCol( VmathMatrix3 *result, int col, const VmathVector3 *vec )
{
    vmathV3Copy( (&result->col0 + col), vec );
}

static inline void vmathM3SetRow( VmathMatrix3 *result, int row, const VmathVector3 *vec )
{
    vmathV3SetElem( &result->col0, row, vmathV3GetElem( vec, 0 ) );
    vmathV3SetElem( &result->col1, row, vmathV3GetElem( vec, 1 ) );
    vmathV3SetElem( &result->col2, row, vmathV3GetElem( vec, 2 ) );
}

static inline void vmathM3SetElem( VmathMatrix3 *result, int col, int row, float val )
{
    VmathVector3 tmpV3_0;
    vmathM3GetCol( &tmpV3_0, result, col );
    vmathV3SetElem( &tmpV3_0, row, val );
    vmathM3SetCol( result, col, &tmpV3_0 );
}

static inline float vmathM3GetElem( const VmathMatrix3 *mat, int col, int row )
{
    VmathVector3 tmpV3_0;
    vmathM3GetCol( &tmpV3_0, mat, col );
    return vmathV3GetElem( &tmpV3_0, row );
}

static inline void vmathM3GetCol0( VmathVector3 *result, const VmathMatrix3 *mat )
{
    vmathV3Copy( result, &mat->col0 );
}

static inline void vmathM3GetCol1( VmathVector3 *result, const VmathMatrix3 *mat )
{
    vmathV3Copy( result, &mat->col1 );
}

static inline void vmathM3GetCol2( VmathVector3 *result, const VmathMatrix3 *mat )
{
    vmathV3Copy( result, &mat->col2 );
}

static inline void vmathM3GetCol( VmathVector3 *result, const VmathMatrix3 *mat, int col )
{
    vmathV3Copy( result, (&mat->col0 + col) );
}

static inline void vmathM3GetRow( VmathVector3 *result, const VmathMatrix3 *mat, int row )
{
    vmathV3MakeFromElems( result, vmathV3GetElem( &mat->col0, row ), vmathV3GetElem( &mat->col1, row ), vmathV3GetElem( &mat->col2, row ) );
}

static inline void vmathM3Transpose( VmathMatrix3 *result, const VmathMatrix3 *mat )
{
    VmathMatrix3 tmpResult;
    vmathV3MakeFromElems( &tmpResult.col0, mat->col0.x, mat->col1.x, mat->col2.x );
    vmathV3MakeFromElems( &tmpResult.col1, mat->col0.y, mat->col1.y, mat->col2.y );
    vmathV3MakeFromElems( &tmpResult.col2, mat->col0.z, mat->col1.z, mat->col2.z );
    vmathM3Copy( result, &tmpResult );
}

static inline void vmathM3Inverse( VmathMatrix3 *result, const VmathMatrix3 *mat )
{
    VmathVector3 tmp0, tmp1, tmp2;
    float detinv;
    vmathV3Cross( &tmp0, &mat->col1, &mat->col2 );
    vmathV3Cross( &tmp1, &mat->col2, &mat->col0 );
    vmathV3Cross( &tmp2, &mat->col0, &mat->col1 );
    detinv = ( 1.0f / vmathV3Dot( &mat->col2, &tmp2 ) );
    vmathV3MakeFromElems( &result->col0, ( tmp0.x * detinv ), ( tmp1.x * detinv ), ( tmp2.x * detinv ) );
    vmathV3MakeFromElems( &result->col1, ( tmp0.y * detinv ), ( tmp1.y * detinv ), ( tmp2.y * detinv ) );
    vmathV3MakeFromElems( &result->col2, ( tmp0.z * detinv ), ( tmp1.z * detinv ), ( tmp2.z * detinv ) );
}

static inline float vmathM3Determinant( const VmathMatrix3 *mat )
{
    VmathVector3 tmpV3_0;
    vmathV3Cross( &tmpV3_0, &mat->col0, &mat->col1 );
    return vmathV3Dot( &mat->col2, &tmpV3_0 );
}

static inline void vmathM3Add( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 )
{
    vmathV3Add( &result->col0, &mat0->col0, &mat1->col0 );
    vmathV3Add( &result->col1, &mat0->col1, &mat1->col1 );
    vmathV3Add( &result->col2, &mat0->col2, &mat1->col2 );
}

static inline void vmathM3Sub( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 )
{
    vmathV3Sub( &result->col0, &mat0->col0, &mat1->col0 );
    vmathV3Sub( &result->col1, &mat0->col1, &mat1->col1 );
    vmathV3Sub( &result->col2, &mat0->col2, &mat1->col2 );
}

static inline void vmathM3Neg( VmathMatrix3 *result, const VmathMatrix3 *mat )
{
    vmathV3Neg( &result->col0, &mat->col0 );
    vmathV3Neg( &result->col1, &mat->col1 );
    vmathV3Neg( &result->col2, &mat->col2 );
}

static inline void vmathM3AbsPerElem( VmathMatrix3 *result, const VmathMatrix3 *mat )
{
    vmathV3AbsPerElem( &result->col0, &mat->col0 );
    vmathV3AbsPerElem( &result->col1, &mat->col1 );
    vmathV3AbsPerElem( &result->col2, &mat->col2 );
}

static inline void vmathM3ScalarMul( VmathMatrix3 *result, const VmathMatrix3 *mat, float scalar )
{
    vmathV3ScalarMul( &result->col0, &mat->col0, scalar );
    vmathV3ScalarMul( &result->col1, &mat->col1, scalar );
    vmathV3ScalarMul( &result->col2, &mat->col2, scalar );
}

static inline void vmathM3MulV3( VmathVector3 *result, const VmathMatrix3 *mat, const VmathVector3 *vec )
{
    float tmpX, tmpY, tmpZ;
    tmpX = ( ( ( mat->col0.x * vec->x ) + ( mat->col1.x * vec->y ) ) + ( mat->col2.x * vec->z ) );
    tmpY = ( ( ( mat->col0.y * vec->x ) + ( mat->col1.y * vec->y ) ) + ( mat->col2.y * vec->z ) );
    tmpZ = ( ( ( mat->col0.z * vec->x ) + ( mat->col1.z * vec->y ) ) + ( mat->col2.z * vec->z ) );
    vmathV3MakeFromElems( result, tmpX, tmpY, tmpZ );
}

static inline void vmathM3Mul( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 )
{
    VmathMatrix3 tmpResult;
    vmathM3MulV3( &tmpResult.col0, mat0, &mat1->col0 );
    vmathM3MulV3( &tmpResult.col1, mat0, &mat1->col1 );
    vmathM3MulV3( &tmpResult.col2, mat0, &mat1->col2 );
    vmathM3Copy( result, &tmpResult );
}

static inline void vmathM3MulPerElem( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1 )
{
    vmathV3MulPerElem( &result->col0, &mat0->col0, &mat1->col0 );
    vmathV3MulPerElem( &result->col1, &mat0->col1, &mat1->col1 );
    vmathV3MulPerElem( &result->col2, &mat0->col2, &mat1->col2 );
}

static inline void vmathM3MakeIdentity( VmathMatrix3 *result )
{
    vmathV3MakeXAxis( &result->col0 );
    vmathV3MakeYAxis( &result->col1 );
    vmathV3MakeZAxis( &result->col2 );
}

static inline void vmathM3MakeRotationX( VmathMatrix3 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV3MakeXAxis( &result->col0 );
    vmathV3MakeFromElems( &result->col1, 0.0f, c, s );
    vmathV3MakeFromElems( &result->col2, 0.0f, -s, c );
}

static inline void vmathM3MakeRotationY( VmathMatrix3 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV3MakeFromElems( &result->col0, c, 0.0f, -s );
    vmathV3MakeYAxis( &result->col1 );
    vmathV3MakeFromElems( &result->col2, s, 0.0f, c );
}

static inline void vmathM3MakeRotationZ( VmathMatrix3 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV3MakeFromElems( &result->col0, c, s, 0.0f );
    vmathV3MakeFromElems( &result->col1, -s, c, 0.0f );
    vmathV3MakeZAxis( &result->col2 );
}

static inline void vmathM3MakeRotationZYX( VmathMatrix3 *result, const VmathVector3 *radiansXYZ )
{
    float sX, cX, sY, cY, sZ, cZ, tmp0, tmp1;
    sX = sinf( radiansXYZ->x );
    cX = cosf( radiansXYZ->x );
    sY = sinf( radiansXYZ->y );
    cY = cosf( radiansXYZ->y );
    sZ = sinf( radiansXYZ->z );
    cZ = cosf( radiansXYZ->z );
    tmp0 = ( cZ * sY );
    tmp1 = ( sZ * sY );
    vmathV3MakeFromElems( &result->col0, ( cZ * cY ), ( sZ * cY ), -sY );
    vmathV3MakeFromElems( &result->col1, ( ( tmp0 * sX ) - ( sZ * cX ) ), ( ( tmp1 * sX ) + ( cZ * cX ) ), ( cY * sX ) );
    vmathV3MakeFromElems( &result->col2, ( ( tmp0 * cX ) + ( sZ * sX ) ), ( ( tmp1 * cX ) - ( cZ * sX ) ), ( cY * cX ) );
}

static inline void vmathM3MakeRotationAxis( VmathMatrix3 *result, float radians, const VmathVector3 *unitVec )
{
    float x, y, z, s, c, oneMinusC, xy, yz, zx;
    s = sinf( radians );
    c = cosf( radians );
    x = unitVec->x;
    y = unitVec->y;
    z = unitVec->z;
    xy = ( x * y );
    yz = ( y * z );
    zx = ( z * x );
    oneMinusC = ( 1.0f - c );
    vmathV3MakeFromElems( &result->col0, ( ( ( x * x ) * oneMinusC ) + c ), ( ( xy * oneMinusC ) + ( z * s ) ), ( ( zx * oneMinusC ) - ( y * s ) ) );
    vmathV3MakeFromElems( &result->col1, ( ( xy * oneMinusC ) - ( z * s ) ), ( ( ( y * y ) * oneMinusC ) + c ), ( ( yz * oneMinusC ) + ( x * s ) ) );
    vmathV3MakeFromElems( &result->col2, ( ( zx * oneMinusC ) + ( y * s ) ), ( ( yz * oneMinusC ) - ( x * s ) ), ( ( ( z * z ) * oneMinusC ) + c ) );
}

static inline void vmathM3MakeRotationQ( VmathMatrix3 *result, const VmathQuat *unitQuat )
{
    vmathM3MakeFromQ( result, unitQuat );
}

static inline void vmathM3MakeScale( VmathMatrix3 *result, const VmathVector3 *scaleVec )
{
    vmathV3MakeFromElems( &result->col0, scaleVec->x, 0.0f, 0.0f );
    vmathV3MakeFromElems( &result->col1, 0.0f, scaleVec->y, 0.0f );
    vmathV3MakeFromElems( &result->col2, 0.0f, 0.0f, scaleVec->z );
}

static inline void vmathM3AppendScale( VmathMatrix3 *result, const VmathMatrix3 *mat, const VmathVector3 *scaleVec )
{
    vmathV3ScalarMul( &result->col0, &mat->col0, vmathV3GetX( scaleVec ) );
    vmathV3ScalarMul( &result->col1, &mat->col1, vmathV3GetY( scaleVec ) );
    vmathV3ScalarMul( &result->col2, &mat->col2, vmathV3GetZ( scaleVec ) );
}

static inline void vmathM3PrependScale( VmathMatrix3 *result, const VmathVector3 *scaleVec, const VmathMatrix3 *mat )
{
    vmathV3MulPerElem( &result->col0, &mat->col0, scaleVec );
    vmathV3MulPerElem( &result->col1, &mat->col1, scaleVec );
    vmathV3MulPerElem( &result->col2, &mat->col2, scaleVec );
}

static inline void vmathM3Select( VmathMatrix3 *result, const VmathMatrix3 *mat0, const VmathMatrix3 *mat1, unsigned int select1 )
{
    vmathV3Select( &result->col0, &mat0->col0, &mat1->col0, select1 );
    vmathV3Select( &result->col1, &mat0->col1, &mat1->col1, select1 );
    vmathV3Select( &result->col2, &mat0->col2, &mat1->col2, select1 );
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathM3Print( const VmathMatrix3 *mat )
{
    VmathVector3 tmpV3_0, tmpV3_1, tmpV3_2;
    vmathM3GetRow( &tmpV3_0, mat, 0 );
    vmathV3Print( &tmpV3_0 );
    vmathM3GetRow( &tmpV3_1, mat, 1 );
    vmathV3Print( &tmpV3_1 );
    vmathM3GetRow( &tmpV3_2, mat, 2 );
    vmathV3Print( &tmpV3_2 );
}

static inline void vmathM3Prints( const VmathMatrix3 *mat, const char *name )
{
    printf("%s:\n", name);
    vmathM3Print( mat );
}

#endif

static inline void vmathM4Copy( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    vmathV4Copy( &result->col0, &mat->col0 );
    vmathV4Copy( &result->col1, &mat->col1 );
    vmathV4Copy( &result->col2, &mat->col2 );
    vmathV4Copy( &result->col3, &mat->col3 );
}

static inline void vmathM4MakeFromScalar( VmathMatrix4 *result, float scalar )
{
    vmathV4MakeFromScalar( &result->col0, scalar );
    vmathV4MakeFromScalar( &result->col1, scalar );
    vmathV4MakeFromScalar( &result->col2, scalar );
    vmathV4MakeFromScalar( &result->col3, scalar );
}

static inline void vmathM4MakeFromT3( VmathMatrix4 *result, const VmathTransform3 *mat )
{
    vmathV4MakeFromV3Scalar( &result->col0, &mat->col0, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col1, &mat->col1, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col2, &mat->col2, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col3, &mat->col3, 1.0f );
}

static inline void vmathM4MakeFromCols( VmathMatrix4 *result, const VmathVector4 *_col0, const VmathVector4 *_col1, const VmathVector4 *_col2, const VmathVector4 *_col3 )
{
    vmathV4Copy( &result->col0, _col0 );
    vmathV4Copy( &result->col1, _col1 );
    vmathV4Copy( &result->col2, _col2 );
    vmathV4Copy( &result->col3, _col3 );
}

static inline void vmathM4MakeFromM3V3( VmathMatrix4 *result, const VmathMatrix3 *mat, const VmathVector3 *translateVec )
{
    vmathV4MakeFromV3Scalar( &result->col0, &mat->col0, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col1, &mat->col1, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col2, &mat->col2, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col3, translateVec, 1.0f );
}

static inline void vmathM4MakeFromQV3( VmathMatrix4 *result, const VmathQuat *unitQuat, const VmathVector3 *translateVec )
{
    VmathMatrix3 mat;
    vmathM3MakeFromQ( &mat, unitQuat );
    vmathV4MakeFromV3Scalar( &result->col0, &mat.col0, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col1, &mat.col1, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col2, &mat.col2, 0.0f );
    vmathV4MakeFromV3Scalar( &result->col3, translateVec, 1.0f );
}

static inline void vmathM4SetCol0( VmathMatrix4 *result, const VmathVector4 *_col0 )
{
    vmathV4Copy( &result->col0, _col0 );
}

static inline void vmathM4SetCol1( VmathMatrix4 *result, const VmathVector4 *_col1 )
{
    vmathV4Copy( &result->col1, _col1 );
}

static inline void vmathM4SetCol2( VmathMatrix4 *result, const VmathVector4 *_col2 )
{
    vmathV4Copy( &result->col2, _col2 );
}

static inline void vmathM4SetCol3( VmathMatrix4 *result, const VmathVector4 *_col3 )
{
    vmathV4Copy( &result->col3, _col3 );
}

static inline void vmathM4SetCol( VmathMatrix4 *result, int col, const VmathVector4 *vec )
{
    vmathV4Copy( (&result->col0 + col), vec );
}

static inline void vmathM4SetRow( VmathMatrix4 *result, int row, const VmathVector4 *vec )
{
    vmathV4SetElem( &result->col0, row, vmathV4GetElem( vec, 0 ) );
    vmathV4SetElem( &result->col1, row, vmathV4GetElem( vec, 1 ) );
    vmathV4SetElem( &result->col2, row, vmathV4GetElem( vec, 2 ) );
    vmathV4SetElem( &result->col3, row, vmathV4GetElem( vec, 3 ) );
}

static inline void vmathM4SetElem( VmathMatrix4 *result, int col, int row, float val )
{
    VmathVector4 tmpV3_0;
    vmathM4GetCol( &tmpV3_0, result, col );
    vmathV4SetElem( &tmpV3_0, row, val );
    vmathM4SetCol( result, col, &tmpV3_0 );
}

static inline float vmathM4GetElem( const VmathMatrix4 *mat, int col, int row )
{
    VmathVector4 tmpV4_0;
    vmathM4GetCol( &tmpV4_0, mat, col );
    return vmathV4GetElem( &tmpV4_0, row );
}

static inline void vmathM4GetCol0( VmathVector4 *result, const VmathMatrix4 *mat )
{
    vmathV4Copy( result, &mat->col0 );
}

static inline void vmathM4GetCol1( VmathVector4 *result, const VmathMatrix4 *mat )
{
    vmathV4Copy( result, &mat->col1 );
}

static inline void vmathM4GetCol2( VmathVector4 *result, const VmathMatrix4 *mat )
{
    vmathV4Copy( result, &mat->col2 );
}

static inline void vmathM4GetCol3( VmathVector4 *result, const VmathMatrix4 *mat )
{
    vmathV4Copy( result, &mat->col3 );
}

static inline void vmathM4GetCol( VmathVector4 *result, const VmathMatrix4 *mat, int col )
{
    vmathV4Copy( result, (&mat->col0 + col) );
}

static inline void vmathM4GetRow( VmathVector4 *result, const VmathMatrix4 *mat, int row )
{
    vmathV4MakeFromElems( result, vmathV4GetElem( &mat->col0, row ), vmathV4GetElem( &mat->col1, row ), vmathV4GetElem( &mat->col2, row ), vmathV4GetElem( &mat->col3, row ) );
}

static inline void vmathM4Transpose( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    VmathMatrix4 tmpResult;
    vmathV4MakeFromElems( &tmpResult.col0, mat->col0.x, mat->col1.x, mat->col2.x, mat->col3.x );
    vmathV4MakeFromElems( &tmpResult.col1, mat->col0.y, mat->col1.y, mat->col2.y, mat->col3.y );
    vmathV4MakeFromElems( &tmpResult.col2, mat->col0.z, mat->col1.z, mat->col2.z, mat->col3.z );
    vmathV4MakeFromElems( &tmpResult.col3, mat->col0.w, mat->col1.w, mat->col2.w, mat->col3.w );
    vmathM4Copy( result, &tmpResult );
}

static inline void vmathM4Inverse( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    VmathVector4 res0, res1, res2, res3;
    float mA, mB, mC, mD, mE, mF, mG, mH, mI, mJ, mK, mL, mM, mN, mO, mP, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, detInv;
    mA = mat->col0.x;
    mB = mat->col0.y;
    mC = mat->col0.z;
    mD = mat->col0.w;
    mE = mat->col1.x;
    mF = mat->col1.y;
    mG = mat->col1.z;
    mH = mat->col1.w;
    mI = mat->col2.x;
    mJ = mat->col2.y;
    mK = mat->col2.z;
    mL = mat->col2.w;
    mM = mat->col3.x;
    mN = mat->col3.y;
    mO = mat->col3.z;
    mP = mat->col3.w;
    tmp0 = ( ( mK * mD ) - ( mC * mL ) );
    tmp1 = ( ( mO * mH ) - ( mG * mP ) );
    tmp2 = ( ( mB * mK ) - ( mJ * mC ) );
    tmp3 = ( ( mF * mO ) - ( mN * mG ) );
    tmp4 = ( ( mJ * mD ) - ( mB * mL ) );
    tmp5 = ( ( mN * mH ) - ( mF * mP ) );
    vmathV4SetX( &res0, ( ( ( mJ * tmp1 ) - ( mL * tmp3 ) ) - ( mK * tmp5 ) ) );
    vmathV4SetY( &res0, ( ( ( mN * tmp0 ) - ( mP * tmp2 ) ) - ( mO * tmp4 ) ) );
    vmathV4SetZ( &res0, ( ( ( mD * tmp3 ) + ( mC * tmp5 ) ) - ( mB * tmp1 ) ) );
    vmathV4SetW( &res0, ( ( ( mH * tmp2 ) + ( mG * tmp4 ) ) - ( mF * tmp0 ) ) );
    detInv = ( 1.0f / ( ( ( ( mA * res0.x ) + ( mE * res0.y ) ) + ( mI * res0.z ) ) + ( mM * res0.w ) ) );
    vmathV4SetX( &res1, ( mI * tmp1 ) );
    vmathV4SetY( &res1, ( mM * tmp0 ) );
    vmathV4SetZ( &res1, ( mA * tmp1 ) );
    vmathV4SetW( &res1, ( mE * tmp0 ) );
    vmathV4SetX( &res3, ( mI * tmp3 ) );
    vmathV4SetY( &res3, ( mM * tmp2 ) );
    vmathV4SetZ( &res3, ( mA * tmp3 ) );
    vmathV4SetW( &res3, ( mE * tmp2 ) );
    vmathV4SetX( &res2, ( mI * tmp5 ) );
    vmathV4SetY( &res2, ( mM * tmp4 ) );
    vmathV4SetZ( &res2, ( mA * tmp5 ) );
    vmathV4SetW( &res2, ( mE * tmp4 ) );
    tmp0 = ( ( mI * mB ) - ( mA * mJ ) );
    tmp1 = ( ( mM * mF ) - ( mE * mN ) );
    tmp2 = ( ( mI * mD ) - ( mA * mL ) );
    tmp3 = ( ( mM * mH ) - ( mE * mP ) );
    tmp4 = ( ( mI * mC ) - ( mA * mK ) );
    tmp5 = ( ( mM * mG ) - ( mE * mO ) );
    vmathV4SetX( &res2, ( ( ( mL * tmp1 ) - ( mJ * tmp3 ) ) + res2.x ) );
    vmathV4SetY( &res2, ( ( ( mP * tmp0 ) - ( mN * tmp2 ) ) + res2.y ) );
    vmathV4SetZ( &res2, ( ( ( mB * tmp3 ) - ( mD * tmp1 ) ) - res2.z ) );
    vmathV4SetW( &res2, ( ( ( mF * tmp2 ) - ( mH * tmp0 ) ) - res2.w ) );
    vmathV4SetX( &res3, ( ( ( mJ * tmp5 ) - ( mK * tmp1 ) ) + res3.x ) );
    vmathV4SetY( &res3, ( ( ( mN * tmp4 ) - ( mO * tmp0 ) ) + res3.y ) );
    vmathV4SetZ( &res3, ( ( ( mC * tmp1 ) - ( mB * tmp5 ) ) - res3.z ) );
    vmathV4SetW( &res3, ( ( ( mG * tmp0 ) - ( mF * tmp4 ) ) - res3.w ) );
    vmathV4SetX( &res1, ( ( ( mK * tmp3 ) - ( mL * tmp5 ) ) - res1.x ) );
    vmathV4SetY( &res1, ( ( ( mO * tmp2 ) - ( mP * tmp4 ) ) - res1.y ) );
    vmathV4SetZ( &res1, ( ( ( mD * tmp5 ) - ( mC * tmp3 ) ) + res1.z ) );
    vmathV4SetW( &res1, ( ( ( mH * tmp4 ) - ( mG * tmp2 ) ) + res1.w ) );
    vmathV4ScalarMul( &result->col0, &res0, detInv );
    vmathV4ScalarMul( &result->col1, &res1, detInv );
    vmathV4ScalarMul( &result->col2, &res2, detInv );
    vmathV4ScalarMul( &result->col3, &res3, detInv );
}

static inline void vmathM4AffineInverse( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    VmathTransform3 affineMat, tmpT3_0;
    VmathVector3 tmpV3_0, tmpV3_1, tmpV3_2, tmpV3_3;
    vmathV4GetXYZ( &tmpV3_0, &mat->col0 );
    vmathT3SetCol0( &affineMat, &tmpV3_0 );
    vmathV4GetXYZ( &tmpV3_1, &mat->col1 );
    vmathT3SetCol1( &affineMat, &tmpV3_1 );
    vmathV4GetXYZ( &tmpV3_2, &mat->col2 );
    vmathT3SetCol2( &affineMat, &tmpV3_2 );
    vmathV4GetXYZ( &tmpV3_3, &mat->col3 );
    vmathT3SetCol3( &affineMat, &tmpV3_3 );
    vmathT3Inverse( &tmpT3_0, &affineMat );
    vmathM4MakeFromT3( result, &tmpT3_0 );
}

static inline void vmathM4OrthoInverse( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    VmathTransform3 affineMat, tmpT3_0;
    VmathVector3 tmpV3_0, tmpV3_1, tmpV3_2, tmpV3_3;
    vmathV4GetXYZ( &tmpV3_0, &mat->col0 );
    vmathT3SetCol0( &affineMat, &tmpV3_0 );
    vmathV4GetXYZ( &tmpV3_1, &mat->col1 );
    vmathT3SetCol1( &affineMat, &tmpV3_1 );
    vmathV4GetXYZ( &tmpV3_2, &mat->col2 );
    vmathT3SetCol2( &affineMat, &tmpV3_2 );
    vmathV4GetXYZ( &tmpV3_3, &mat->col3 );
    vmathT3SetCol3( &affineMat, &tmpV3_3 );
    vmathT3OrthoInverse( &tmpT3_0, &affineMat );
    vmathM4MakeFromT3( result, &tmpT3_0 );
}

static inline float vmathM4Determinant( const VmathMatrix4 *mat )
{
    float dx, dy, dz, dw, mA, mB, mC, mD, mE, mF, mG, mH, mI, mJ, mK, mL, mM, mN, mO, mP, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
    mA = mat->col0.x;
    mB = mat->col0.y;
    mC = mat->col0.z;
    mD = mat->col0.w;
    mE = mat->col1.x;
    mF = mat->col1.y;
    mG = mat->col1.z;
    mH = mat->col1.w;
    mI = mat->col2.x;
    mJ = mat->col2.y;
    mK = mat->col2.z;
    mL = mat->col2.w;
    mM = mat->col3.x;
    mN = mat->col3.y;
    mO = mat->col3.z;
    mP = mat->col3.w;
    tmp0 = ( ( mK * mD ) - ( mC * mL ) );
    tmp1 = ( ( mO * mH ) - ( mG * mP ) );
    tmp2 = ( ( mB * mK ) - ( mJ * mC ) );
    tmp3 = ( ( mF * mO ) - ( mN * mG ) );
    tmp4 = ( ( mJ * mD ) - ( mB * mL ) );
    tmp5 = ( ( mN * mH ) - ( mF * mP ) );
    dx = ( ( ( mJ * tmp1 ) - ( mL * tmp3 ) ) - ( mK * tmp5 ) );
    dy = ( ( ( mN * tmp0 ) - ( mP * tmp2 ) ) - ( mO * tmp4 ) );
    dz = ( ( ( mD * tmp3 ) + ( mC * tmp5 ) ) - ( mB * tmp1 ) );
    dw = ( ( ( mH * tmp2 ) + ( mG * tmp4 ) ) - ( mF * tmp0 ) );
    return ( ( ( ( mA * dx ) + ( mE * dy ) ) + ( mI * dz ) ) + ( mM * dw ) );
}

static inline void vmathM4Add( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 )
{
    vmathV4Add( &result->col0, &mat0->col0, &mat1->col0 );
    vmathV4Add( &result->col1, &mat0->col1, &mat1->col1 );
    vmathV4Add( &result->col2, &mat0->col2, &mat1->col2 );
    vmathV4Add( &result->col3, &mat0->col3, &mat1->col3 );
}

static inline void vmathM4Sub( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 )
{
    vmathV4Sub( &result->col0, &mat0->col0, &mat1->col0 );
    vmathV4Sub( &result->col1, &mat0->col1, &mat1->col1 );
    vmathV4Sub( &result->col2, &mat0->col2, &mat1->col2 );
    vmathV4Sub( &result->col3, &mat0->col3, &mat1->col3 );
}

static inline void vmathM4Neg( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    vmathV4Neg( &result->col0, &mat->col0 );
    vmathV4Neg( &result->col1, &mat->col1 );
    vmathV4Neg( &result->col2, &mat->col2 );
    vmathV4Neg( &result->col3, &mat->col3 );
}

static inline void vmathM4AbsPerElem( VmathMatrix4 *result, const VmathMatrix4 *mat )
{
    vmathV4AbsPerElem( &result->col0, &mat->col0 );
    vmathV4AbsPerElem( &result->col1, &mat->col1 );
    vmathV4AbsPerElem( &result->col2, &mat->col2 );
    vmathV4AbsPerElem( &result->col3, &mat->col3 );
}

static inline void vmathM4ScalarMul( VmathMatrix4 *result, const VmathMatrix4 *mat, float scalar )
{
    vmathV4ScalarMul( &result->col0, &mat->col0, scalar );
    vmathV4ScalarMul( &result->col1, &mat->col1, scalar );
    vmathV4ScalarMul( &result->col2, &mat->col2, scalar );
    vmathV4ScalarMul( &result->col3, &mat->col3, scalar );
}

static inline void vmathM4MulV4( VmathVector4 *result, const VmathMatrix4 *mat, const VmathVector4 *vec )
{
    float tmpX, tmpY, tmpZ, tmpW;
    tmpX = ( ( ( ( mat->col0.x * vec->x ) + ( mat->col1.x * vec->y ) ) + ( mat->col2.x * vec->z ) ) + ( mat->col3.x * vec->w ) );
    tmpY = ( ( ( ( mat->col0.y * vec->x ) + ( mat->col1.y * vec->y ) ) + ( mat->col2.y * vec->z ) ) + ( mat->col3.y * vec->w ) );
    tmpZ = ( ( ( ( mat->col0.z * vec->x ) + ( mat->col1.z * vec->y ) ) + ( mat->col2.z * vec->z ) ) + ( mat->col3.z * vec->w ) );
    tmpW = ( ( ( ( mat->col0.w * vec->x ) + ( mat->col1.w * vec->y ) ) + ( mat->col2.w * vec->z ) ) + ( mat->col3.w * vec->w ) );
    vmathV4MakeFromElems( result, tmpX, tmpY, tmpZ, tmpW );
}

static inline void vmathM4MulV3( VmathVector4 *result, const VmathMatrix4 *mat, const VmathVector3 *vec )
{
    result->x = ( ( ( mat->col0.x * vec->x ) + ( mat->col1.x * vec->y ) ) + ( mat->col2.x * vec->z ) );
    result->y = ( ( ( mat->col0.y * vec->x ) + ( mat->col1.y * vec->y ) ) + ( mat->col2.y * vec->z ) );
    result->z = ( ( ( mat->col0.z * vec->x ) + ( mat->col1.z * vec->y ) ) + ( mat->col2.z * vec->z ) );
    result->w = ( ( ( mat->col0.w * vec->x ) + ( mat->col1.w * vec->y ) ) + ( mat->col2.w * vec->z ) );
}

static inline void vmathM4MulP3( VmathVector4 *result, const VmathMatrix4 *mat, const VmathPoint3 *pnt )
{
    result->x = ( ( ( ( mat->col0.x * pnt->x ) + ( mat->col1.x * pnt->y ) ) + ( mat->col2.x * pnt->z ) ) + mat->col3.x );
    result->y = ( ( ( ( mat->col0.y * pnt->x ) + ( mat->col1.y * pnt->y ) ) + ( mat->col2.y * pnt->z ) ) + mat->col3.y );
    result->z = ( ( ( ( mat->col0.z * pnt->x ) + ( mat->col1.z * pnt->y ) ) + ( mat->col2.z * pnt->z ) ) + mat->col3.z );
    result->w = ( ( ( ( mat->col0.w * pnt->x ) + ( mat->col1.w * pnt->y ) ) + ( mat->col2.w * pnt->z ) ) + mat->col3.w );
}

static inline void vmathM4Mul( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 )
{
    VmathMatrix4 tmpResult;
    vmathM4MulV4( &tmpResult.col0, mat0, &mat1->col0 );
    vmathM4MulV4( &tmpResult.col1, mat0, &mat1->col1 );
    vmathM4MulV4( &tmpResult.col2, mat0, &mat1->col2 );
    vmathM4MulV4( &tmpResult.col3, mat0, &mat1->col3 );
    vmathM4Copy( result, &tmpResult );
}

static inline void vmathM4MulT3( VmathMatrix4 *result, const VmathMatrix4 *mat, const VmathTransform3 *tfrm1 )
{
    VmathMatrix4 tmpResult;
    VmathPoint3 tmpP3_0;
    vmathM4MulV3( &tmpResult.col0, mat, &tfrm1->col0 );
    vmathM4MulV3( &tmpResult.col1, mat, &tfrm1->col1 );
    vmathM4MulV3( &tmpResult.col2, mat, &tfrm1->col2 );
    vmathP3MakeFromV3( &tmpP3_0, &tfrm1->col3 );
    vmathM4MulP3( &tmpResult.col3, mat, &tmpP3_0 );
    vmathM4Copy( result, &tmpResult );
}

static inline void vmathM4MulPerElem( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1 )
{
    vmathV4MulPerElem( &result->col0, &mat0->col0, &mat1->col0 );
    vmathV4MulPerElem( &result->col1, &mat0->col1, &mat1->col1 );
    vmathV4MulPerElem( &result->col2, &mat0->col2, &mat1->col2 );
    vmathV4MulPerElem( &result->col3, &mat0->col3, &mat1->col3 );
}

static inline void vmathM4MakeIdentity( VmathMatrix4 *result )
{
    vmathV4MakeXAxis( &result->col0 );
    vmathV4MakeYAxis( &result->col1 );
    vmathV4MakeZAxis( &result->col2 );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4SetUpper3x3( VmathMatrix4 *result, const VmathMatrix3 *mat3 )
{
    vmathV4SetXYZ( &result->col0, &mat3->col0 );
    vmathV4SetXYZ( &result->col1, &mat3->col1 );
    vmathV4SetXYZ( &result->col2, &mat3->col2 );
}

static inline void vmathM4GetUpper3x3( VmathMatrix3 *result, const VmathMatrix4 *mat )
{
    vmathV4GetXYZ( &result->col0, &mat->col0 );
    vmathV4GetXYZ( &result->col1, &mat->col1 );
    vmathV4GetXYZ( &result->col2, &mat->col2 );
}

static inline void vmathM4SetTranslation( VmathMatrix4 *result, const VmathVector3 *translateVec )
{
    vmathV4SetXYZ( &result->col3, translateVec );
}

static inline void vmathM4GetTranslation( VmathVector3 *result, const VmathMatrix4 *mat )
{
    vmathV4GetXYZ( result, &mat->col3 );
}

static inline void vmathM4MakeRotationX( VmathMatrix4 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV4MakeXAxis( &result->col0 );
    vmathV4MakeFromElems( &result->col1, 0.0f, c, s, 0.0f );
    vmathV4MakeFromElems( &result->col2, 0.0f, -s, c, 0.0f );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4MakeRotationY( VmathMatrix4 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV4MakeFromElems( &result->col0, c, 0.0f, -s, 0.0f );
    vmathV4MakeYAxis( &result->col1 );
    vmathV4MakeFromElems( &result->col2, s, 0.0f, c, 0.0f );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4MakeRotationZ( VmathMatrix4 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV4MakeFromElems( &result->col0, c, s, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col1, -s, c, 0.0f, 0.0f );
    vmathV4MakeZAxis( &result->col2 );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4MakeRotationZYX( VmathMatrix4 *result, const VmathVector3 *radiansXYZ )
{
    float sX, cX, sY, cY, sZ, cZ, tmp0, tmp1;
    sX = sinf( radiansXYZ->x );
    cX = cosf( radiansXYZ->x );
    sY = sinf( radiansXYZ->y );
    cY = cosf( radiansXYZ->y );
    sZ = sinf( radiansXYZ->z );
    cZ = cosf( radiansXYZ->z );
    tmp0 = ( cZ * sY );
    tmp1 = ( sZ * sY );
    vmathV4MakeFromElems( &result->col0, ( cZ * cY ), ( sZ * cY ), -sY, 0.0f );
    vmathV4MakeFromElems( &result->col1, ( ( tmp0 * sX ) - ( sZ * cX ) ), ( ( tmp1 * sX ) + ( cZ * cX ) ), ( cY * sX ), 0.0f );
    vmathV4MakeFromElems( &result->col2, ( ( tmp0 * cX ) + ( sZ * sX ) ), ( ( tmp1 * cX ) - ( cZ * sX ) ), ( cY * cX ), 0.0f );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4MakeRotationAxis( VmathMatrix4 *result, float radians, const VmathVector3 *unitVec )
{
    float x, y, z, s, c, oneMinusC, xy, yz, zx;
    s = sinf( radians );
    c = cosf( radians );
    x = unitVec->x;
    y = unitVec->y;
    z = unitVec->z;
    xy = ( x * y );
    yz = ( y * z );
    zx = ( z * x );
    oneMinusC = ( 1.0f - c );
    vmathV4MakeFromElems( &result->col0, ( ( ( x * x ) * oneMinusC ) + c ), ( ( xy * oneMinusC ) + ( z * s ) ), ( ( zx * oneMinusC ) - ( y * s ) ), 0.0f );
    vmathV4MakeFromElems( &result->col1, ( ( xy * oneMinusC ) - ( z * s ) ), ( ( ( y * y ) * oneMinusC ) + c ), ( ( yz * oneMinusC ) + ( x * s ) ), 0.0f );
    vmathV4MakeFromElems( &result->col2, ( ( zx * oneMinusC ) + ( y * s ) ), ( ( yz * oneMinusC ) - ( x * s ) ), ( ( ( z * z ) * oneMinusC ) + c ), 0.0f );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4MakeRotationQ( VmathMatrix4 *result, const VmathQuat *unitQuat )
{
    VmathTransform3 tmpT3_0;
    vmathT3MakeRotationQ( &tmpT3_0, unitQuat );
    vmathM4MakeFromT3( result, &tmpT3_0 );
}

static inline void vmathM4MakeScale( VmathMatrix4 *result, const VmathVector3 *scaleVec )
{
    vmathV4MakeFromElems( &result->col0, scaleVec->x, 0.0f, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col1, 0.0f, scaleVec->y, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col2, 0.0f, 0.0f, scaleVec->z, 0.0f );
    vmathV4MakeWAxis( &result->col3 );
}

static inline void vmathM4AppendScale( VmathMatrix4 *result, const VmathMatrix4 *mat, const VmathVector3 *scaleVec )
{
    vmathV4ScalarMul( &result->col0, &mat->col0, vmathV3GetX( scaleVec ) );
    vmathV4ScalarMul( &result->col1, &mat->col1, vmathV3GetY( scaleVec ) );
    vmathV4ScalarMul( &result->col2, &mat->col2, vmathV3GetZ( scaleVec ) );
    vmathV4Copy( &result->col3, &mat->col3 );
}

static inline void vmathM4PrependScale( VmathMatrix4 *result, const VmathVector3 *scaleVec, const VmathMatrix4 *mat )
{
    VmathVector4 scale4;
    vmathV4MakeFromV3Scalar( &scale4, scaleVec, 1.0f );
    vmathV4MulPerElem( &result->col0, &mat->col0, &scale4 );
    vmathV4MulPerElem( &result->col1, &mat->col1, &scale4 );
    vmathV4MulPerElem( &result->col2, &mat->col2, &scale4 );
    vmathV4MulPerElem( &result->col3, &mat->col3, &scale4 );
}

static inline void vmathM4MakeTranslation( VmathMatrix4 *result, const VmathVector3 *translateVec )
{
    vmathV4MakeXAxis( &result->col0 );
    vmathV4MakeYAxis( &result->col1 );
    vmathV4MakeZAxis( &result->col2 );
    vmathV4MakeFromV3Scalar( &result->col3, translateVec, 1.0f );
}

static inline void vmathM4MakeLookAt( VmathMatrix4 *result, const VmathPoint3 *eyePos, const VmathPoint3 *lookAtPos, const VmathVector3 *upVec )
{
    VmathMatrix4 m4EyeFrame;
    VmathVector3 v3X, v3Y, v3Z, tmpV3_0, tmpV3_1;
    VmathVector4 tmpV4_0, tmpV4_1, tmpV4_2, tmpV4_3;
    vmathV3Normalize( &v3Y, upVec );
    vmathP3Sub( &tmpV3_0, eyePos, lookAtPos );
    vmathV3Normalize( &v3Z, &tmpV3_0 );
    vmathV3Cross( &tmpV3_1, &v3Y, &v3Z );
    vmathV3Normalize( &v3X, &tmpV3_1 );
    vmathV3Cross( &v3Y, &v3Z, &v3X );
    vmathV4MakeFromV3( &tmpV4_0, &v3X );
    vmathV4MakeFromV3( &tmpV4_1, &v3Y );
    vmathV4MakeFromV3( &tmpV4_2, &v3Z );
    vmathV4MakeFromP3( &tmpV4_3, eyePos );
    vmathM4MakeFromCols( &m4EyeFrame, &tmpV4_0, &tmpV4_1, &tmpV4_2, &tmpV4_3 );
    vmathM4OrthoInverse( result, &m4EyeFrame );
}

static inline void vmathM4MakePerspective( VmathMatrix4 *result, float fovyRadians, float aspect, float zNear, float zFar )
{
    float f, rangeInv;
    f = tanf( ( (float)( _VECTORMATH_PI_OVER_2 ) - ( 0.5f * fovyRadians ) ) );
    rangeInv = ( 1.0f / ( zNear - zFar ) );
    vmathV4MakeFromElems( &result->col0, ( f / aspect ), 0.0f, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col1, 0.0f, f, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col2, 0.0f, 0.0f, ( ( zNear + zFar ) * rangeInv ), -1.0f );
    vmathV4MakeFromElems( &result->col3, 0.0f, 0.0f, ( ( ( zNear * zFar ) * rangeInv ) * 2.0f ), 0.0f );
}

static inline void vmathM4MakeFrustum( VmathMatrix4 *result, float left, float right, float bottom, float top, float zNear, float zFar )
{
    float sum_rl, sum_tb, sum_nf, inv_rl, inv_tb, inv_nf, n2;
    sum_rl = ( right + left );
    sum_tb = ( top + bottom );
    sum_nf = ( zNear + zFar );
    inv_rl = ( 1.0f / ( right - left ) );
    inv_tb = ( 1.0f / ( top - bottom ) );
    inv_nf = ( 1.0f / ( zNear - zFar ) );
    n2 = ( zNear + zNear );
    vmathV4MakeFromElems( &result->col0, ( n2 * inv_rl ), 0.0f, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col1, 0.0f, ( n2 * inv_tb ), 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col2, ( sum_rl * inv_rl ), ( sum_tb * inv_tb ), ( sum_nf * inv_nf ), -1.0f );
    vmathV4MakeFromElems( &result->col3, 0.0f, 0.0f, ( ( n2 * inv_nf ) * zFar ), 0.0f );
}

static inline void vmathM4MakeOrthographic( VmathMatrix4 *result, float left, float right, float bottom, float top, float zNear, float zFar )
{
    float sum_rl, sum_tb, sum_nf, inv_rl, inv_tb, inv_nf;
    sum_rl = ( right + left );
    sum_tb = ( top + bottom );
    sum_nf = ( zNear + zFar );
    inv_rl = ( 1.0f / ( right - left ) );
    inv_tb = ( 1.0f / ( top - bottom ) );
    inv_nf = ( 1.0f / ( zNear - zFar ) );
    vmathV4MakeFromElems( &result->col0, ( inv_rl + inv_rl ), 0.0f, 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col1, 0.0f, ( inv_tb + inv_tb ), 0.0f, 0.0f );
    vmathV4MakeFromElems( &result->col2, 0.0f, 0.0f, ( inv_nf + inv_nf ), 0.0f );
    vmathV4MakeFromElems( &result->col3, ( -sum_rl * inv_rl ), ( -sum_tb * inv_tb ), ( sum_nf * inv_nf ), 1.0f );
}

static inline void vmathM4Select( VmathMatrix4 *result, const VmathMatrix4 *mat0, const VmathMatrix4 *mat1, unsigned int select1 )
{
    vmathV4Select( &result->col0, &mat0->col0, &mat1->col0, select1 );
    vmathV4Select( &result->col1, &mat0->col1, &mat1->col1, select1 );
    vmathV4Select( &result->col2, &mat0->col2, &mat1->col2, select1 );
    vmathV4Select( &result->col3, &mat0->col3, &mat1->col3, select1 );
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathM4Print( const VmathMatrix4 *mat )
{
    VmathVector4 tmpV4_0, tmpV4_1, tmpV4_2, tmpV4_3;
    vmathM4GetRow( &tmpV4_0, mat, 0 );
    vmathV4Print( &tmpV4_0 );
    vmathM4GetRow( &tmpV4_1, mat, 1 );
    vmathV4Print( &tmpV4_1 );
    vmathM4GetRow( &tmpV4_2, mat, 2 );
    vmathV4Print( &tmpV4_2 );
    vmathM4GetRow( &tmpV4_3, mat, 3 );
    vmathV4Print( &tmpV4_3 );
}

static inline void vmathM4Prints( const VmathMatrix4 *mat, const char *name )
{
    printf("%s:\n", name);
    vmathM4Print( mat );
}

#endif

static inline void vmathT3Copy( VmathTransform3 *result, const VmathTransform3 *tfrm )
{
    vmathV3Copy( &result->col0, &tfrm->col0 );
    vmathV3Copy( &result->col1, &tfrm->col1 );
    vmathV3Copy( &result->col2, &tfrm->col2 );
    vmathV3Copy( &result->col3, &tfrm->col3 );
}

static inline void vmathT3MakeFromScalar( VmathTransform3 *result, float scalar )
{
    vmathV3MakeFromScalar( &result->col0, scalar );
    vmathV3MakeFromScalar( &result->col1, scalar );
    vmathV3MakeFromScalar( &result->col2, scalar );
    vmathV3MakeFromScalar( &result->col3, scalar );
}

static inline void vmathT3MakeFromCols( VmathTransform3 *result, const VmathVector3 *_col0, const VmathVector3 *_col1, const VmathVector3 *_col2, const VmathVector3 *_col3 )
{
    vmathV3Copy( &result->col0, _col0 );
    vmathV3Copy( &result->col1, _col1 );
    vmathV3Copy( &result->col2, _col2 );
    vmathV3Copy( &result->col3, _col3 );
}

static inline void vmathT3MakeFromM3V3( VmathTransform3 *result, const VmathMatrix3 *tfrm, const VmathVector3 *translateVec )
{
    vmathT3SetUpper3x3( result, tfrm );
    vmathT3SetTranslation( result, translateVec );
}

static inline void vmathT3MakeFromQV3( VmathTransform3 *result, const VmathQuat *unitQuat, const VmathVector3 *translateVec )
{
    VmathMatrix3 tmpM3_0;
    vmathM3MakeFromQ( &tmpM3_0, unitQuat );
    vmathT3SetUpper3x3( result, &tmpM3_0 );
    vmathT3SetTranslation( result, translateVec );
}

static inline void vmathT3SetCol0( VmathTransform3 *result, const VmathVector3 *_col0 )
{
    vmathV3Copy( &result->col0, _col0 );
}

static inline void vmathT3SetCol1( VmathTransform3 *result, const VmathVector3 *_col1 )
{
    vmathV3Copy( &result->col1, _col1 );
}

static inline void vmathT3SetCol2( VmathTransform3 *result, const VmathVector3 *_col2 )
{
    vmathV3Copy( &result->col2, _col2 );
}

static inline void vmathT3SetCol3( VmathTransform3 *result, const VmathVector3 *_col3 )
{
    vmathV3Copy( &result->col3, _col3 );
}

static inline void vmathT3SetCol( VmathTransform3 *result, int col, const VmathVector3 *vec )
{
    vmathV3Copy( (&result->col0 + col), vec );
}

static inline void vmathT3SetRow( VmathTransform3 *result, int row, const VmathVector4 *vec )
{
    vmathV3SetElem( &result->col0, row, vmathV4GetElem( vec, 0 ) );
    vmathV3SetElem( &result->col1, row, vmathV4GetElem( vec, 1 ) );
    vmathV3SetElem( &result->col2, row, vmathV4GetElem( vec, 2 ) );
    vmathV3SetElem( &result->col3, row, vmathV4GetElem( vec, 3 ) );
}

static inline void vmathT3SetElem( VmathTransform3 *result, int col, int row, float val )
{
    VmathVector3 tmpV3_0;
    vmathT3GetCol( &tmpV3_0, result, col );
    vmathV3SetElem( &tmpV3_0, row, val );
    vmathT3SetCol( result, col, &tmpV3_0 );
}

static inline float vmathT3GetElem( const VmathTransform3 *tfrm, int col, int row )
{
    VmathVector3 tmpV3_0;
    vmathT3GetCol( &tmpV3_0, tfrm, col );
    return vmathV3GetElem( &tmpV3_0, row );
}

static inline void vmathT3GetCol0( VmathVector3 *result, const VmathTransform3 *tfrm )
{
    vmathV3Copy( result, &tfrm->col0 );
}

static inline void vmathT3GetCol1( VmathVector3 *result, const VmathTransform3 *tfrm )
{
    vmathV3Copy( result, &tfrm->col1 );
}

static inline void vmathT3GetCol2( VmathVector3 *result, const VmathTransform3 *tfrm )
{
    vmathV3Copy( result, &tfrm->col2 );
}

static inline void vmathT3GetCol3( VmathVector3 *result, const VmathTransform3 *tfrm )
{
    vmathV3Copy( result, &tfrm->col3 );
}

static inline void vmathT3GetCol( VmathVector3 *result, const VmathTransform3 *tfrm, int col )
{
    vmathV3Copy( result, (&tfrm->col0 + col) );
}

static inline void vmathT3GetRow( VmathVector4 *result, const VmathTransform3 *tfrm, int row )
{
    vmathV4MakeFromElems( result, vmathV3GetElem( &tfrm->col0, row ), vmathV3GetElem( &tfrm->col1, row ), vmathV3GetElem( &tfrm->col2, row ), vmathV3GetElem( &tfrm->col3, row ) );
}

static inline void vmathT3Inverse( VmathTransform3 *result, const VmathTransform3 *tfrm )
{
    VmathVector3 tmp0, tmp1, tmp2, inv0, inv1, inv2, tmpV3_0, tmpV3_1, tmpV3_2, tmpV3_3, tmpV3_4, tmpV3_5;
    float detinv;
    vmathV3Cross( &tmp0, &tfrm->col1, &tfrm->col2 );
    vmathV3Cross( &tmp1, &tfrm->col2, &tfrm->col0 );
    vmathV3Cross( &tmp2, &tfrm->col0, &tfrm->col1 );
    detinv = ( 1.0f / vmathV3Dot( &tfrm->col2, &tmp2 ) );
    vmathV3MakeFromElems( &inv0, ( tmp0.x * detinv ), ( tmp1.x * detinv ), ( tmp2.x * detinv ) );
    vmathV3MakeFromElems( &inv1, ( tmp0.y * detinv ), ( tmp1.y * detinv ), ( tmp2.y * detinv ) );
    vmathV3MakeFromElems( &inv2, ( tmp0.z * detinv ), ( tmp1.z * detinv ), ( tmp2.z * detinv ) );
    vmathV3Copy( &result->col0, &inv0 );
    vmathV3Copy( &result->col1, &inv1 );
    vmathV3Copy( &result->col2, &inv2 );
    vmathV3ScalarMul( &tmpV3_0, &inv0, tfrm->col3.x );
    vmathV3ScalarMul( &tmpV3_1, &inv1, tfrm->col3.y );
    vmathV3ScalarMul( &tmpV3_2, &inv2, tfrm->col3.z );
    vmathV3Add( &tmpV3_3, &tmpV3_1, &tmpV3_2 );
    vmathV3Add( &tmpV3_4, &tmpV3_0, &tmpV3_3 );
    vmathV3Neg( &tmpV3_5, &tmpV3_4 );
    vmathV3Copy( &result->col3, &tmpV3_5 );
}

static inline void vmathT3OrthoInverse( VmathTransform3 *result, const VmathTransform3 *tfrm )
{
    VmathVector3 inv0, inv1, inv2, tmpV3_0, tmpV3_1, tmpV3_2, tmpV3_3, tmpV3_4, tmpV3_5;
    vmathV3MakeFromElems( &inv0, tfrm->col0.x, tfrm->col1.x, tfrm->col2.x );
    vmathV3MakeFromElems( &inv1, tfrm->col0.y, tfrm->col1.y, tfrm->col2.y );
    vmathV3MakeFromElems( &inv2, tfrm->col0.z, tfrm->col1.z, tfrm->col2.z );
    vmathV3Copy( &result->col0, &inv0 );
    vmathV3Copy( &result->col1, &inv1 );
    vmathV3Copy( &result->col2, &inv2 );
    vmathV3ScalarMul( &tmpV3_0, &inv0, tfrm->col3.x );
    vmathV3ScalarMul( &tmpV3_1, &inv1, tfrm->col3.y );
    vmathV3ScalarMul( &tmpV3_2, &inv2, tfrm->col3.z );
    vmathV3Add( &tmpV3_3, &tmpV3_1, &tmpV3_2 );
    vmathV3Add( &tmpV3_4, &tmpV3_0, &tmpV3_3 );
    vmathV3Neg( &tmpV3_5, &tmpV3_4 );
    vmathV3Copy( &result->col3, &tmpV3_5 );
}

static inline void vmathT3AbsPerElem( VmathTransform3 *result, const VmathTransform3 *tfrm )
{
    vmathV3AbsPerElem( &result->col0, &tfrm->col0 );
    vmathV3AbsPerElem( &result->col1, &tfrm->col1 );
    vmathV3AbsPerElem( &result->col2, &tfrm->col2 );
    vmathV3AbsPerElem( &result->col3, &tfrm->col3 );
}

static inline void vmathT3MulV3( VmathVector3 *result, const VmathTransform3 *tfrm, const VmathVector3 *vec )
{
    float tmpX, tmpY, tmpZ;
    tmpX = ( ( ( tfrm->col0.x * vec->x ) + ( tfrm->col1.x * vec->y ) ) + ( tfrm->col2.x * vec->z ) );
    tmpY = ( ( ( tfrm->col0.y * vec->x ) + ( tfrm->col1.y * vec->y ) ) + ( tfrm->col2.y * vec->z ) );
    tmpZ = ( ( ( tfrm->col0.z * vec->x ) + ( tfrm->col1.z * vec->y ) ) + ( tfrm->col2.z * vec->z ) );
    vmathV3MakeFromElems( result, tmpX, tmpY, tmpZ );
}

static inline void vmathT3MulP3( VmathPoint3 *result, const VmathTransform3 *tfrm, const VmathPoint3 *pnt )
{
    float tmpX, tmpY, tmpZ;
    tmpX = ( ( ( ( tfrm->col0.x * pnt->x ) + ( tfrm->col1.x * pnt->y ) ) + ( tfrm->col2.x * pnt->z ) ) + tfrm->col3.x );
    tmpY = ( ( ( ( tfrm->col0.y * pnt->x ) + ( tfrm->col1.y * pnt->y ) ) + ( tfrm->col2.y * pnt->z ) ) + tfrm->col3.y );
    tmpZ = ( ( ( ( tfrm->col0.z * pnt->x ) + ( tfrm->col1.z * pnt->y ) ) + ( tfrm->col2.z * pnt->z ) ) + tfrm->col3.z );
    vmathP3MakeFromElems( result, tmpX, tmpY, tmpZ );
}

static inline void vmathT3Mul( VmathTransform3 *result, const VmathTransform3 *tfrm0, const VmathTransform3 *tfrm1 )
{
    VmathTransform3 tmpResult;
    VmathPoint3 tmpP3_0, tmpP3_1;
    vmathT3MulV3( &tmpResult.col0, tfrm0, &tfrm1->col0 );
    vmathT3MulV3( &tmpResult.col1, tfrm0, &tfrm1->col1 );
    vmathT3MulV3( &tmpResult.col2, tfrm0, &tfrm1->col2 );
    vmathP3MakeFromV3( &tmpP3_0, &tfrm1->col3 );
    vmathT3MulP3( &tmpP3_1, tfrm0, &tmpP3_0 );
    vmathV3MakeFromP3( &tmpResult.col3, &tmpP3_1 );
    vmathT3Copy( result, &tmpResult );
}

static inline void vmathT3MulPerElem( VmathTransform3 *result, const VmathTransform3 *tfrm0, const VmathTransform3 *tfrm1 )
{
    vmathV3MulPerElem( &result->col0, &tfrm0->col0, &tfrm1->col0 );
    vmathV3MulPerElem( &result->col1, &tfrm0->col1, &tfrm1->col1 );
    vmathV3MulPerElem( &result->col2, &tfrm0->col2, &tfrm1->col2 );
    vmathV3MulPerElem( &result->col3, &tfrm0->col3, &tfrm1->col3 );
}

static inline void vmathT3MakeIdentity( VmathTransform3 *result )
{
    vmathV3MakeXAxis( &result->col0 );
    vmathV3MakeYAxis( &result->col1 );
    vmathV3MakeZAxis( &result->col2 );
    vmathV3MakeFromScalar( &result->col3, 0.0f );
}

static inline void vmathT3SetUpper3x3( VmathTransform3 *result, const VmathMatrix3 *tfrm )
{
    vmathV3Copy( &result->col0, &tfrm->col0 );
    vmathV3Copy( &result->col1, &tfrm->col1 );
    vmathV3Copy( &result->col2, &tfrm->col2 );
}

static inline void vmathT3GetUpper3x3( VmathMatrix3 *result, const VmathTransform3 *tfrm )
{
    vmathM3MakeFromCols( result, &tfrm->col0, &tfrm->col1, &tfrm->col2 );
}

static inline void vmathT3SetTranslation( VmathTransform3 *result, const VmathVector3 *translateVec )
{
    vmathV3Copy( &result->col3, translateVec );
}

static inline void vmathT3GetTranslation( VmathVector3 *result, const VmathTransform3 *tfrm )
{
    vmathV3Copy( result, &tfrm->col3 );
}

static inline void vmathT3MakeRotationX( VmathTransform3 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV3MakeXAxis( &result->col0 );
    vmathV3MakeFromElems( &result->col1, 0.0f, c, s );
    vmathV3MakeFromElems( &result->col2, 0.0f, -s, c );
    vmathV3MakeFromScalar( &result->col3, 0.0f );
}

static inline void vmathT3MakeRotationY( VmathTransform3 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV3MakeFromElems( &result->col0, c, 0.0f, -s );
    vmathV3MakeYAxis( &result->col1 );
    vmathV3MakeFromElems( &result->col2, s, 0.0f, c );
    vmathV3MakeFromScalar( &result->col3, 0.0f );
}

static inline void vmathT3MakeRotationZ( VmathTransform3 *result, float radians )
{
    float s, c;
    s = sinf( radians );
    c = cosf( radians );
    vmathV3MakeFromElems( &result->col0, c, s, 0.0f );
    vmathV3MakeFromElems( &result->col1, -s, c, 0.0f );
    vmathV3MakeZAxis( &result->col2 );
    vmathV3MakeFromScalar( &result->col3, 0.0f );
}

static inline void vmathT3MakeRotationZYX( VmathTransform3 *result, const VmathVector3 *radiansXYZ )
{
    float sX, cX, sY, cY, sZ, cZ, tmp0, tmp1;
    sX = sinf( radiansXYZ->x );
    cX = cosf( radiansXYZ->x );
    sY = sinf( radiansXYZ->y );
    cY = cosf( radiansXYZ->y );
    sZ = sinf( radiansXYZ->z );
    cZ = cosf( radiansXYZ->z );
    tmp0 = ( cZ * sY );
    tmp1 = ( sZ * sY );
    vmathV3MakeFromElems( &result->col0, ( cZ * cY ), ( sZ * cY ), -sY );
    vmathV3MakeFromElems( &result->col1, ( ( tmp0 * sX ) - ( sZ * cX ) ), ( ( tmp1 * sX ) + ( cZ * cX ) ), ( cY * sX ) );
    vmathV3MakeFromElems( &result->col2, ( ( tmp0 * cX ) + ( sZ * sX ) ), ( ( tmp1 * cX ) - ( cZ * sX ) ), ( cY * cX ) );
    vmathV3MakeFromScalar( &result->col3, 0.0f );
}

static inline void vmathT3MakeRotationAxis( VmathTransform3 *result, float radians, const VmathVector3 *unitVec )
{
    VmathMatrix3 tmpM3_0;
    VmathVector3 tmpV3_0;
    vmathM3MakeRotationAxis( &tmpM3_0, radians, unitVec );
    vmathV3MakeFromScalar( &tmpV3_0, 0.0f );
    vmathT3MakeFromM3V3( result, &tmpM3_0, &tmpV3_0 );
}

static inline void vmathT3MakeRotationQ( VmathTransform3 *result, const VmathQuat *unitQuat )
{
    VmathMatrix3 tmpM3_0;
    VmathVector3 tmpV3_0;
    vmathM3MakeFromQ( &tmpM3_0, unitQuat );
    vmathV3MakeFromScalar( &tmpV3_0, 0.0f );
    vmathT3MakeFromM3V3( result, &tmpM3_0, &tmpV3_0 );
}

static inline void vmathT3MakeScale( VmathTransform3 *result, const VmathVector3 *scaleVec )
{
    vmathV3MakeFromElems( &result->col0, scaleVec->x, 0.0f, 0.0f );
    vmathV3MakeFromElems( &result->col1, 0.0f, scaleVec->y, 0.0f );
    vmathV3MakeFromElems( &result->col2, 0.0f, 0.0f, scaleVec->z );
    vmathV3MakeFromScalar( &result->col3, 0.0f );
}

static inline void vmathT3AppendScale( VmathTransform3 *result, const VmathTransform3 *tfrm, const VmathVector3 *scaleVec )
{
    vmathV3ScalarMul( &result->col0, &tfrm->col0, vmathV3GetX( scaleVec ) );
    vmathV3ScalarMul( &result->col1, &tfrm->col1, vmathV3GetY( scaleVec ) );
    vmathV3ScalarMul( &result->col2, &tfrm->col2, vmathV3GetZ( scaleVec ) );
    vmathV3Copy( &result->col3, &tfrm->col3 );
}

static inline void vmathT3PrependScale( VmathTransform3 *result, const VmathVector3 *scaleVec, const VmathTransform3 *tfrm )
{
    vmathV3MulPerElem( &result->col0, &tfrm->col0, scaleVec );
    vmathV3MulPerElem( &result->col1, &tfrm->col1, scaleVec );
    vmathV3MulPerElem( &result->col2, &tfrm->col2, scaleVec );
    vmathV3MulPerElem( &result->col3, &tfrm->col3, scaleVec );
}

static inline void vmathT3MakeTranslation( VmathTransform3 *result, const VmathVector3 *translateVec )
{
    vmathV3MakeXAxis( &result->col0 );
    vmathV3MakeYAxis( &result->col1 );
    vmathV3MakeZAxis( &result->col2 );
    vmathV3Copy( &result->col3, translateVec );
}

static inline void vmathT3Select( VmathTransform3 *result, const VmathTransform3 *tfrm0, const VmathTransform3 *tfrm1, unsigned int select1 )
{
    vmathV3Select( &result->col0, &tfrm0->col0, &tfrm1->col0, select1 );
    vmathV3Select( &result->col1, &tfrm0->col1, &tfrm1->col1, select1 );
    vmathV3Select( &result->col2, &tfrm0->col2, &tfrm1->col2, select1 );
    vmathV3Select( &result->col3, &tfrm0->col3, &tfrm1->col3, select1 );
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathT3Print( const VmathTransform3 *tfrm )
{
    VmathVector4 tmpV4_0, tmpV4_1, tmpV4_2;
    vmathT3GetRow( &tmpV4_0, tfrm, 0 );
    vmathV4Print( &tmpV4_0 );
    vmathT3GetRow( &tmpV4_1, tfrm, 1 );
    vmathV4Print( &tmpV4_1 );
    vmathT3GetRow( &tmpV4_2, tfrm, 2 );
    vmathV4Print( &tmpV4_2 );
}

static inline void vmathT3Prints( const VmathTransform3 *tfrm, const char *name )
{
    printf("%s:\n", name);
    vmathT3Print( tfrm );
}

#endif

static inline void vmathQMakeFromM3( VmathQuat *result, const VmathMatrix3 *tfrm )
{
    float trace, radicand, scale, xx, yx, zx, xy, yy, zy, xz, yz, zz, tmpx, tmpy, tmpz, tmpw, qx, qy, qz, qw;
    int negTrace, ZgtX, ZgtY, YgtX;
    int largestXorY, largestYorZ, largestZorX;

    xx = tfrm->col0.x;
    yx = tfrm->col0.y;
    zx = tfrm->col0.z;
    xy = tfrm->col1.x;
    yy = tfrm->col1.y;
    zy = tfrm->col1.z;
    xz = tfrm->col2.x;
    yz = tfrm->col2.y;
    zz = tfrm->col2.z;

    trace = ( ( xx + yy ) + zz );

    negTrace = ( trace < 0.0f );
    ZgtX = zz > xx;
    ZgtY = zz > yy;
    YgtX = yy > xx;
    largestXorY = ( !ZgtX || !ZgtY ) && negTrace;
    largestYorZ = ( YgtX || ZgtX ) && negTrace;
    largestZorX = ( ZgtY || !YgtX ) && negTrace;
    
    if ( largestXorY )
    {
        zz = -zz;
        xy = -xy;
    }
    if ( largestYorZ )
    {
        xx = -xx;
        yz = -yz;
    }
    if ( largestZorX )
    {
        yy = -yy;
        zx = -zx;
    }

    radicand = ( ( ( xx + yy ) + zz ) + 1.0f );
    scale = ( 0.5f * ( 1.0f / sqrtf( radicand ) ) );

    tmpx = ( ( zy - yz ) * scale );
    tmpy = ( ( xz - zx ) * scale );
    tmpz = ( ( yx - xy ) * scale );
    tmpw = ( radicand * scale );
    qx = tmpx;
    qy = tmpy;
    qz = tmpz;
    qw = tmpw;

    if ( largestXorY )
    {
        qx = tmpw;
        qy = tmpz;
        qz = tmpy;
        qw = tmpx;
    }
    if ( largestYorZ )
    {
        tmpx = qx;
        tmpz = qz;
        qx = qy;
        qy = tmpx;
        qz = qw;
        qw = tmpz;
    }

    result->x = qx;
    result->y = qy;
    result->z = qz;
    result->w = qw;
}

static inline void vmathV3Outer( VmathMatrix3 *result, const VmathVector3 *tfrm0, const VmathVector3 *tfrm1 )
{
    vmathV3ScalarMul( &result->col0, tfrm0, vmathV3GetX( tfrm1 ) );
    vmathV3ScalarMul( &result->col1, tfrm0, vmathV3GetY( tfrm1 ) );
    vmathV3ScalarMul( &result->col2, tfrm0, vmathV3GetZ( tfrm1 ) );
}

static inline void vmathV4Outer( VmathMatrix4 *result, const VmathVector4 *tfrm0, const VmathVector4 *tfrm1 )
{
    vmathV4ScalarMul( &result->col0, tfrm0, vmathV4GetX( tfrm1 ) );
    vmathV4ScalarMul( &result->col1, tfrm0, vmathV4GetY( tfrm1 ) );
    vmathV4ScalarMul( &result->col2, tfrm0, vmathV4GetZ( tfrm1 ) );
    vmathV4ScalarMul( &result->col3, tfrm0, vmathV4GetW( tfrm1 ) );
}

static inline void vmathV3RowMul( VmathVector3 *result, const VmathVector3 *vec, const VmathMatrix3 *mat )
{
    float tmpX, tmpY, tmpZ;
    tmpX = ( ( ( vec->x * mat->col0.x ) + ( vec->y * mat->col0.y ) ) + ( vec->z * mat->col0.z ) );
    tmpY = ( ( ( vec->x * mat->col1.x ) + ( vec->y * mat->col1.y ) ) + ( vec->z * mat->col1.z ) );
    tmpZ = ( ( ( vec->x * mat->col2.x ) + ( vec->y * mat->col2.y ) ) + ( vec->z * mat->col2.z ) );
    vmathV3MakeFromElems( result, tmpX, tmpY, tmpZ );
}

static inline void vmathV3CrossMatrix( VmathMatrix3 *result, const VmathVector3 *vec )
{
    vmathV3MakeFromElems( &result->col0, 0.0f, vec->z, -vec->y );
    vmathV3MakeFromElems( &result->col1, -vec->z, 0.0f, vec->x );
    vmathV3MakeFromElems( &result->col2, vec->y, -vec->x, 0.0f );
}

static inline void vmathV3CrossMatrixMul( VmathMatrix3 *result, const VmathVector3 *vec, const VmathMatrix3 *mat )
{
    VmathVector3 tmpV3_0, tmpV3_1, tmpV3_2;
    vmathV3Cross( &tmpV3_0, vec, &mat->col0 );
    vmathV3Cross( &tmpV3_1, vec, &mat->col1 );
    vmathV3Cross( &tmpV3_2, vec, &mat->col2 );
    vmathM3MakeFromCols( result, &tmpV3_0, &tmpV3_1, &tmpV3_2 );
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#endif

#endif


/*-----------------------------------------------------------------------------
 * Constants
 */
#define _VECTORMATH_SLERP_TOL 0.999f

/*-----------------------------------------------------------------------------
 * Definitions
 */
#ifndef _VECTORMATH_INTERNAL_FUNCTIONS
#define _VECTORMATH_INTERNAL_FUNCTIONS

#endif

static inline VmathVector3 vmathV3MakeFromElems_V( float _x, float _y, float _z )
{
    VmathVector3 result;
    vmathV3MakeFromElems(&result, _x, _y, _z);
    return result;
}

static inline VmathVector3 vmathV3MakeFromP3_V( VmathPoint3 pnt )
{
    VmathVector3 result;
    vmathV3MakeFromP3(&result, &pnt);
    return result;
}

static inline VmathVector3 vmathV3MakeFromScalar_V( float scalar )
{
    VmathVector3 result;
    vmathV3MakeFromScalar(&result, scalar);
    return result;
}

static inline VmathVector3 vmathV3MakeXAxis_V( )
{
    VmathVector3 result;
    vmathV3MakeXAxis(&result);
    return result;
}

static inline VmathVector3 vmathV3MakeYAxis_V( )
{
    VmathVector3 result;
    vmathV3MakeYAxis(&result);
    return result;
}

static inline VmathVector3 vmathV3MakeZAxis_V( )
{
    VmathVector3 result;
    vmathV3MakeZAxis(&result);
    return result;
}

static inline VmathVector3 vmathV3Lerp_V( float t, VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3Lerp(&result, t, &vec0, &vec1);
    return result;
}

static inline VmathVector3 vmathV3Slerp_V( float t, VmathVector3 unitVec0, VmathVector3 unitVec1 )
{
    VmathVector3 result;
    vmathV3Slerp(&result, t, &unitVec0, &unitVec1);
    return result;
}

static inline void vmathV3SetX_V( VmathVector3 *result, float _x )
{
    vmathV3SetX(result, _x);
}

static inline float vmathV3GetX_V( VmathVector3 vec )
{
    return vmathV3GetX(&vec);
}

static inline void vmathV3SetY_V( VmathVector3 *result, float _y )
{
    vmathV3SetY(result, _y);
}

static inline float vmathV3GetY_V( VmathVector3 vec )
{
    return vmathV3GetY(&vec);
}

static inline void vmathV3SetZ_V( VmathVector3 *result, float _z )
{
    vmathV3SetZ(result, _z);
}

static inline float vmathV3GetZ_V( VmathVector3 vec )
{
    return vmathV3GetZ(&vec);
}

static inline void vmathV3SetElem_V( VmathVector3 *result, int idx, float value )
{
    vmathV3SetElem(result, idx, value);
}

static inline float vmathV3GetElem_V( VmathVector3 vec, int idx )
{
    return vmathV3GetElem(&vec, idx);
}

static inline VmathVector3 vmathV3Add_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3Add(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector3 vmathV3Sub_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3Sub(&result, &vec0, &vec1);
    return result;
}

static inline VmathPoint3 vmathV3AddP3_V( VmathVector3 vec, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathV3AddP3(&result, &vec, &pnt1);
    return result;
}

static inline VmathVector3 vmathV3ScalarMul_V( VmathVector3 vec, float scalar )
{
    VmathVector3 result;
    vmathV3ScalarMul(&result, &vec, scalar);
    return result;
}

static inline VmathVector3 vmathV3ScalarDiv_V( VmathVector3 vec, float scalar )
{
    VmathVector3 result;
    vmathV3ScalarDiv(&result, &vec, scalar);
    return result;
}

static inline VmathVector3 vmathV3Neg_V( VmathVector3 vec )
{
    VmathVector3 result;
    vmathV3Neg(&result, &vec);
    return result;
}

static inline VmathVector3 vmathV3MulPerElem_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3MulPerElem(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector3 vmathV3DivPerElem_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3DivPerElem(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector3 vmathV3RecipPerElem_V( VmathVector3 vec )
{
    VmathVector3 result;
    vmathV3RecipPerElem(&result, &vec);
    return result;
}

static inline VmathVector3 vmathV3SqrtPerElem_V( VmathVector3 vec )
{
    VmathVector3 result;
    vmathV3SqrtPerElem(&result, &vec);
    return result;
}

static inline VmathVector3 vmathV3RsqrtPerElem_V( VmathVector3 vec )
{
    VmathVector3 result;
    vmathV3RsqrtPerElem(&result, &vec);
    return result;
}

static inline VmathVector3 vmathV3AbsPerElem_V( VmathVector3 vec )
{
    VmathVector3 result;
    vmathV3AbsPerElem(&result, &vec);
    return result;
}

static inline VmathVector3 vmathV3CopySignPerElem_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3CopySignPerElem(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector3 vmathV3MaxPerElem_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3MaxPerElem(&result, &vec0, &vec1);
    return result;
}

static inline float vmathV3MaxElem_V( VmathVector3 vec )
{
    return vmathV3MaxElem(&vec);
}

static inline VmathVector3 vmathV3MinPerElem_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3MinPerElem(&result, &vec0, &vec1);
    return result;
}

static inline float vmathV3MinElem_V( VmathVector3 vec )
{
    return vmathV3MinElem(&vec);
}

static inline float vmathV3Sum_V( VmathVector3 vec )
{
    return vmathV3Sum(&vec);
}

static inline float vmathV3Dot_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    return vmathV3Dot(&vec0, &vec1);
}

static inline float vmathV3LengthSqr_V( VmathVector3 vec )
{
    return vmathV3LengthSqr(&vec);
}

static inline float vmathV3Length_V( VmathVector3 vec )
{
    return vmathV3Length(&vec);
}

static inline VmathVector3 vmathV3Normalize_V( VmathVector3 vec )
{
    VmathVector3 result;
    vmathV3Normalize(&result, &vec);
    return result;
}

static inline VmathVector3 vmathV3Cross_V( VmathVector3 vec0, VmathVector3 vec1 )
{
    VmathVector3 result;
    vmathV3Cross(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector3 vmathV3Select_V( VmathVector3 vec0, VmathVector3 vec1, unsigned int select1 )
{
    VmathVector3 result;
    vmathV3Select(&result, &vec0, &vec1, select1);
    return result;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathV3Print_V( VmathVector3 vec )
{
    vmathV3Print(&vec);
}

static inline void vmathV3Prints_V( VmathVector3 vec, const char *name )
{
    vmathV3Prints(&vec, name);
}

#endif

static inline VmathVector4 vmathV4MakeFromElems_V( float _x, float _y, float _z, float _w )
{
    VmathVector4 result;
    vmathV4MakeFromElems(&result, _x, _y, _z, _w);
    return result;
}

static inline VmathVector4 vmathV4MakeFromV3Scalar_V( VmathVector3 xyz, float _w )
{
    VmathVector4 result;
    vmathV4MakeFromV3Scalar(&result, &xyz, _w);
    return result;
}

static inline VmathVector4 vmathV4MakeFromV3_V( VmathVector3 vec )
{
    VmathVector4 result;
    vmathV4MakeFromV3(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4MakeFromP3_V( VmathPoint3 pnt )
{
    VmathVector4 result;
    vmathV4MakeFromP3(&result, &pnt);
    return result;
}

static inline VmathVector4 vmathV4MakeFromQ_V( VmathQuat quat )
{
    VmathVector4 result;
    vmathV4MakeFromQ(&result, &quat);
    return result;
}

static inline VmathVector4 vmathV4MakeFromScalar_V( float scalar )
{
    VmathVector4 result;
    vmathV4MakeFromScalar(&result, scalar);
    return result;
}

static inline VmathVector4 vmathV4MakeXAxis_V( )
{
    VmathVector4 result;
    vmathV4MakeXAxis(&result);
    return result;
}

static inline VmathVector4 vmathV4MakeYAxis_V( )
{
    VmathVector4 result;
    vmathV4MakeYAxis(&result);
    return result;
}

static inline VmathVector4 vmathV4MakeZAxis_V( )
{
    VmathVector4 result;
    vmathV4MakeZAxis(&result);
    return result;
}

static inline VmathVector4 vmathV4MakeWAxis_V( )
{
    VmathVector4 result;
    vmathV4MakeWAxis(&result);
    return result;
}

static inline VmathVector4 vmathV4Lerp_V( float t, VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4Lerp(&result, t, &vec0, &vec1);
    return result;
}

static inline VmathVector4 vmathV4Slerp_V( float t, VmathVector4 unitVec0, VmathVector4 unitVec1 )
{
    VmathVector4 result;
    vmathV4Slerp(&result, t, &unitVec0, &unitVec1);
    return result;
}

static inline void vmathV4SetXYZ_V( VmathVector4 *result, VmathVector3 vec )
{
    vmathV4SetXYZ(result, &vec);
}

static inline VmathVector3 vmathV4GetXYZ_V( VmathVector4 vec )
{
    VmathVector3 result;
    vmathV4GetXYZ(&result, &vec);
    return result;
}

static inline void vmathV4SetX_V( VmathVector4 *result, float _x )
{
    vmathV4SetX(result, _x);
}

static inline float vmathV4GetX_V( VmathVector4 vec )
{
    return vmathV4GetX(&vec);
}

static inline void vmathV4SetY_V( VmathVector4 *result, float _y )
{
    vmathV4SetY(result, _y);
}

static inline float vmathV4GetY_V( VmathVector4 vec )
{
    return vmathV4GetY(&vec);
}

static inline void vmathV4SetZ_V( VmathVector4 *result, float _z )
{
    vmathV4SetZ(result, _z);
}

static inline float vmathV4GetZ_V( VmathVector4 vec )
{
    return vmathV4GetZ(&vec);
}

static inline void vmathV4SetW_V( VmathVector4 *result, float _w )
{
    vmathV4SetW(result, _w);
}

static inline float vmathV4GetW_V( VmathVector4 vec )
{
    return vmathV4GetW(&vec);
}

static inline void vmathV4SetElem_V( VmathVector4 *result, int idx, float value )
{
    vmathV4SetElem(result, idx, value);
}

static inline float vmathV4GetElem_V( VmathVector4 vec, int idx )
{
    return vmathV4GetElem(&vec, idx);
}

static inline VmathVector4 vmathV4Add_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4Add(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector4 vmathV4Sub_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4Sub(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector4 vmathV4ScalarMul_V( VmathVector4 vec, float scalar )
{
    VmathVector4 result;
    vmathV4ScalarMul(&result, &vec, scalar);
    return result;
}

static inline VmathVector4 vmathV4ScalarDiv_V( VmathVector4 vec, float scalar )
{
    VmathVector4 result;
    vmathV4ScalarDiv(&result, &vec, scalar);
    return result;
}

static inline VmathVector4 vmathV4Neg_V( VmathVector4 vec )
{
    VmathVector4 result;
    vmathV4Neg(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4MulPerElem_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4MulPerElem(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector4 vmathV4DivPerElem_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4DivPerElem(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector4 vmathV4RecipPerElem_V( VmathVector4 vec )
{
    VmathVector4 result;
    vmathV4RecipPerElem(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4SqrtPerElem_V( VmathVector4 vec )
{
    VmathVector4 result;
    vmathV4SqrtPerElem(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4RsqrtPerElem_V( VmathVector4 vec )
{
    VmathVector4 result;
    vmathV4RsqrtPerElem(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4AbsPerElem_V( VmathVector4 vec )
{
    VmathVector4 result;
    vmathV4AbsPerElem(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4CopySignPerElem_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4CopySignPerElem(&result, &vec0, &vec1);
    return result;
}

static inline VmathVector4 vmathV4MaxPerElem_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4MaxPerElem(&result, &vec0, &vec1);
    return result;
}

static inline float vmathV4MaxElem_V( VmathVector4 vec )
{
    return vmathV4MaxElem(&vec);
}

static inline VmathVector4 vmathV4MinPerElem_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    VmathVector4 result;
    vmathV4MinPerElem(&result, &vec0, &vec1);
    return result;
}

static inline float vmathV4MinElem_V( VmathVector4 vec )
{
    return vmathV4MinElem(&vec);
}

static inline float vmathV4Sum_V( VmathVector4 vec )
{
    return vmathV4Sum(&vec);
}

static inline float vmathV4Dot_V( VmathVector4 vec0, VmathVector4 vec1 )
{
    return vmathV4Dot(&vec0, &vec1);
}

static inline float vmathV4LengthSqr_V( VmathVector4 vec )
{
    return vmathV4LengthSqr(&vec);
}

static inline float vmathV4Length_V( VmathVector4 vec )
{
    return vmathV4Length(&vec);
}

static inline VmathVector4 vmathV4Normalize_V( VmathVector4 vec )
{
    VmathVector4 result;
    vmathV4Normalize(&result, &vec);
    return result;
}

static inline VmathVector4 vmathV4Select_V( VmathVector4 vec0, VmathVector4 vec1, unsigned int select1 )
{
    VmathVector4 result;
    vmathV4Select(&result, &vec0, &vec1, select1);
    return result;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathV4Print_V( VmathVector4 vec )
{
    vmathV4Print(&vec);
}

static inline void vmathV4Prints_V( VmathVector4 vec, const char *name )
{
    vmathV4Prints(&vec, name);
}

#endif

static inline VmathPoint3 vmathP3MakeFromElems_V( float _x, float _y, float _z )
{
    VmathPoint3 result;
    vmathP3MakeFromElems(&result, _x, _y, _z);
    return result;
}

static inline VmathPoint3 vmathP3MakeFromV3_V( VmathVector3 vec )
{
    VmathPoint3 result;
    vmathP3MakeFromV3(&result, &vec);
    return result;
}

static inline VmathPoint3 vmathP3MakeFromScalar_V( float scalar )
{
    VmathPoint3 result;
    vmathP3MakeFromScalar(&result, scalar);
    return result;
}

static inline VmathPoint3 vmathP3Lerp_V( float t, VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathP3Lerp(&result, t, &pnt0, &pnt1);
    return result;
}

static inline void vmathP3SetX_V( VmathPoint3 *result, float _x )
{
    vmathP3SetX(result, _x);
}

static inline float vmathP3GetX_V( VmathPoint3 pnt )
{
    return vmathP3GetX(&pnt);
}

static inline void vmathP3SetY_V( VmathPoint3 *result, float _y )
{
    vmathP3SetY(result, _y);
}

static inline float vmathP3GetY_V( VmathPoint3 pnt )
{
    return vmathP3GetY(&pnt);
}

static inline void vmathP3SetZ_V( VmathPoint3 *result, float _z )
{
    vmathP3SetZ(result, _z);
}

static inline float vmathP3GetZ_V( VmathPoint3 pnt )
{
    return vmathP3GetZ(&pnt);
}

static inline void vmathP3SetElem_V( VmathPoint3 *result, int idx, float value )
{
    vmathP3SetElem(result, idx, value);
}

static inline float vmathP3GetElem_V( VmathPoint3 pnt, int idx )
{
    return vmathP3GetElem(&pnt, idx);
}

static inline VmathVector3 vmathP3Sub_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathVector3 result;
    vmathP3Sub(&result, &pnt0, &pnt1);
    return result;
}

static inline VmathPoint3 vmathP3AddV3_V( VmathPoint3 pnt, VmathVector3 vec1 )
{
    VmathPoint3 result;
    vmathP3AddV3(&result, &pnt, &vec1);
    return result;
}

static inline VmathPoint3 vmathP3SubV3_V( VmathPoint3 pnt, VmathVector3 vec1 )
{
    VmathPoint3 result;
    vmathP3SubV3(&result, &pnt, &vec1);
    return result;
}

static inline VmathPoint3 vmathP3MulPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathP3MulPerElem(&result, &pnt0, &pnt1);
    return result;
}

static inline VmathPoint3 vmathP3DivPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathP3DivPerElem(&result, &pnt0, &pnt1);
    return result;
}

static inline VmathPoint3 vmathP3RecipPerElem_V( VmathPoint3 pnt )
{
    VmathPoint3 result;
    vmathP3RecipPerElem(&result, &pnt);
    return result;
}

static inline VmathPoint3 vmathP3SqrtPerElem_V( VmathPoint3 pnt )
{
    VmathPoint3 result;
    vmathP3SqrtPerElem(&result, &pnt);
    return result;
}

static inline VmathPoint3 vmathP3RsqrtPerElem_V( VmathPoint3 pnt )
{
    VmathPoint3 result;
    vmathP3RsqrtPerElem(&result, &pnt);
    return result;
}

static inline VmathPoint3 vmathP3AbsPerElem_V( VmathPoint3 pnt )
{
    VmathPoint3 result;
    vmathP3AbsPerElem(&result, &pnt);
    return result;
}

static inline VmathPoint3 vmathP3CopySignPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathP3CopySignPerElem(&result, &pnt0, &pnt1);
    return result;
}

static inline VmathPoint3 vmathP3MaxPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathP3MaxPerElem(&result, &pnt0, &pnt1);
    return result;
}

static inline float vmathP3MaxElem_V( VmathPoint3 pnt )
{
    return vmathP3MaxElem(&pnt);
}

static inline VmathPoint3 vmathP3MinPerElem_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    VmathPoint3 result;
    vmathP3MinPerElem(&result, &pnt0, &pnt1);
    return result;
}

static inline float vmathP3MinElem_V( VmathPoint3 pnt )
{
    return vmathP3MinElem(&pnt);
}

static inline float vmathP3Sum_V( VmathPoint3 pnt )
{
    return vmathP3Sum(&pnt);
}

static inline VmathPoint3 vmathP3Scale_V( VmathPoint3 pnt, float scaleVal )
{
    VmathPoint3 result;
    vmathP3Scale(&result, &pnt, scaleVal);
    return result;
}

static inline VmathPoint3 vmathP3NonUniformScale_V( VmathPoint3 pnt, VmathVector3 scaleVec )
{
    VmathPoint3 result;
    vmathP3NonUniformScale(&result, &pnt, &scaleVec);
    return result;
}

static inline float vmathP3Projection_V( VmathPoint3 pnt, VmathVector3 unitVec )
{
    return vmathP3Projection(&pnt, &unitVec);
}

static inline float vmathP3DistSqrFromOrigin_V( VmathPoint3 pnt )
{
    return vmathP3DistSqrFromOrigin(&pnt);
}

static inline float vmathP3DistFromOrigin_V( VmathPoint3 pnt )
{
    return vmathP3DistFromOrigin(&pnt);
}

static inline float vmathP3DistSqr_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    return vmathP3DistSqr(&pnt0, &pnt1);
}

static inline float vmathP3Dist_V( VmathPoint3 pnt0, VmathPoint3 pnt1 )
{
    return vmathP3Dist(&pnt0, &pnt1);
}

static inline VmathPoint3 vmathP3Select_V( VmathPoint3 pnt0, VmathPoint3 pnt1, unsigned int select1 )
{
    VmathPoint3 result;
    vmathP3Select(&result, &pnt0, &pnt1, select1);
    return result;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathP3Print_V( VmathPoint3 pnt )
{
    vmathP3Print(&pnt);
}

static inline void vmathP3Prints_V( VmathPoint3 pnt, const char *name )
{
    vmathP3Prints(&pnt, name);
}

#endif

/*-----------------------------------------------------------------------------
 * Constants
 */
#define _VECTORMATH_PI_OVER_2 1.570796327f

/*-----------------------------------------------------------------------------
 * Definitions
 */
static inline VmathMatrix3 vmathM3MakeFromScalar_V( float scalar )
{
    VmathMatrix3 result;
    vmathM3MakeFromScalar(&result, scalar);
    return result;
}

static inline VmathMatrix3 vmathM3MakeFromQ_V( VmathQuat unitQuat )
{
    VmathMatrix3 result;
    vmathM3MakeFromQ(&result, &unitQuat);
    return result;
}

static inline VmathMatrix3 vmathM3MakeFromCols_V( VmathVector3 _col0, VmathVector3 _col1, VmathVector3 _col2 )
{
    VmathMatrix3 result;
    vmathM3MakeFromCols(&result, &_col0, &_col1, &_col2);
    return result;
}

static inline void vmathM3SetCol0_V( VmathMatrix3 *result, VmathVector3 _col0 )
{
    vmathM3SetCol0(result, &_col0);
}

static inline void vmathM3SetCol1_V( VmathMatrix3 *result, VmathVector3 _col1 )
{
    vmathM3SetCol1(result, &_col1);
}

static inline void vmathM3SetCol2_V( VmathMatrix3 *result, VmathVector3 _col2 )
{
    vmathM3SetCol2(result, &_col2);
}

static inline void vmathM3SetCol_V( VmathMatrix3 *result, int col, VmathVector3 vec )
{
    vmathM3SetCol(result, col, &vec);
}

static inline void vmathM3SetRow_V( VmathMatrix3 *result, int row, VmathVector3 vec )
{
    vmathM3SetRow(result, row, &vec);
}

static inline void vmathM3SetElem_V( VmathMatrix3 *result, int col, int row, float val )
{
    vmathM3SetElem(result, col, row, val);
}

static inline float vmathM3GetElem_V( VmathMatrix3 mat, int col, int row )
{
    return vmathM3GetElem(&mat, col, row);
}

static inline VmathVector3 vmathM3GetCol0_V( VmathMatrix3 mat )
{
    VmathVector3 result;
    vmathM3GetCol0(&result, &mat);
    return result;
}

static inline VmathVector3 vmathM3GetCol1_V( VmathMatrix3 mat )
{
    VmathVector3 result;
    vmathM3GetCol1(&result, &mat);
    return result;
}

static inline VmathVector3 vmathM3GetCol2_V( VmathMatrix3 mat )
{
    VmathVector3 result;
    vmathM3GetCol2(&result, &mat);
    return result;
}

static inline VmathVector3 vmathM3GetCol_V( VmathMatrix3 mat, int col )
{
    VmathVector3 result;
    vmathM3GetCol(&result, &mat, col);
    return result;
}

static inline VmathVector3 vmathM3GetRow_V( VmathMatrix3 mat, int row )
{
    VmathVector3 result;
    vmathM3GetRow(&result, &mat, row);
    return result;
}

static inline VmathMatrix3 vmathM3Transpose_V( VmathMatrix3 mat )
{
    VmathMatrix3 result;
    vmathM3Transpose(&result, &mat);
    return result;
}

static inline VmathMatrix3 vmathM3Inverse_V( VmathMatrix3 mat )
{
    VmathMatrix3 result;
    vmathM3Inverse(&result, &mat);
    return result;
}

static inline float vmathM3Determinant_V( VmathMatrix3 mat )
{
    return vmathM3Determinant(&mat);
}

static inline VmathMatrix3 vmathM3Add_V( VmathMatrix3 mat0, VmathMatrix3 mat1 )
{
    VmathMatrix3 result;
    vmathM3Add(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix3 vmathM3Sub_V( VmathMatrix3 mat0, VmathMatrix3 mat1 )
{
    VmathMatrix3 result;
    vmathM3Sub(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix3 vmathM3Neg_V( VmathMatrix3 mat )
{
    VmathMatrix3 result;
    vmathM3Neg(&result, &mat);
    return result;
}

static inline VmathMatrix3 vmathM3AbsPerElem_V( VmathMatrix3 mat )
{
    VmathMatrix3 result;
    vmathM3AbsPerElem(&result, &mat);
    return result;
}

static inline VmathMatrix3 vmathM3ScalarMul_V( VmathMatrix3 mat, float scalar )
{
    VmathMatrix3 result;
    vmathM3ScalarMul(&result, &mat, scalar);
    return result;
}

static inline VmathVector3 vmathM3MulV3_V( VmathMatrix3 mat, VmathVector3 vec )
{
    VmathVector3 result;
    vmathM3MulV3(&result, &mat, &vec);
    return result;
}

static inline VmathMatrix3 vmathM3Mul_V( VmathMatrix3 mat0, VmathMatrix3 mat1 )
{
    VmathMatrix3 result;
    vmathM3Mul(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix3 vmathM3MulPerElem_V( VmathMatrix3 mat0, VmathMatrix3 mat1 )
{
    VmathMatrix3 result;
    vmathM3MulPerElem(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix3 vmathM3MakeIdentity_V( )
{
    VmathMatrix3 result;
    vmathM3MakeIdentity(&result);
    return result;
}

static inline VmathMatrix3 vmathM3MakeRotationX_V( float radians )
{
    VmathMatrix3 result;
    vmathM3MakeRotationX(&result, radians);
    return result;
}

static inline VmathMatrix3 vmathM3MakeRotationY_V( float radians )
{
    VmathMatrix3 result;
    vmathM3MakeRotationY(&result, radians);
    return result;
}

static inline VmathMatrix3 vmathM3MakeRotationZ_V( float radians )
{
    VmathMatrix3 result;
    vmathM3MakeRotationZ(&result, radians);
    return result;
}

static inline VmathMatrix3 vmathM3MakeRotationZYX_V( VmathVector3 radiansXYZ )
{
    VmathMatrix3 result;
    vmathM3MakeRotationZYX(&result, &radiansXYZ);
    return result;
}

static inline VmathMatrix3 vmathM3MakeRotationAxis_V( float radians, VmathVector3 unitVec )
{
    VmathMatrix3 result;
    vmathM3MakeRotationAxis(&result, radians, &unitVec);
    return result;
}

static inline VmathMatrix3 vmathM3MakeRotationQ_V( VmathQuat unitQuat )
{
    VmathMatrix3 result;
    vmathM3MakeRotationQ(&result, &unitQuat);
    return result;
}

static inline VmathMatrix3 vmathM3MakeScale_V( VmathVector3 scaleVec )
{
    VmathMatrix3 result;
    vmathM3MakeScale(&result, &scaleVec);
    return result;
}

static inline VmathMatrix3 vmathM3AppendScale_V( VmathMatrix3 mat, VmathVector3 scaleVec )
{
    VmathMatrix3 result;
    vmathM3AppendScale(&result, &mat, &scaleVec);
    return result;
}

static inline VmathMatrix3 vmathM3PrependScale_V( VmathVector3 scaleVec, VmathMatrix3 mat )
{
    VmathMatrix3 result;
    vmathM3PrependScale(&result, &scaleVec, &mat);
    return result;
}

static inline VmathMatrix3 vmathM3Select_V( VmathMatrix3 mat0, VmathMatrix3 mat1, unsigned int select1 )
{
    VmathMatrix3 result;
    vmathM3Select(&result, &mat0, &mat1, select1);
    return result;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathM3Print_V( VmathMatrix3 mat )
{
    vmathM3Print(&mat);
}

static inline void vmathM3Prints_V( VmathMatrix3 mat, const char *name )
{
    vmathM3Prints(&mat, name);
}

#endif

static inline VmathMatrix4 vmathM4MakeFromScalar_V( float scalar )
{
    VmathMatrix4 result;
    vmathM4MakeFromScalar(&result, scalar);
    return result;
}

static inline VmathMatrix4 vmathM4MakeFromT3_V( VmathTransform3 mat )
{
    VmathMatrix4 result;
    vmathM4MakeFromT3(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4MakeFromCols_V( VmathVector4 _col0, VmathVector4 _col1, VmathVector4 _col2, VmathVector4 _col3 )
{
    VmathMatrix4 result;
    vmathM4MakeFromCols(&result, &_col0, &_col1, &_col2, &_col3);
    return result;
}

static inline VmathMatrix4 vmathM4MakeFromM3V3_V( VmathMatrix3 mat, VmathVector3 translateVec )
{
    VmathMatrix4 result;
    vmathM4MakeFromM3V3(&result, &mat, &translateVec);
    return result;
}

static inline VmathMatrix4 vmathM4MakeFromQV3_V( VmathQuat unitQuat, VmathVector3 translateVec )
{
    VmathMatrix4 result;
    vmathM4MakeFromQV3(&result, &unitQuat, &translateVec);
    return result;
}

static inline void vmathM4SetCol0_V( VmathMatrix4 *result, VmathVector4 _col0 )
{
    vmathM4SetCol0(result, &_col0);
}

static inline void vmathM4SetCol1_V( VmathMatrix4 *result, VmathVector4 _col1 )
{
    vmathM4SetCol1(result, &_col1);
}

static inline void vmathM4SetCol2_V( VmathMatrix4 *result, VmathVector4 _col2 )
{
    vmathM4SetCol2(result, &_col2);
}

static inline void vmathM4SetCol3_V( VmathMatrix4 *result, VmathVector4 _col3 )
{
    vmathM4SetCol3(result, &_col3);
}

static inline void vmathM4SetCol_V( VmathMatrix4 *result, int col, VmathVector4 vec )
{
    vmathM4SetCol(result, col, &vec);
}

static inline void vmathM4SetRow_V( VmathMatrix4 *result, int row, VmathVector4 vec )
{
    vmathM4SetRow(result, row, &vec);
}

static inline void vmathM4SetElem_V( VmathMatrix4 *result, int col, int row, float val )
{
    vmathM4SetElem(result, col, row, val);
}

static inline float vmathM4GetElem_V( VmathMatrix4 mat, int col, int row )
{
    return vmathM4GetElem(&mat, col, row);
}

static inline VmathVector4 vmathM4GetCol0_V( VmathMatrix4 mat )
{
    VmathVector4 result;
    vmathM4GetCol0(&result, &mat);
    return result;
}

static inline VmathVector4 vmathM4GetCol1_V( VmathMatrix4 mat )
{
    VmathVector4 result;
    vmathM4GetCol1(&result, &mat);
    return result;
}

static inline VmathVector4 vmathM4GetCol2_V( VmathMatrix4 mat )
{
    VmathVector4 result;
    vmathM4GetCol2(&result, &mat);
    return result;
}

static inline VmathVector4 vmathM4GetCol3_V( VmathMatrix4 mat )
{
    VmathVector4 result;
    vmathM4GetCol3(&result, &mat);
    return result;
}

static inline VmathVector4 vmathM4GetCol_V( VmathMatrix4 mat, int col )
{
    VmathVector4 result;
    vmathM4GetCol(&result, &mat, col);
    return result;
}

static inline VmathVector4 vmathM4GetRow_V( VmathMatrix4 mat, int row )
{
    VmathVector4 result;
    vmathM4GetRow(&result, &mat, row);
    return result;
}

static inline VmathMatrix4 vmathM4Transpose_V( VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4Transpose(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4Inverse_V( VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4Inverse(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4AffineInverse_V( VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4AffineInverse(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4OrthoInverse_V( VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4OrthoInverse(&result, &mat);
    return result;
}

static inline float vmathM4Determinant_V( VmathMatrix4 mat )
{
    return vmathM4Determinant(&mat);
}

static inline VmathMatrix4 vmathM4Add_V( VmathMatrix4 mat0, VmathMatrix4 mat1 )
{
    VmathMatrix4 result;
    vmathM4Add(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix4 vmathM4Sub_V( VmathMatrix4 mat0, VmathMatrix4 mat1 )
{
    VmathMatrix4 result;
    vmathM4Sub(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix4 vmathM4Neg_V( VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4Neg(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4AbsPerElem_V( VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4AbsPerElem(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4ScalarMul_V( VmathMatrix4 mat, float scalar )
{
    VmathMatrix4 result;
    vmathM4ScalarMul(&result, &mat, scalar);
    return result;
}

static inline VmathVector4 vmathM4MulV4_V( VmathMatrix4 mat, VmathVector4 vec )
{
    VmathVector4 result;
    vmathM4MulV4(&result, &mat, &vec);
    return result;
}

static inline VmathVector4 vmathM4MulV3_V( VmathMatrix4 mat, VmathVector3 vec )
{
    VmathVector4 result;
    vmathM4MulV3(&result, &mat, &vec);
    return result;
}

static inline VmathVector4 vmathM4MulP3_V( VmathMatrix4 mat, VmathPoint3 pnt )
{
    VmathVector4 result;
    vmathM4MulP3(&result, &mat, &pnt);
    return result;
}

static inline VmathMatrix4 vmathM4Mul_V( VmathMatrix4 mat0, VmathMatrix4 mat1 )
{
    VmathMatrix4 result;
    vmathM4Mul(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix4 vmathM4MulT3_V( VmathMatrix4 mat, VmathTransform3 tfrm1 )
{
    VmathMatrix4 result;
    vmathM4MulT3(&result, &mat, &tfrm1);
    return result;
}

static inline VmathMatrix4 vmathM4MulPerElem_V( VmathMatrix4 mat0, VmathMatrix4 mat1 )
{
    VmathMatrix4 result;
    vmathM4MulPerElem(&result, &mat0, &mat1);
    return result;
}

static inline VmathMatrix4 vmathM4MakeIdentity_V( )
{
    VmathMatrix4 result;
    vmathM4MakeIdentity(&result);
    return result;
}

static inline void vmathM4SetUpper3x3_V( VmathMatrix4 *result, VmathMatrix3 mat3 )
{
    vmathM4SetUpper3x3(result, &mat3);
}

static inline VmathMatrix3 vmathM4GetUpper3x3_V( VmathMatrix4 mat )
{
    VmathMatrix3 result;
    vmathM4GetUpper3x3(&result, &mat);
    return result;
}

static inline void vmathM4SetTranslation_V( VmathMatrix4 *result, VmathVector3 translateVec )
{
    vmathM4SetTranslation(result, &translateVec);
}

static inline VmathVector3 vmathM4GetTranslation_V( VmathMatrix4 mat )
{
    VmathVector3 result;
    vmathM4GetTranslation(&result, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4MakeRotationX_V( float radians )
{
    VmathMatrix4 result;
    vmathM4MakeRotationX(&result, radians);
    return result;
}

static inline VmathMatrix4 vmathM4MakeRotationY_V( float radians )
{
    VmathMatrix4 result;
    vmathM4MakeRotationY(&result, radians);
    return result;
}

static inline VmathMatrix4 vmathM4MakeRotationZ_V( float radians )
{
    VmathMatrix4 result;
    vmathM4MakeRotationZ(&result, radians);
    return result;
}

static inline VmathMatrix4 vmathM4MakeRotationZYX_V( VmathVector3 radiansXYZ )
{
    VmathMatrix4 result;
    vmathM4MakeRotationZYX(&result, &radiansXYZ);
    return result;
}

static inline VmathMatrix4 vmathM4MakeRotationAxis_V( float radians, VmathVector3 unitVec )
{
    VmathMatrix4 result;
    vmathM4MakeRotationAxis(&result, radians, &unitVec);
    return result;
}

static inline VmathMatrix4 vmathM4MakeRotationQ_V( VmathQuat unitQuat )
{
    VmathMatrix4 result;
    vmathM4MakeRotationQ(&result, &unitQuat);
    return result;
}

static inline VmathMatrix4 vmathM4MakeScale_V( VmathVector3 scaleVec )
{
    VmathMatrix4 result;
    vmathM4MakeScale(&result, &scaleVec);
    return result;
}

static inline VmathMatrix4 vmathM4AppendScale_V( VmathMatrix4 mat, VmathVector3 scaleVec )
{
    VmathMatrix4 result;
    vmathM4AppendScale(&result, &mat, &scaleVec);
    return result;
}

static inline VmathMatrix4 vmathM4PrependScale_V( VmathVector3 scaleVec, VmathMatrix4 mat )
{
    VmathMatrix4 result;
    vmathM4PrependScale(&result, &scaleVec, &mat);
    return result;
}

static inline VmathMatrix4 vmathM4MakeTranslation_V( VmathVector3 translateVec )
{
    VmathMatrix4 result;
    vmathM4MakeTranslation(&result, &translateVec);
    return result;
}

static inline VmathMatrix4 vmathM4MakeLookAt_V( VmathPoint3 eyePos, VmathPoint3 lookAtPos, VmathVector3 upVec )
{
    VmathMatrix4 result;
    vmathM4MakeLookAt(&result, &eyePos, &lookAtPos, &upVec);
    return result;
}

static inline VmathMatrix4 vmathM4MakePerspective_V( float fovyRadians, float aspect, float zNear, float zFar )
{
    VmathMatrix4 result;
    vmathM4MakePerspective(&result, fovyRadians, aspect, zNear, zFar);
    return result;
}

static inline VmathMatrix4 vmathM4MakeFrustum_V( float left, float right, float bottom, float top, float zNear, float zFar )
{
    VmathMatrix4 result;
    vmathM4MakeFrustum(&result, left, right, bottom, top, zNear, zFar);
    return result;
}

static inline VmathMatrix4 vmathM4MakeOrthographic_V( float left, float right, float bottom, float top, float zNear, float zFar )
{
    VmathMatrix4 result;
    vmathM4MakeOrthographic(&result, left, right, bottom, top, zNear, zFar);
    return result;
}

static inline VmathMatrix4 vmathM4Select_V( VmathMatrix4 mat0, VmathMatrix4 mat1, unsigned int select1 )
{
    VmathMatrix4 result;
    vmathM4Select(&result, &mat0, &mat1, select1);
    return result;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathM4Print_V( VmathMatrix4 mat )
{
    vmathM4Print(&mat);
}

static inline void vmathM4Prints_V( VmathMatrix4 mat, const char *name )
{
    vmathM4Prints(&mat, name);
}

#endif

static inline VmathTransform3 vmathT3MakeFromScalar_V( float scalar )
{
    VmathTransform3 result;
    vmathT3MakeFromScalar(&result, scalar);
    return result;
}

static inline VmathTransform3 vmathT3MakeFromCols_V( VmathVector3 _col0, VmathVector3 _col1, VmathVector3 _col2, VmathVector3 _col3 )
{
    VmathTransform3 result;
    vmathT3MakeFromCols(&result, &_col0, &_col1, &_col2, &_col3);
    return result;
}

static inline VmathTransform3 vmathT3MakeFromM3V3_V( VmathMatrix3 tfrm, VmathVector3 translateVec )
{
    VmathTransform3 result;
    vmathT3MakeFromM3V3(&result, &tfrm, &translateVec);
    return result;
}

static inline VmathTransform3 vmathT3MakeFromQV3_V( VmathQuat unitQuat, VmathVector3 translateVec )
{
    VmathTransform3 result;
    vmathT3MakeFromQV3(&result, &unitQuat, &translateVec);
    return result;
}

static inline void vmathT3SetCol0_V( VmathTransform3 *result, VmathVector3 _col0 )
{
    vmathT3SetCol0(result, &_col0);
}

static inline void vmathT3SetCol1_V( VmathTransform3 *result, VmathVector3 _col1 )
{
    vmathT3SetCol1(result, &_col1);
}

static inline void vmathT3SetCol2_V( VmathTransform3 *result, VmathVector3 _col2 )
{
    vmathT3SetCol2(result, &_col2);
}

static inline void vmathT3SetCol3_V( VmathTransform3 *result, VmathVector3 _col3 )
{
    vmathT3SetCol3(result, &_col3);
}

static inline void vmathT3SetCol_V( VmathTransform3 *result, int col, VmathVector3 vec )
{
    vmathT3SetCol(result, col, &vec);
}

static inline void vmathT3SetRow_V( VmathTransform3 *result, int row, VmathVector4 vec )
{
    vmathT3SetRow(result, row, &vec);
}

static inline void vmathT3SetElem_V( VmathTransform3 *result, int col, int row, float val )
{
    vmathT3SetElem(result, col, row, val);
}

static inline float vmathT3GetElem_V( VmathTransform3 tfrm, int col, int row )
{
    return vmathT3GetElem(&tfrm, col, row);
}

static inline VmathVector3 vmathT3GetCol0_V( VmathTransform3 tfrm )
{
    VmathVector3 result;
    vmathT3GetCol0(&result, &tfrm);
    return result;
}

static inline VmathVector3 vmathT3GetCol1_V( VmathTransform3 tfrm )
{
    VmathVector3 result;
    vmathT3GetCol1(&result, &tfrm);
    return result;
}

static inline VmathVector3 vmathT3GetCol2_V( VmathTransform3 tfrm )
{
    VmathVector3 result;
    vmathT3GetCol2(&result, &tfrm);
    return result;
}

static inline VmathVector3 vmathT3GetCol3_V( VmathTransform3 tfrm )
{
    VmathVector3 result;
    vmathT3GetCol3(&result, &tfrm);
    return result;
}

static inline VmathVector3 vmathT3GetCol_V( VmathTransform3 tfrm, int col )
{
    VmathVector3 result;
    vmathT3GetCol(&result, &tfrm, col);
    return result;
}

static inline VmathVector4 vmathT3GetRow_V( VmathTransform3 tfrm, int row )
{
    VmathVector4 result;
    vmathT3GetRow(&result, &tfrm, row);
    return result;
}

static inline VmathTransform3 vmathT3Inverse_V( VmathTransform3 tfrm )
{
    VmathTransform3 result;
    vmathT3Inverse(&result, &tfrm);
    return result;
}

static inline VmathTransform3 vmathT3OrthoInverse_V( VmathTransform3 tfrm )
{
    VmathTransform3 result;
    vmathT3OrthoInverse(&result, &tfrm);
    return result;
}

static inline VmathTransform3 vmathT3AbsPerElem_V( VmathTransform3 tfrm )
{
    VmathTransform3 result;
    vmathT3AbsPerElem(&result, &tfrm);
    return result;
}

static inline VmathVector3 vmathT3MulV3_V( VmathTransform3 tfrm, VmathVector3 vec )
{
    VmathVector3 result;
    vmathT3MulV3(&result, &tfrm, &vec);
    return result;
}

static inline VmathPoint3 vmathT3MulP3_V( VmathTransform3 tfrm, VmathPoint3 pnt )
{
    VmathPoint3 result;
    vmathT3MulP3(&result, &tfrm, &pnt);
    return result;
}

static inline VmathTransform3 vmathT3Mul_V( VmathTransform3 tfrm0, VmathTransform3 tfrm1 )
{
    VmathTransform3 result;
    vmathT3Mul(&result, &tfrm0, &tfrm1);
    return result;
}

static inline VmathTransform3 vmathT3MulPerElem_V( VmathTransform3 tfrm0, VmathTransform3 tfrm1 )
{
    VmathTransform3 result;
    vmathT3MulPerElem(&result, &tfrm0, &tfrm1);
    return result;
}

static inline VmathTransform3 vmathT3MakeIdentity_V( )
{
    VmathTransform3 result;
    vmathT3MakeIdentity(&result);
    return result;
}

static inline void vmathT3SetUpper3x3_V( VmathTransform3 *result, VmathMatrix3 tfrm )
{
    vmathT3SetUpper3x3(result, &tfrm);
}

static inline VmathMatrix3 vmathT3GetUpper3x3_V( VmathTransform3 tfrm )
{
    VmathMatrix3 result;
    vmathT3GetUpper3x3(&result, &tfrm);
    return result;
}

static inline void vmathT3SetTranslation_V( VmathTransform3 *result, VmathVector3 translateVec )
{
    vmathT3SetTranslation(result, &translateVec);
}

static inline VmathVector3 vmathT3GetTranslation_V( VmathTransform3 tfrm )
{
    VmathVector3 result;
    vmathT3GetTranslation(&result, &tfrm);
    return result;
}

static inline VmathTransform3 vmathT3MakeRotationX_V( float radians )
{
    VmathTransform3 result;
    vmathT3MakeRotationX(&result, radians);
    return result;
}

static inline VmathTransform3 vmathT3MakeRotationY_V( float radians )
{
    VmathTransform3 result;
    vmathT3MakeRotationY(&result, radians);
    return result;
}

static inline VmathTransform3 vmathT3MakeRotationZ_V( float radians )
{
    VmathTransform3 result;
    vmathT3MakeRotationZ(&result, radians);
    return result;
}

static inline VmathTransform3 vmathT3MakeRotationZYX_V( VmathVector3 radiansXYZ )
{
    VmathTransform3 result;
    vmathT3MakeRotationZYX(&result, &radiansXYZ);
    return result;
}

static inline VmathTransform3 vmathT3MakeRotationAxis_V( float radians, VmathVector3 unitVec )
{
    VmathTransform3 result;
    vmathT3MakeRotationAxis(&result, radians, &unitVec);
    return result;
}

static inline VmathTransform3 vmathT3MakeRotationQ_V( VmathQuat unitQuat )
{
    VmathTransform3 result;
    vmathT3MakeRotationQ(&result, &unitQuat);
    return result;
}

static inline VmathTransform3 vmathT3MakeScale_V( VmathVector3 scaleVec )
{
    VmathTransform3 result;
    vmathT3MakeScale(&result, &scaleVec);
    return result;
}

static inline VmathTransform3 vmathT3AppendScale_V( VmathTransform3 tfrm, VmathVector3 scaleVec )
{
    VmathTransform3 result;
    vmathT3AppendScale(&result, &tfrm, &scaleVec);
    return result;
}

static inline VmathTransform3 vmathT3PrependScale_V( VmathVector3 scaleVec, VmathTransform3 tfrm )
{
    VmathTransform3 result;
    vmathT3PrependScale(&result, &scaleVec, &tfrm);
    return result;
}

static inline VmathTransform3 vmathT3MakeTranslation_V( VmathVector3 translateVec )
{
    VmathTransform3 result;
    vmathT3MakeTranslation(&result, &translateVec);
    return result;
}

static inline VmathTransform3 vmathT3Select_V( VmathTransform3 tfrm0, VmathTransform3 tfrm1, unsigned int select1 )
{
    VmathTransform3 result;
    vmathT3Select(&result, &tfrm0, &tfrm1, select1);
    return result;
}

#ifdef _VECTORMATH_DEBUG

static inline void vmathT3Print_V( VmathTransform3 tfrm )
{
    vmathT3Print(&tfrm);
}

static inline void vmathT3Prints_V( VmathTransform3 tfrm, const char *name )
{
    vmathT3Prints(&tfrm, name);
}

#endif

static inline VmathQuat vmathQMakeFromM3_V( VmathMatrix3 tfrm )
{
    VmathQuat result;
    vmathQMakeFromM3(&result, &tfrm);
    return result;
}

static inline VmathMatrix3 vmathV3Outer_V( VmathVector3 tfrm0, VmathVector3 tfrm1 )
{
    VmathMatrix3 result;
    vmathV3Outer(&result, &tfrm0, &tfrm1);
    return result;
}

static inline VmathMatrix4 vmathV4Outer_V( VmathVector4 tfrm0, VmathVector4 tfrm1 )
{
    VmathMatrix4 result;
    vmathV4Outer(&result, &tfrm0, &tfrm1);
    return result;
}

static inline VmathVector3 vmathV3RowMul_V( VmathVector3 vec, VmathMatrix3 mat )
{
    VmathVector3 result;
    vmathV3RowMul(&result, &vec, &mat);
    return result;
}

static inline VmathMatrix3 vmathV3CrossMatrix_V( VmathVector3 vec )
{
    VmathMatrix3 result;
    vmathV3CrossMatrix(&result, &vec);
    return result;
}

static inline VmathMatrix3 vmathV3CrossMatrixMul_V( VmathVector3 vec, VmathMatrix3 mat )
{
    VmathMatrix3 result;
    vmathV3CrossMatrixMul(&result, &vec, &mat);
    return result;
}


// May the Sony authors forgive us...
// We need shortened (yes, namespace-polluting) names for our book.

#define Point3 VmathPoint3
#define Vector3 VmathVector3
#define Vector4 VmathVector4
#define Quaternion VmathQuat
#define Matrix3 VmathMatrix3
#define Matrix4 VmathMatrix4
#define Transform3 VmathTransform3

#define V3MakeFromElems vmathV3MakeFromElems_V
#define V3MakeFromP3 vmathV3MakeFromP3_V
#define V3MakeFromScalar vmathV3MakeFromScalar_V
#define V3SetX vmathV3SetX_V
#define V3SetY vmathV3SetY_V
#define V3SetZ vmathV3SetZ_V
#define V3GetX vmathV3GetX_V
#define V3GetY vmathV3GetY_V
#define V3GetZ vmathV3GetZ_V
#define V3SetElem vmathV3SetElem_V
#define V3GetElem vmathV3GetElem_V
#define V3Add vmathV3Add_V
#define V3Sub vmathV3Sub_V
#define V3AddP3 vmathV3AddP3_V
#define V3ScalarMul vmathV3ScalarMul_V
#define V3ScalarDiv vmathV3ScalarDiv_V
#define V3Neg vmathV3Neg_V
#define V3MakeXAxis vmathV3MakeXAxis_V
#define V3MakeYAxis vmathV3MakeYAxis_V
#define V3MakeZAxis vmathV3MakeZAxis_V
#define V3MulPerElem vmathV3MulPerElem_V
#define V3DivPerElem vmathV3DivPerElem_V
#define V3RecipPerElem vmathV3RecipPerElem_V
#define V3SqrtPerElem vmathV3SqrtPerElem_V
#define V3RsqrtPerElem vmathV3RsqrtPerElem_V
#define V3AbsPerElem vmathV3AbsPerElem_V
#define V3CopySignPerElem vmathV3CopySignPerElem_V
#define V3MaxPerElem vmathV3MaxPerElem_V
#define V3MinPerElem vmathV3MinPerElem_V
#define V3MaxElem vmathV3MaxElem_V
#define V3MinElem vmathV3MinElem_V
#define V3Sum vmathV3Sum_V
#define V3Dot vmathV3Dot_V
#define V3LengthSqr vmathV3LengthSqr_V
#define V3Length vmathV3Length_V
#define V3Normalize vmathV3Normalize_V
#define V3Cross vmathV3Cross_V
#define V3Outer vmathV3Outer_V
#define V3RowMul vmathV3RowMul_V
#define V3CrossMatrix vmathV3CrossMatrix_V
#define V3CrossMatrixMul vmathV3CrossMatrixMul_V
#define V3Lerp vmathV3Lerp_V
#define V3Slerp vmathV3Slerp_V
#define V3Select vmathV3Select_V
#define V4MakeFromElems vmathV4MakeFromElems_V
#define V4MakeFromV3Scalar vmathV4MakeFromV3Scalar_V
#define V4MakeFromV3 vmathV4MakeFromV3_V
#define V4MakeFromP3 vmathV4MakeFromP3_V
#define V4MakeFromQ vmathV4MakeFromQ_V
#define V4MakeFromScalar vmathV4MakeFromScalar_V
#define V4SetXYZ vmathV4SetXYZ_V
#define V4GetXYZ vmathV4GetXYZ_V
#define V4SetX vmathV4SetX_V
#define V4SetY vmathV4SetY_V
#define V4SetZ vmathV4SetZ_V
#define V4SetW vmathV4SetW_V
#define V4GetX vmathV4GetX_V
#define V4GetY vmathV4GetY_V
#define V4GetZ vmathV4GetZ_V
#define V4GetW vmathV4GetW_V
#define V4SetElem vmathV4SetElem_V
#define V4GetElem vmathV4GetElem_V
#define V4Add vmathV4Add_V
#define V4Sub vmathV4Sub_V
#define V4ScalarMul vmathV4ScalarMul_V
#define V4ScalarDiv vmathV4ScalarDiv_V
#define V4Neg vmathV4Neg_V
#define V4MakeXAxis vmathV4MakeXAxis_V
#define V4MakeYAxis vmathV4MakeYAxis_V
#define V4MakeZAxis vmathV4MakeZAxis_V
#define V4MakeWAxis vmathV4MakeWAxis_V
#define V4MulPerElem vmathV4MulPerElem_V
#define V4DivPerElem vmathV4DivPerElem_V
#define V4RecipPerElem vmathV4RecipPerElem_V
#define V4SqrtPerElem vmathV4SqrtPerElem_V
#define V4RsqrtPerElem vmathV4RsqrtPerElem_V
#define V4AbsPerElem vmathV4AbsPerElem_V
#define V4CopySignPerElem vmathV4CopySignPerElem_V
#define V4MaxPerElem vmathV4MaxPerElem_V
#define V4MinPerElem vmathV4MinPerElem_V
#define V4MaxElem vmathV4MaxElem_V
#define V4MinElem vmathV4MinElem_V
#define V4Sum vmathV4Sum_V
#define V4Dot vmathV4Dot_V
#define V4LengthSqr vmathV4LengthSqr_V
#define V4Length vmathV4Length_V
#define V4Normalize vmathV4Normalize_V
#define V4Outer vmathV4Outer_V
#define V4Lerp vmathV4Lerp_V
#define V4Slerp vmathV4Slerp_V
#define V4Select vmathV4Select_V
#define P3MakeFromElems vmathP3MakeFromElems_V
#define P3MakeFromV3 vmathP3MakeFromV3_V
#define P3MakeFromScalar vmathP3MakeFromScalar_V
#define P3SetX vmathP3SetX_V
#define P3SetY vmathP3SetY_V
#define P3SetZ vmathP3SetZ_V
#define P3GetX vmathP3GetX_V
#define P3GetY vmathP3GetY_V
#define P3GetZ vmathP3GetZ_V
#define P3SetElem vmathP3SetElem_V
#define P3GetElem vmathP3GetElem_V
#define P3Sub vmathP3Sub_V
#define P3AddV3 vmathP3AddV3_V
#define P3SubV3 vmathP3SubV3_V
#define P3MulPerElem vmathP3MulPerElem_V
#define P3DivPerElem vmathP3DivPerElem_V
#define P3RecipPerElem vmathP3RecipPerElem_V
#define P3SqrtPerElem vmathP3SqrtPerElem_V
#define P3RsqrtPerElem vmathP3RsqrtPerElem_V
#define P3AbsPerElem vmathP3AbsPerElem_V
#define P3CopySignPerElem vmathP3CopySignPerElem_V
#define P3MaxPerElem vmathP3MaxPerElem_V
#define P3MinPerElem vmathP3MinPerElem_V
#define P3MaxElem vmathP3MaxElem_V
#define P3MinElem vmathP3MinElem_V
#define P3Sum vmathP3Sum_V
#define P3Scale vmathP3Scale_V
#define P3NonUniformScale vmathP3NonUniformScale_V
#define P3Projection vmathP3Projection_V
#define P3DistSqrFromOrigin vmathP3DistSqrFromOrigin_V
#define P3DistFromOrigin vmathP3DistFromOrigin_V
#define P3DistSqr vmathP3DistSqr_V
#define P3Dist vmathP3Dist_V
#define P3Lerp vmathP3Lerp_V
#define P3Select vmathP3Select_V
#define QMakeFromElems vmathQMakeFromElems_V
#define QMakeFromV3Scalar vmathQMakeFromV3Scalar_V
#define QMakeFromV4 vmathQMakeFromV4_V
#define QMakeFromM3 vmathQMakeFromM3_V
#define QMakeFromScalar vmathQMakeFromScalar_V
#define QSetXYZ vmathQSetXYZ_V
#define QGetXYZ vmathQGetXYZ_V
#define QSetX vmathQSetX_V
#define QSetY vmathQSetY_V
#define QSetZ vmathQSetZ_V
#define QSetW vmathQSetW_V
#define QGetX vmathQGetX_V
#define QGetY vmathQGetY_V
#define QGetZ vmathQGetZ_V
#define QGetW vmathQGetW_V
#define QSetElem vmathQSetElem_V
#define QGetElem vmathQGetElem_V
#define QAdd vmathQAdd_V
#define QSub vmathQSub_V
#define QMul vmathQMul_V
#define QScalarMul vmathQScalarMul_V
#define QScalarDiv vmathQScalarDiv_V
#define QNeg vmathQNeg_V
#define QMakeIdentity vmathQMakeIdentity_V
#define QMakeRotationArc vmathQMakeRotationArc_V
#define QMakeRotationAxis vmathQMakeRotationAxis_V
#define QMakeRotationX vmathQMakeRotationX_V
#define QMakeRotationY vmathQMakeRotationY_V
#define QMakeRotationZ vmathQMakeRotationZ_V
#define QConj vmathQConj_V
#define QRotate vmathQRotate_V
#define QDot vmathQDot_V
#define QNorm vmathQNorm_V
#define QNormalize vmathQNormalize_V
#define QLerp vmathQLerp_V
#define QSlerp vmathQSlerp_V
#define QSquad vmathQSquad_V
#define QSelect vmathQSelect_V
#define M3MakeFromCols vmathM3MakeFromCols_V
#define M3MakeFromQ vmathM3MakeFromQ_V
#define M3MakeFromScalar vmathM3MakeFromScalar_V
#define M3SetCol0 vmathM3SetCol0_V
#define M3SetCol1 vmathM3SetCol1_V
#define M3SetCol2 vmathM3SetCol2_V
#define M3GetCol0 vmathM3GetCol0_V
#define M3GetCol1 vmathM3GetCol1_V
#define M3GetCol2 vmathM3GetCol2_V
#define M3SetCol vmathM3SetCol_V
#define M3SetRow vmathM3SetRow_V
#define M3GetCol vmathM3GetCol_V
#define M3GetRow vmathM3GetRow_V
#define M3SetElem vmathM3SetElem_V
#define M3GetElem vmathM3GetElem_V
#define M3Add vmathM3Add_V
#define M3Sub vmathM3Sub_V
#define M3Neg vmathM3Neg_V
#define M3ScalarMul vmathM3ScalarMul_V
#define M3MulV3 vmathM3MulV3_V
#define M3Mul vmathM3Mul_V
#define M3MakeIdentity vmathM3MakeIdentity_V
#define M3MakeRotationX vmathM3MakeRotationX_V
#define M3MakeRotationY vmathM3MakeRotationY_V
#define M3MakeRotationZ vmathM3MakeRotationZ_V
#define M3MakeRotationZYX vmathM3MakeRotationZYX_V
#define M3MakeRotationAxis vmathM3MakeRotationAxis_V
#define M3MakeRotationQ vmathM3MakeRotationQ_V
#define M3MakeScale vmathM3MakeScale_V
#define M3AppendScale vmathM3AppendScale_V
#define M3PrependScale vmathM3PrependScale_V
#define M3MulPerElem vmathM3MulPerElem_V
#define M3AbsPerElem vmathM3AbsPerElem_V
#define M3Transpose vmathM3Transpose_V
#define M3Inverse vmathM3Inverse_V
#define M3Determinant vmathM3Determinant_V
#define M3Select vmathM3Select_V
#define M4MakeFromCols vmathM4MakeFromCols_V
#define M4MakeFromT3 vmathM4MakeFromT3_V
#define M4MakeFromM3V3 vmathM4MakeFromM3V3_V
#define M4MakeFromQV3 vmathM4MakeFromQV3_V
#define M4MakeFromScalar vmathM4MakeFromScalar_V
#define M4SetUpper3x3 vmathM4SetUpper3x3_V
#define M4GetUpper3x3 vmathM4GetUpper3x3_V
#define M4SetTranslation vmathM4SetTranslation_V
#define M4GetTranslation vmathM4GetTranslation_V
#define M4SetCol0 vmathM4SetCol0_V
#define M4SetCol1 vmathM4SetCol1_V
#define M4SetCol2 vmathM4SetCol2_V
#define M4SetCol3 vmathM4SetCol3_V
#define M4GetCol0 vmathM4GetCol0_V
#define M4GetCol1 vmathM4GetCol1_V
#define M4GetCol2 vmathM4GetCol2_V
#define M4GetCol3 vmathM4GetCol3_V
#define M4SetCol vmathM4SetCol_V
#define M4SetRow vmathM4SetRow_V
#define M4GetCol vmathM4GetCol_V
#define M4GetRow vmathM4GetRow_V
#define M4SetElem vmathM4SetElem_V
#define M4GetElem vmathM4GetElem_V
#define M4Add vmathM4Add_V
#define M4Sub vmathM4Sub_V
#define M4Neg vmathM4Neg_V
#define M4ScalarMul vmathM4ScalarMul_V
#define M4MulV4 vmathM4MulV4_V
#define M4MulV3 vmathM4MulV3_V
#define M4MulP3 vmathM4MulP3_V
#define M4Mul vmathM4Mul_V
#define M4MulT3 vmathM4MulT3_V
#define M4MakeIdentity vmathM4MakeIdentity_V
#define M4MakeRotationX vmathM4MakeRotationX_V
#define M4MakeRotationY vmathM4MakeRotationY_V
#define M4MakeRotationZ vmathM4MakeRotationZ_V
#define M4MakeRotationZYX vmathM4MakeRotationZYX_V
#define M4MakeRotationAxis vmathM4MakeRotationAxis_V
#define M4MakeRotationQ vmathM4MakeRotationQ_V
#define M4MakeScale vmathM4MakeScale_V
#define M4MakeTranslation vmathM4MakeTranslation_V
#define M4MakeLookAt vmathM4MakeLookAt_V
#define M4MakePerspective vmathM4MakePerspective_V
#define M4MakeFrustum vmathM4MakeFrustum_V
#define M4MakeOrthographic vmathM4MakeOrthographic_V
#define M4AppendScale vmathM4AppendScale_V
#define M4PrependScale vmathM4PrependScale_V
#define M4MulPerElem vmathM4MulPerElem_V
#define M4AbsPerElem vmathM4AbsPerElem_V
#define M4Transpose vmathM4Transpose_V
#define M4Inverse vmathM4Inverse_V
#define M4AffineInverse vmathM4AffineInverse_V
#define M4OrthoInverse vmathM4OrthoInverse_V
#define M4Determinant vmathM4Determinant_V
#define M4Select vmathM4Select_V
#define T3MakeFromCols vmathT3MakeFromCols_V
#define T3MakeFromM3V3 vmathT3MakeFromM3V3_V
#define T3MakeFromQV3 vmathT3MakeFromQV3_V
#define T3MakeFromScalar vmathT3MakeFromScalar_V
#define T3SetUpper3x3 vmathT3SetUpper3x3_V
#define T3GetUpper3x3 vmathT3GetUpper3x3_V
#define T3SetTranslation vmathT3SetTranslation_V
#define T3GetTranslation vmathT3GetTranslation_V
#define T3SetCol0 vmathT3SetCol0_V
#define T3SetCol1 vmathT3SetCol1_V
#define T3SetCol2 vmathT3SetCol2_V
#define T3SetCol3 vmathT3SetCol3_V
#define T3GetCol0 vmathT3GetCol0_V
#define T3GetCol1 vmathT3GetCol1_V
#define T3GetCol2 vmathT3GetCol2_V
#define T3GetCol3 vmathT3GetCol3_V
#define T3SetCol vmathT3SetCol_V
#define T3SetRow vmathT3SetRow_V
#define T3GetCol vmathT3GetCol_V
#define T3GetRow vmathT3GetRow_V
#define T3SetElem vmathT3SetElem_V
#define T3GetElem vmathT3GetElem_V
#define T3MulV3 vmathT3MulV3_V
#define T3MulP3 vmathT3MulP3_V
#define T3Mul vmathT3Mul_V
#define T3MakeIdentity vmathT3MakeIdentity_V
#define T3MakeRotationX vmathT3MakeRotationX_V
#define T3MakeRotationY vmathT3MakeRotationY_V
#define T3MakeRotationZ vmathT3MakeRotationZ_V
#define T3MakeRotationZYX vmathT3MakeRotationZYX_V
#define T3MakeRotationAxis vmathT3MakeRotationAxis_V
#define T3MakeRotationQ vmathT3MakeRotationQ_V
#define T3MakeScale vmathT3MakeScale_V
#define T3MakeTranslation vmathT3MakeTranslation_V
#define T3AppendScale vmathT3AppendScale_V
#define T3PrependScale vmathT3PrependScale_V
#define T3MulPerElem vmathT3MulPerElem_V
#define T3AbsPerElem vmathT3AbsPerElem_V
#define T3Inverse vmathT3Inverse_V
#define T3OrthoInverse vmathT3OrthoInverse_V
#define T3Select vmathT3Select_V
