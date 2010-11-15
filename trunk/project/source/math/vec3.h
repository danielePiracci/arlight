/// \file math/vec3.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
//
// This file define a template class for 3 dimension vectors.

#ifndef MATH_VEC3_H__
#define MATH_VEC3_H__

#include "global.h"
#include <math.h>
#include <memory.h>

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(Math);

template<class _T>
class Vec3 {
 public:
  union {
    struct {_T x, y, z;}; // Vector components.
    struct {_T r, g, b;}; // Color components.
    struct {_T s, t, p;}; // Texture components.
    _T values[3];
  };
	
  // Vector constructors and destructor.
  Vec3();
  Vec3(const _T& _tx);
  Vec3(const _T& _tx, const _T& _ty);
  Vec3(const _T& _tx, const _T& _ty, const _T& _tz);
  ~Vec3();

  // Assingment operators.
  void operator = (const _T& _param);
  void operator = (const Vec3<_T>& _param);

  // Indexing operator.
  _T operator [](const int& _index) const;

  // Operators to increase and decrease vector's components.
  void operator ++();
  void operator --();

  // To negate the vector.
  Vec3<_T> operator - ();

  // Operators to add two vectors.
  Vec3<_T> operator + (const Vec3<_T>& _param) const;
  void operator +=(const Vec3<_T>& _param);
	
  // Operators to add a value to each vector component.
  Vec3<_T> operator + (const _T& _param) const;
  void operator +=(const _T& _param);
	
  // Operators to substract two vectors.
  Vec3<_T> operator - (const Vec3<_T>& _param) const;
  void operator -=(const Vec3<_T>& _param);

  // Operators to substract a value to each vector component.
  Vec3<_T> operator - (const _T& _param) const;
  void operator -=(const _T& _param);
	
  // Operators to multiply a value for each vector component.
  Vec3<_T> operator * (const _T& _param) const;
  void operator *=(const _T& _param);
	
  // Operators to divide a value for each vector component.
  Vec3<_T> operator / (const _T& _param) const;
  void operator /=(const _T& _param);
	
  // Compare operators between two vectors.
  bool operator >  (const Vec3<_T>& _param) const;
  bool operator <  (const Vec3<_T>& _param) const;
  bool operator >= (const Vec3<_T>& _param) const;
  bool operator <= (const Vec3<_T>& _param) const;
  bool operator == (const Vec3<_T>& _param) const;
  bool operator != (const Vec3<_T>& _param) const;

  // Compare operators between a vector and a value.
  bool operator >  (const _T& _param) const;
  bool operator <  (const _T& _param) const;
  bool operator >= (const _T& _param) const;
  bool operator <= (const _T& _param) const;
  bool operator == (const _T& _param) const;
  bool operator != (const _T& _param) const;

  // Methods to get module and to normalize the vector.
  _T module() const;
  void normalize();
  
  // Methods to initialize the vector.
  void init();
  void set(const _T& _tx);
  void set(const _T& _tx, const _T& _ty);
  void set(const _T& _tx, const _T& _ty, const _T& _tz);	

  // Methods to scale the vector.
  void scale(const Vec3<_T>& s);
  void scale(const _T& sx, const _T& sy, const _T& sz);
	
  // Methods to translate the vector.
  void translate(const Vec3<_T>& t);
  void translate(const _T& tx, const _T& ty, const _T& tz);

  // Methods to rotate the vector.
  void rotateX(const _T& angle);
  void rotateY(const _T& angle);
  void rotateZ(const _T& angle);
};

// Constructors
template<class _T>
Vec3<_T>::Vec3() : x(0), y(0), z(0) { }

template<class _T>
Vec3<_T>::Vec3(const _T& _tx) : x(_tx), y(0), z(0) { }

template<class _T>
Vec3<_T>::Vec3(const _T& _tx, const _T& _ty) : x(_tx), y(_ty), z(0) { }

template<class _T>
Vec3<_T>::Vec3(const _T& _tx, const _T& _ty, const _T& _tz)
	: x(_tx), y(_ty), z(_tz) { }

// Destructor
template<class _T>
Vec3<_T>::~Vec3() { }

END_NAMESPACE(Math);
END_PROJECT_NAMESPACE();

#endif  // MATH_VEC3_H__
