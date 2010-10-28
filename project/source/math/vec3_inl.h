/// \file vec3_inl.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0

// TODO: translate comments..

#ifndef MATH_VEC3_INL_H__
#define MATH_VEC3_INL_H__

#include "math/vec3.h"

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(Math);

// Operdor de casting entre un Vec3 y un flotante
template<class _T>
__forceinline void Vec3<_T>::operator =(const _T& _param) {
  // Se actualizan los valores de las componentes del vector
  x = y = z = _param;
}

// Operador de casting entre dos Vec3
template<class _T>
__forceinline void Vec3<_T>::operator =(const Vec3<_T>& _param) {
  // Se actualizan los valores de las componentes del vector
  memcpy(values, _param.values, sizeof(values));
}

// Operador para obtener un elemento del vector
template<class _T>
__forceinline _T Vec3<_T>::operator [](const int &_index) const {
  // Se retorna el elemento i del vector
  return values[_index];
}

// Operador para incrementar las componentes del vector
template<class _T>
__forceinline void Vec3<_T>::operator ++() {
  // Se actualizan los valores de las componentes del vector
  x++; y++; z++;
}

// Operador para decrementar las componentes del vector
template<class _T>
__forceinline void Vec3<_T>::operator --() {
  // Se actualizan los valores de las componentes del vector
  x--; y--; z--;
}

// Operador para negar el vector
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator - () {
  return Vec3<_T> (-x, -y, -z);
}

// Operador de suma entre dos Vec3
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator +(const Vec3<_T>& _param) const {
  // Se calcula el vector resultante y se retorna
  return Vec3<_T>(x + _param.x, y + _param.y, z + _param.z);
}

// Operdor de suma y asignacion entre dos Vec3
template<class _T>
__forceinline void Vec3<_T>::operator +=(const Vec3<_T>& _param) {
  // Se actualizan los valores de las componentes del vector
  x += _param.x;	y += _param.y;	z += _param.z;
}

// Operdor de suma entre un Vec3 y flotante 
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator +(const _T& _param) const {
  // Se calcula el vector resultante y se retorna
  return Vec3<_T>(x + _param, y + _param, z + _param);
}

// 
template<class _T>
__forceinline void Vec3<_T>::operator +=(const _T& _param) {
  // Se actualizan los valores de las componentes del vector
  x += _param; y += _param; z += _param;
}

// Operadores de resta entre dos vectores
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator -(const Vec3<_T>& _param) const {
  // Se calcula el vector resultante y se retorna
  return Vec3<_T>(x - _param.x, y - _param.y, z - _param.z);
}

// 
template<class _T>
__forceinline void Vec3<_T>::operator -=(const Vec3<_T>& _param) {
  // Se actualizan los valores de las componentes del vector
  x -= _param.x; y -= _param.y; z -= _param.z;
}

// Operadores para restarle un flotante a todas las componentes del vector
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator -(const _T& _param) const {
  // Se calcula el vector resultante y se retorna
  return Vec3<_T>(x - _param, y - _param, z - _param);
}

// 
template<class _T>
__forceinline void Vec3<_T>::operator -=(const _T& _param) {
  // Se actualizan los valores de las componentes del vector
  x -= _param; y -= _param; z -= _param;
}


// Operadores para el producto entre un vector y un escalar
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator *(const _T& _param) const {
  // Se calcula el vector resultante y se retorna
  return Vec3<_T>(x * _param, y * _param, z * _param);
}

// 
template<class _T>
__forceinline void Vec3<_T>::operator *=(const _T& _param) {
  // Se actualizan los valores de las componentes del vector
  x *= _param; y *= _param; z *= _param;
}

// Operadores para la division entre un vector y un escalar
template<class _T>
__forceinline Vec3<_T> Vec3<_T>::operator /(const _T& _param) const {
  // Se calcula el vector resultante y se retorna
  const _T _t = static_cast<_T>(1) / _param;
  return Vec3<_T>(x * _t, y * _t, z * _t);
}

// 
template<class _T>
__forceinline void Vec3<_T>::operator /=(const _T& _param) {
  // Se actualizan los valores de las componentes del vector
  const _T _t = static_cast<_T>(1) / _param;
  x *= _t; y *= _t; z *= _t;
}

// Operadores de comparacion entre vectores
template<class _T>
__forceinline bool Vec3<_T>::operator ==(const Vec3<_T>& _param) const {
  return x == _param.x && y == _param.y && z == _param.z;
}

template<class _T>
__forceinline bool Vec3<_T>::operator !=(const Vec3<_T>& _param) const {
  return x != _param.x || y != _param.y || z != _param.z;
}

template<class _T>
__forceinline bool Vec3<_T>::operator <(const Vec3<_T>& _param) const {
  return x < _param.x && y < _param.y && z < _param.z;
}

template<class _T>
__forceinline bool Vec3<_T>::operator >(const Vec3<_T>& _param) const {
  return x > _param.x && y > _param.y && z > _param.z;
}

template<class _T>
__forceinline bool Vec3<_T>::operator <=(const Vec3<_T>& _param) const {
  return x <= _param.x && y <= _param.y && z <= _param.z;
}

template<class _T>
__forceinline bool Vec3<_T>::operator >=(const Vec3<_T>& _param) const {
  return x >= _param.x && y >= _param.y && z >= _param.z;
}

// Operadores de comparacion entre un vector y un flotante
template<class _T>
__forceinline bool Vec3<_T>::operator <(const _T& _param) const {
  return x < _param && y < _param && z < _param;
}

template<class _T>
__forceinline bool Vec3<_T>::operator >(const _T& _param) const {
  return x > _param && y > _param && z > _param;
}

template<class _T>
__forceinline bool Vec3<_T>::operator <=(const _T& _param) const {
  return x <= _param && y <= _param && z <= _param;
}

template<class _T>
__forceinline bool Vec3<_T>::operator >=(const _T& _param) const {
  return x >= _param && y >= _param && z >= _param;
}

template<class _T>
__forceinline bool Vec3<_T>::operator ==(const _T& _param) const {
  return x == _param && y == _param && z == _param;
}

template<class _T>
__forceinline bool Vec3<_T>::operator !=(const _T& _param) const {
  return x != _param && y != _param && z != _param;
}

// Metodo para inicializar el vector
template<class _T>
void Vec3<_T>::init() {
  // Se iniicializan los valores de las componentes del vector
  memset(values, 0, sizeof(values));
}

// Metodo para obtener el modulo del vector
template<class _T>
_T Vec3<_T>::module() const {
  return ::sqrt(x*x + y*y + z*z);
}

// Metodo para normalizar el vector
template<class _T>
void Vec3<_T>::normalize() {
  const _T mod = static_cast<_T> (1) / module();
  x *= mod; y *= mod; z *= mod;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec3<_T>::set(const _T& _tx) {
  // Se actualizan los valores de las componentes del vector
  x = _tx;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec3<_T>::set(const _T& _tx, const _T& _ty) {
  // Se actualizan los valores de las componentes del vector
  x = _tx; y = _ty;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec3<_T>::set(const _T& _tx, const _T& _ty, const _T& _tz) {
  // Se actualizan los valores de las componentes del vector
  x = _tx; y = _ty; z = _tz;
}

// Metodo para calcular el producto punto entre dos vectores
template<class _T>
_T dot(const Vec3<_T>& v1, const Vec3<_T>& v2) {
  return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

// Metodo para calcular el producto cruz entre dos vectores
template<class _T>
Vec3<_T> cross(const Vec3<_T>& v1, const Vec3<_T>& v2) {
  //se calcula el vector resultante y se retorna
  return Vec3<_T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

// Metodo para calcular el vector reflejado
//donde I es el vector de insidencia y N es la normal de la superficie
template<class _T>
Vec3<_T> reflect(const Vec3<_T> &I, const Vec3<_T> &N) {
  return  N * 2 * dot(-I, N) + I;
  //nota: no se si hace falta normalizar le vector
}

// Metodo para calcular el vector de refracccion
//donde I es el vector de insidencia, N es la normal de la superficie 
//y irr es el indice relativo de refraccion
template<class _T>
Vec3<_T> refract(const Vec3<_T> &I, const Vec3<_T> &N, const _T& irr) {
  const _T IdotN = dot(I, N);	//nota: --> revizar si no tengo q multiplicar I por -1
  const _T k = 1.0f - irr * irr *(1.0f - IdotN * IdotN);
  return I * irr - N * (irr * IdotN + sqrt(k));
}

// Metodo para proyectar el vector v1 en el vector v2
//donde v2 tiene que ser un vetor unitario
template<class _T>
Vec3<_T> project(const Vec3<_T> &v1, const Vec3<_T> &v2) {
  return v2 * dot(v1, v2);
}

// Metodo para escalar el vector
template<class _T>
void Vec3<_T>::scale(const Vec3<_T>& s) {
  // Se actualizan las componentes del vector
  x *= s.x; y *= s.y; z *= s.z;
}

// Metodo para escalar el vector
template<class _T>
void Vec3<_T>::scale(const _T& sx, const _T& sy, const _T& sz) {
  // Se actualizan las componentes del vector
  x *= sx; y *= sy; z *= sz;
}

// Metodo para trasladar el vector
template<class _T>
void Vec3<_T>::translate(const Vec3<_T>& t) {
  // Se actualizan las componentes del vector
  x += t.x; y += t.y; z += t.z;
}

// Metodo para trasladar el vector
template<class _T>
void Vec3<_T>::translate(const _T& tx, const _T& ty, const _T& tz) {
  // Se actualizan las componentes del vector
  x += tx; y += ty; z += tz;
}

// Metodo para rotar el vector con respecto al eje x
template<class _T>
void Vec3<_T>::rotateX(const _T& angle) {
  // Se calcula el seno y el coseno del angulo
  const _T s = sin(angle);
  const _T c = cos(angle);

  //
  const _T ny = y*c - z*s;
  const _T nz = y*s + z*c;

  //
  y = ny;
  z = nz;
}

// Metodo para rotar el vector con respecto al eje y
template<class _T>
void Vec3<_T>::rotateY(const _T& angle) {
  // Se calcula el seno y el coseno del angulo
  const _T s = sin(angle);
  const _T c = cos(angle);

  //
  const _T nx =  x*c + z*s;
  const _T nz = -x*s + z*c;

  //
  x = nx;
  z = nz;
}

// Metodo para rotar el vector con respecto al eje z
template<class _T>
void Vec3<_T>::rotateZ(const _T& angle) {
  // Se calcula el seno y el coseno del angulo
  const _T s = sin(angle);
  const _T c = cos(angle);

  //
  const _T nx = x*c - y*s;
  const _T ny = x*s + y*c;

  //
  x = nx;
  y = ny;
}

// Metodo para rotar el vector con respecto al eje x
template<class _T>
Vec3<_T> rotateX(const Vec3<_T>& v, const _T& angle) {
  // Se calcula el seno y el coseno del angulo
  const _T s = sin(angle);
  const _T c = cos(angle);

  //se calcula el vector resultante y se retorna
  return Vec3<_T>(v.x, v.y*c - v.z*s, v.y*s + v.z*c);
}

// Metodo para rotar el vector con respecto al eje y
template<class _T>
Vec3<_T> rotateY(const Vec3<_T>& v, const _T& angle) {
  // Se calcula el seno y el coseno del angulo
  const _T s = sin(angle);
  const _T c = cos(angle);

  //se calclula vector resultante y se retorna
  return Vec3<_T>(v.y, v.x*c + v.z*s, -v.x*s + v.z*c);
}

// Metodo para rotar el vector con respecto al eje z
template<class _T>
Vec3<_T> rotateZ(const Vec3<_T> &v, const _T& angle) {
  // Se calcula el seno y el coseno del angulo
  const _T s = sin(angle);
  const _T c = cos(angle);

  //se caclula el vector resultante y se retorna
  return Vec3<_T>(v.x*c - v.y*s, v.x*s + v.y*c, v.z);
}

END_NAMESPACE(Math);
END_PROJECT_NAMESPACE();

#endif  // MATH_VEC3_INL_H__
