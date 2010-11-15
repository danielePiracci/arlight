/// \file math/vector.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
// 
// This file define a list of nicknames for common use of the vector class.
#ifndef VECTOR_H__
#define VECTOR_H__

#include "math/vec3_inl.h"
#include "math/vec4_inl.h"

BEGIN_PROJECT_NAMESPACE();

typedef Math::Vec3<int> vec3i;
typedef Math::Vec4<int> vec4i;

typedef Math::Vec3<float> vec3f;
typedef Math::Vec4<float> vec4f;

typedef Math::Vec3<double> vec3d;
typedef Math::Vec4<double> vec4d;

END_PROJECT_NAMESPACE();

#endif  // VECTOR_H__
