/// \file vec4_inl.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
#ifndef MATH_VEC4_INL_H__
#define MATH_VEC4_INL_H__

#include "math/vec4.h"

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(Math);

// Operdor de casting entre un Vec3 y un flotante
template<class _T>
__forceinline void Vec4<_T>::operator =(const _T& _param) {
	// Se actualizan los valores de las componentes del vector
	x = y = z = w = _param;
}

// Operador de casting entre dos Vec3
template<class _T>
__forceinline void Vec4<_T>::operator =(const Vec4<_T>& _param) {
	// Se actualizan los valores de las componentes del vector
	memcpy(values, _param.values, sizeof(values));
}

// Operador para obtener un elemento del vector
template<class _T>
__forceinline _T Vec4<_T>::operator [](const int &_index) const {
	// Se retorna el elemento i del vector
	return values[_index];
}

// Operador para incrementar las componentes del vector
template<class _T>
__forceinline void Vec4<_T>::operator ++() {
	// Se actualizan los valores de las componentes del vector
	x++;	y++;	z++;	w++;
}

// Operador para decrementar las componentes del vector
template<class _T>
__forceinline void Vec4<_T>::operator --() {
	// Se actualizan los valores de las componentes del vector
	x--;	y--;	z--;	w--;
}

// Operador de suma entre dos Vec3
template<class _T>
__forceinline Vec4<_T> Vec4<_T>::operator +(const Vec4<_T>& _param) const {
	// Se calcula el vector resultante y se retorna
	return Vec4<_T>(x + _param.x, y + _param.y, z + _param.z, w + _param.w);
}

// Operdor de suma y asignacion entre dos Vec3
template<class _T>
__forceinline void Vec4<_T>::operator +=(const Vec4<_T>& _param) {
	// Se actualizan los valores de las componentes del vector
	x += _param.x;	y += _param.y;	z += _param.z;	w += _param.w;
}

// Operdor de suma entre un Vec3 y flotante 
template<class _T>
__forceinline Vec4<_T> Vec4<_T>::operator +(const _T& _param) const {
	// Se calcula el vector resultante y se retorna
	return Vec4<_T>(x + _param, y + _param, z + _param, w + _param);
}

// 
template<class _T>
__forceinline void Vec4<_T>::operator +=(const _T& _param) {
	// Se actualizan los valores de las componentes del vector
	x += _param;	y += _param;	z += _param;	w += _param;
}

// Operadores de resta entre dos vectores
template<class _T>
__forceinline Vec4<_T> Vec4<_T>::operator -(const Vec4<_T>& _param) const {
	// Se calcula el vector resultante y se retorna
	return Vec4<_T>(x - _param.x, y - _param.y, z - _param.z, w - _param.w);
}

// 
template<class _T>
__forceinline void Vec4<_T>::operator -=(const Vec4<_T>& _param) {
	// Se actualizan los valores de las componentes del vector
	x -= _param.x;	y -= _param.y;	z -= _param.z;	w -= _param.w;
}

// Operadores para restarle un flotante a todas las componentes del vector
template<class _T>
__forceinline Vec4<_T> Vec4<_T>::operator -(const _T& _param) const {
	// Se calcula el vector resultante y se retorna
	return Vec4<_T>(x - _param, y - _param, z - _param, w - _param);
}

// 
template<class _T>
__forceinline void Vec4<_T>::operator -=(const _T& _param) {
	// Se actualizan los valores de las componentes del vector
	x -= _param;	y -= _param;	z -= _param;	w -= _param;
}

// Operadores para el producto entre un vector y un escalar
template<class _T>
__forceinline Vec4<_T> Vec4<_T>::operator *(const _T& _param) const {
	// Se calcula el vector resultante y se retorna
	return Vec4<_T>(x * _param, y * _param, z * _param, w * _param);
}

// 
template<class _T>
__forceinline void Vec4<_T>::operator *=(const _T& _param) {
	// Se actualizan los valores de las componentes del vector
	x *= _param;	y *= _param;	z *= _param;	w *= _param;
}

// Operadores para la division entre un vector y un escalar
template<class _T>
__forceinline Vec4<_T> Vec4<_T>::operator /(const _T& _param) const {
	// Se calcula el vector resultante y se retorna
	const _T _t = static_cast<_T>(1) / _param;
	return Vec4<_T>(x * _t, y * _t, z * _t, w * _t);
}

// 
template<class _T>
__forceinline void Vec4<_T>::operator /=(const _T& _param) {
	// Se actualizan los valores de las componentes del vector
	const _T _t = static_cast<_T>(1) / _param;
	x *= _t;	y *= _t;	z *= _t;	w *= _t;
}

// Operadores de comparacion entre vectores
template<class _T>
__forceinline bool Vec4<_T>::operator ==(const Vec4<_T>& _param) const {
	return x == _param.x && y == _param.y && z == _param.z && w == _param.w;
}

template<class _T>
__forceinline bool Vec4<_T>::operator !=(const Vec4<_T>& _param) const {
	return x != _param.x || y != _param.y || z != _param.z || w != _param.w;
}

template<class _T>
__forceinline bool Vec4<_T>::operator <(const Vec4<_T>& _param) const {
	return x < _param.x && y < _param.y && z < _param.z && w < _param.w;
}

template<class _T>
__forceinline bool Vec4<_T>::operator >(const Vec4<_T>& _param) const {
	return x > _param.x && y > _param.y && z > _param.z && w > _param.w;
}

template<class _T>
__forceinline bool Vec4<_T>::operator <=(const Vec4<_T>& _param) const {
	return x <= _param.x && y <= _param.y && z <= _param.z && w <= _param.w;
}

template<class _T>
__forceinline bool Vec4<_T>::operator >=(const Vec4<_T>& _param) const {
	return x >= _param.x && y >= _param.y && z >= _param.z && w >= _param.w;
}

// Operadores de comparacion entre un vector y un flotante
template<class _T>
__forceinline bool Vec4<_T>::operator <(const _T& _param) const {
	return x < _param && y < _param && z < _param && w < _param;
}

template<class _T>
__forceinline bool Vec4<_T>::operator >(const _T& _param) const {
	return x > _param && y > _param && z > _param && w > _param;
}

template<class _T>
__forceinline bool Vec4<_T>::operator <=(const _T& _param) const {
	return x <= _param && y <= _param && z <= _param && w <= _param;
}

template<class _T>
__forceinline bool Vec4<_T>::operator >=(const _T& _param) const {
	return x >= _param && y >= _param && z >= _param && w >= _param;
}

template<class _T>
__forceinline bool Vec4<_T>::operator ==(const _T& _param) const {
	return x == _param && y == _param && z == _param && w == _param;
}

template<class _T>
__forceinline bool Vec4<_T>::operator !=(const _T& _param) const {
	return x != _param && y != _param && z != _param && w != _param;
}

// Metodo para inicializar el vector
template<class _T>
void Vec4<_T>::init() {
	// Se iniicializan los valores de las componentes del vector
	memset(values, 0, sizeof(values));
}

// Metodo para obtener el modulo del vector
template<class _T>
_T Vec4<_T>::module() {
	return sqrt(x*x + y*y + z*z + w*w);
}

// Metodo para normalizar el vector
template<class _T>
void Vec4<_T>::normalize() {
	const _T mod = static_cast<_T> (1) / module();
	x *= mod; y *= mod; z *= mod; w *= mod;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec4<_T>::set(const _T& _tx) {
	// Se actualizan los valores de las componentes del vector
	x = _tx;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec4<_T>::set(const _T& _tx, const _T& _ty) {
	// Se actualizan los valores de las componentes del vector
	x = _tx;	y = _ty;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec4<_T>::set(const _T& _tx, const _T& _ty, const _T& _tz) {
	// Se actualizan los valores de las componentes del vector
	x = _tx;	y = _ty;	z = _tz;
}

// Metodo para ajustar las componentes del vector
template<class _T>
void Vec4<_T>::set(const _T& _tx, const _T& _ty, const _T& _tz, const _T& _tw) {
	// Se actualizan los valores de las componentes del vector
	x = _tx;	y = _ty;	z = _tz;	w = _tw;
}

END_NAMESPACE(Math);
END_PROJECT_NAMESPACE();

#endif  // MATH_VEC4_INL_H__
