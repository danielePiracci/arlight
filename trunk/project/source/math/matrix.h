/// \file math/matrix.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
// 
// This file define a list of nicknames for common use of the matrix class.
#ifndef MATH_MATRIX_H__
#define MATH_MATRIX_H__

#include "math/Mat4.h"

BEGIN_PROJECT_NAMESPACE();

typedef Math::Mat4<int> mat4i;
typedef Math::Mat4<float> mat4f;
typedef Math::Mat4<double> mat4d;

END_PROJECT_NAMESPACE();

#endif  // MATH_MATRIX_H__
