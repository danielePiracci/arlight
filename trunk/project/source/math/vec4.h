/// \file vec4.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
//
// This file define a template class for 3 dimension vectors.
#ifndef MATH_VEC4_H__
#define MATH_VEC4_H__

#include "global.h"
#include <math.h>
#include <memory.h>

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(Math);

// Estructura para representar un vector de 4 dimensiones
template<class _T>
class Vec4 {
public:
	// Definicion de la estructura del Vec3
	// Attributes
	union {
		struct {_T x, y, z, w;};		// Componentes de vector
		struct {_T r, g, b, a;};		// Componentes de color
		struct {_T s, t, p, q;};		// Componentes de textura
		_T values[4];			//
	};
	
	// Constructores del vector
	Vec4();
	Vec4(const _T& _tx);
	Vec4(const _T& _tx, const _T& _ty);
	Vec4(const _T& _tx, const _T& _ty, const _T& _tz);
	Vec4(const _T& _tx, const _T& _ty, const _T& _tz, const _T& _tw);

	// Destructor del vector
	~Vec4();

	// Operadores de asignacion	
	void operator = (const _T& _param);
	void operator = (const Vec4<_T>& _param);
	
	// Operador para obtener un elemento del vector
	_T operator [](const int& _index) const;

	// Operador para incrementar todas las componentes del vector
	void operator ++();

	// Operador para decrementar todas las componentes del vector
	void operator --();

	// Operadores para la suma de dos vectores
	Vec4<_T> operator + (const Vec4<_T>& _param) const;
	void operator +=(const Vec4<_T>& _param);
	
	// Operadores para sumarle a las componentes del vector un flotante
	Vec4<_T> operator + (const _T& _param) const;
	void operator +=(const _T& _param);
	
	// Operadores para la resta de dos vectores
	Vec4<_T> operator - (const Vec4<_T>& _param) const;
	void operator -=(const Vec4<_T>& _param);

	// Operadores para restarle a las componentes del vector un flotante
	Vec4<_T> operator - (const _T& _param) const;
	void operator -=(const _T& _param);
	
	// Operadores para el producto de un vector por un escalar
	Vec4<_T> operator * (const _T& _param) const;
	void operator *=(const _T& _param);
	
	// Operadores para la division de un vector por un escalar
	Vec4<_T> operator / (const _T& _param) const;
	void operator /=(const _T& _param);
	
	// Operadores de comparacion entre dos vectores
	bool operator >  (const Vec4<_T>& _param) const;
	bool operator <  (const Vec4<_T>& _param) const;
	bool operator >= (const Vec4<_T>& _param) const;
	bool operator <= (const Vec4<_T>& _param) const;
	bool operator == (const Vec4<_T>& _param) const;
	bool operator != (const Vec4<_T>& _param) const;

	// Operadores de comparacion entre un vector y un flotante
	bool operator >  (const _T& _param) const;
	bool operator <  (const _T& _param) const;
	bool operator >= (const _T& _param) const;
	bool operator <= (const _T& _param) const;
	bool operator == (const _T& _param) const;
	bool operator != (const _T& _param) const;

	// Metodos
	void init();		// Para inicializar el vector
	_T module();		// Para calcular el modulo del vector
	void normalize();	// Para normalizar el vector
	void set(const _T& _tx);
	void set(const _T& _tx, const _T& _ty);
	void set(const _T& _tx, const _T& _ty, const _T& _tz);
	void set(const _T& _tx, const _T& _ty, const _T& _tz, const _T& _tw);
};


// Constructors
template<class _T>
Vec4<_T>::Vec4() : x(0), y(0), z(0), w(0) { }

template<class _T>
Vec4<_T>::Vec4(const _T& _tx) : x(_tx), y(0), z(0), w(0) { }

template<class _T>
Vec4<_T>::Vec4(const _T& _tx, const _T& _ty) : x(_tx), y(_ty), z(0), w(0) { }

template<class _T>
Vec4<_T>::Vec4(const _T& _tx, const _T& _ty, const _T& _tz)
	: x(_tx), y(_ty), z(_tz), w(0) { }

template<class _T>
Vec4<_T>::Vec4(const _T& _tx, const _T& _ty, const _T& _tz, const _T& _tw)
	: x(_tx), y(_ty), z(_tz), w(_tw) { }

// Destructor
template<class _T>
Vec4<_T>::~Vec4() { }

END_NAMESPACE(Math);
END_PROJECT_NAMESPACE();

#endif  // MATH_VEC4_H__
