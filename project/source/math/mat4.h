/// \file math/mat4.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
//
// This file define a template class for 4x4 matrix.

// TODO: Implement methods ussing SSE.
// TODO: Implement logical operators.

#ifndef MATH_MAT4_H__
#define MATH_MAT4_H__

#include "global.h"
#include "math/vector.h"

#include <math.h>
#include <memory.h>

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(Math);

//estructura para representar una matrix de 4x4
template<class _T>	
class Mat4 {
public:
	// Attributes
	union {
		struct  {
			_T m00, m01, m02, m03;
			_T m10, m11, m12, m13;
			_T m20, m21, m22, m23;
			_T m30, m31, m32, m33;
		};
		struct { Vec4<_T> v[4]; };
		_T f1[4], f2[4], f3[4], f4[4];
		_T m[16];
		_T M[4][4];
	};

	// Constructors
	Mat4();
    Mat4(_T* _m);
	Mat4(_T _m00, _T _m01, _T _m02, _T _m03,
		 _T _m10, _T _m11, _T _m12, _T _m13,
		 _T _m20, _T _m21, _T _m22, _T _m23,
		 _T _m30, _T _m31, _T _m32, _T _m33);

	// operadores de casting
	void operator = (const Mat4<_T> &param);
	
	// operador para obtener un elemento de la matrix
	_T operator [](const int& index)const;

	// operadores para la suma entre dos matrices
	Mat4<_T> operator + (const Mat4<_T>& param) const;
	void operator +=(const Mat4<_T>& param);

	// operadores para la resta entre dos matrices
	Mat4<_T> operator - (const Mat4<_T>& param) const;
	void operator -=(const Mat4<_T>& param);

	// operadores para el producto entre dos matrices
	Mat4<_T> operator * (const Mat4<_T>& param) const;
	void operator *=(const Mat4<_T>& param);

	// operadores para el producto entre una matrix y un vector
	Vec4<_T> operator * (const Vec4<_T>& param) const;

	// Operadores de comparacion
	bool operator == (const Mat4<_T>& param) const;
	bool operator != (const Mat4<_T>& param) const;

	// para inicializar la matrix con ceros
	void init();	
	
	// para inicializar la matrix con este valor en la diagonal
	void set(const _T& t);	
	
	// para inicializar una matrix con estos volres en la diagonal
	void set(const _T& t1, const _T& t2, const _T& t3, const _T& t4);	
	
	// para inicializar la matrix con los valores del vector en la diagonal
	void set(const Vec4<_T>& v);

	// para inicializar la matrix con vectores como filas  
	void set(const Vec4<_T>& v1, const Vec4<_T>& v2, const Vec4<_T>& v3, const Vec4<_T>& v4);

	// 
	void identity();

	// funcion para crear una matrix de sombras
	void createShadowMatrix(Vec4<_T> planeNormal, Vec4<_T> lightPos);

	// funcion para crear una matrix de billboard alineada a los ejes, a partir de un vector de rotacion
	void createAxisAlignedBBMatrix(Vec3<_T> v);

	//nota: -->tambien puedo poner aqui las transfomaciones 

};

// Cosntructors
template<class _T>
Mat4<_T>::Mat4() {
  memset(m, 0, sizeof(m));
}

template<class _T>
Mat4<_T>::Mat4(_T* _m) {
  memcpy(m, _m, sizeof(m));
}

template<class _T>
Mat4<_T>::Mat4(_T _m00, _T _m01, _T _m02, _T _m03,
			   _T _m10, _T _m11, _T _m12, _T _m13,
			   _T _m20, _T _m21, _T _m22, _T _m23,
			   _T _m30, _T _m31, _T _m32, _T _m33) {
	// 
	m00 = _m00; m01 = _m01; m02 = _m02; m03 = _m03;
	m10 = _m10; m11 = _m11; m12 = _m12; m13 = _m13;
	m20 = _m20; m21 = _m21; m22 = _m22; m23 = _m23;
	m30 = _m30; m31 = _m31; m32 = _m32; m33 = _m33;
}

// Operador de casting para una matrix de 4x4
template<class _T>
void Mat4<_T>::operator = (const Mat4<_T>& param) {
	memcpy(m, param.m, sizeof(m));
}

// Operador para obtener un elemento de la matrxi
template<class _T>
_T Mat4<_T>::operator [](const int& index) const {
	return m[index];
}

// Operadores para la suma entre dos matrices
template<class _T>
Mat4<_T> Mat4<_T>::operator + (const Mat4<_T>& param) const {
	return Mat4<_T>(
		m00 + param.m00, m01 + param.m01, m02 + param.m02, m03 + param.m03,
		m10 + param.m10, m11 + param.m11, m12 + param.m12, m13 + param.m13,
		m20 + param.m20, m21 + param.m21, m22 + param.m22, m23 + param.m23,
		m30 + param.m30, m31 + param.m31, m32 + param.m32, m33 + param.m33);
}

template<class _T>
void Mat4<_T>::operator +=(const Mat4<_T>& param) {
	m00 += param.m00; m01 += param.m01;	m02 += param.m02; m03 += param.m03;
	m10 += param.m10; m11 += param.m11;	m12 += param.m12; m13 += param.m13;
	m20 += param.m20; m21 += param.m21;	m22 += param.m22; m23 += param.m23;
	m30 += param.m30; m31 += param.m31;	m32 += param.m32; m33 += param.m33;
}

// Operadores para la resta entre dos matrices
template<class _T>
Mat4<_T> Mat4<_T>::operator - (const Mat4<_T>& param) const {
	return Mat4<_T>(
		m00 - param.m00, m01 - param.m01, m02 - param.m02, m03 - param.m03,
		m10 - param.m10, m11 - param.m11, m12 - param.m12, m13 - param.m13,
		m20 - param.m20, m21 - param.m21, m22 - param.m22, m23 - param.m23,
		m30 - param.m30, m31 - param.m31, m32 - param.m32, m33 - param.m33);
}

template<class _T>
void Mat4<_T>::operator -=(const Mat4<_T>& param) {
	m00 -= param.m00; m01 -= param.m01; m02 -= param.m02; m03 -= param.m03;
	m10 -= param.m10; m11 -= param.m11;	m12 -= param.m12; m13 -= param.m13;
	m20 -= param.m20; m21 -= param.m21;	m22 -= param.m22; m23 -= param.m23;
	m30 -= param.m30; m31 -= param.m31;	m32 -= param.m32; m33 -= param.m33;
}

//operadores para el producto entre dos matrices
template<class _T>
Mat4<_T> Mat4<_T>::operator * (const Mat4<_T>& param) const {
	return Mat4<_T>(
		m00*param.m00 + m01*param.m10 + m02*param.m20 + m03*param.m30, 
		m00*param.m01 + m01*param.m11 + m02*param.m21 + m03*param.m31, 
		m00*param.m02 + m01*param.m12 + m02*param.m22 + m03*param.m32, 
		m00*param.m03 + m01*param.m13 + m02*param.m23 + m03*param.m33, 
		m10*param.m00 + m11*param.m10 + m12*param.m20 + m13*param.m30,  
		m10*param.m01 + m11*param.m11 + m12*param.m21 + m13*param.m31, 
		m10*param.m02 + m11*param.m12 + m12*param.m22 + m13*param.m32, 
		m10*param.m03 + m11*param.m13 + m12*param.m23 + m13*param.m33, 
		m20*param.m00 + m21*param.m10 + m22*param.m20 + m23*param.m30, 
		m20*param.m01 + m21*param.m11 + m22*param.m21 + m23*param.m31, 
		m20*param.m02 + m21*param.m12 + m22*param.m22 + m23*param.m32, 
		m20*param.m03 + m21*param.m13 + m22*param.m23 + m23*param.m33, 
		m30*param.m00 + m31*param.m10 + m32*param.m20 + m33*param.m30,
		m30*param.m01 + m31*param.m11 + m32*param.m21 + m33*param.m31, 
		m30*param.m02 + m31*param.m12 + m32*param.m22 + m33*param.m32, 
		m30*param.m03 + m31*param.m13 + m32*param.m23 + m33*param.m33);
}

template<class _T>
void Mat4<_T>::operator *=(const Mat4<_T> &param) {
	// TODO: Implement ...
}

// Operadores para el producto entre una matrix y un vector
template<class _T>
Vec4<_T> Mat4<_T>::operator * (const Vec4<_T>& param) const {
	return Vec4<_T>(
		m00*param.x + m01*param.y + m02*param.z + m03*param.w,
		m10*param.x + m11*param.y + m12*param.z + m13*param.w,
		m20*param.x + m21*param.y + m22*param.z + m23*param.w,
		m30*param.x + m31*param.y + m32*param.z + m33*param.w);
}

// Operadores de comparacion.
template<class _T>
bool Mat4<_T>::operator == (const Mat4<_T>& param) const {
  return memcmp(m, param.m, sizeof(m)) == 0;
}

template<class _T>
bool Mat4<_T>::operator != (const Mat4<_T>& param) const {
  return memcmp(m, param.m, sizeof(m)) != 0;
}

// Funcion para inicializar la matrix con ceros
template<class _T>
void Mat4<_T>::init() {
	memset(m, 0, sizeof(m));
}

// Funcion para inicializar la diagonal de la matrix con el valor pasado a la funcion
template<class _T>
void Mat4<_T>::set(const _T& t) {
	memset(m, 0, sizeof(m));
	m00 = m11 = m22 = m33 = f;
}
/*
//funcion para inicializar la diagonal de la matrxi con los valores pasados a la funcion
template<class _T>
void Mat4<_T>::init(const _Tt& t1, const _T& t2, const _T& t3, const _T& t4) {
	memset(m, 0, sizeof(m));
	m00 = t1; m11 = t2; m22 = t3; m33 = t4;
}
*/
//funcion para inicializar la diagonal de la matrix con los valores del vector
template<class _T>
void Mat4<_T>::set(const Vec4<_T>& v) {
	memset(m, 0, sizeof(m));
	m00 = v.x; m11 = v.y; m22 = v.z; m33 = v.w;
}

// funcion para inicalizar la matrix con los vectores como filas
template<class _T>
void Mat4<_T>::set(const Vec4<_T>& v1, const Vec4<_T>& v2, const Vec4<_T>& v3, const Vec4<_T>& v4) {
	memcpy(f1, v1.values, sizeof(f1));
	memcpy(f2, v2.values, sizeof(f2));
	memcpy(f3, v3.values, sizeof(f3));
	memcpy(f4, v4.values, sizeof(f4));
}

// Function to create an identity matrix.
template<class _T>
void Mat4<_T>::identity(void) {
  m00 = 1; m01 = 0; m02 = 0; m03 = 0;
  m10 = 0; m11 = 1; m12 = 0; m13 = 0;
  m20 = 0; m21 = 0; m22 = 1; m23 = 0;
  m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

// Funcion para crear una matrix de rotacion alrededor del eja x
template<class _T>
Mat4<_T> rotateX(const float &angle) {
	return Mat4<_T>(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)cos(angle), (float)-sin(angle), 0.0f,
		0.0f, (float)sin(angle), (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Funcion para crear una matrix de rotacion alrededor del eja y
template<class _T>
Mat4<_T> rotateY(const float &angle) {
	return Mat4<_T>(
		(float)cos(angle), 0.0f, (float)sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(float)-sin(angle), 0.0f, (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Funcion para crear una matrix de rotacion alrededor del eja z
template<class _T>
Mat4<_T> rotateZ(const float &angle) {
	return Mat4<_T>(
		(float)cos(angle), (float)-sin(angle), 0.0f, 0.0f,
		(float)sin(angle), (float)cos(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Funcion para crear una matrix de escalacion
template<class _T>
Mat4<_T> scale(const float &sx, const float &sy, const float &sz) {
	return Mat4<_T>(
		sx, 0.0f, 0.0f, 0.0f,
		0.0f, sy, 0.0f, 0.0f,
		0.0f, 0.0f, sz, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Funcion para crear una matrix de traslacion
template<class _T>
Mat4<_T> translate(const float &tx, const float &ty, const float &tz) {
	return Mat4<_T>(
		1.0f, 0.0f, 0.0f, tx,
		0.0f, 1.0f, 0.0f, ty,
		0.0f, 0.0f, 1.0f, tz,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Funcion para obtener la traspuesta asociada a la matrix
template<class _T>
Mat4<_T> transpose(const Mat4<_T> &m) {
	return Mat4<_T>(
		m.m00, m.m10, m.m20, m.m30,
		m.m01, m.m11, m.m21, m.m31,
		m.m02, m.m12, m.m22, m.m32,
		m.m03, m.m13, m.m23, m.m33);
}

// Function to get the inverse of a matrix
// Gauss-Jordan elimination with partial pivoting
template<class _T>
Mat4<_T> inverse(const Mat4<_T> &m) {
	Mat4<_T> a(m),	    // As a evolves from original mat into identity
	b;   // b evolves from identity into inverse(a)
    b.identity();
	int i, j, i1;

	// Loop over cols of a from left to right, eliminating above and below diag
	for (j=0; j<4; j++) {   // Find largest pivot in column j among rows j..3
		i1 = j;		    // Row with largest pivot candidate
		for (i=j+1; i<4; i++)
			if (fabs(a.v[i].values[j]) > fabs(a.v[i1].values[j]))
				i1 = i;

		// Swap rows i1 and j in a and b to put pivot on diagonal
		std::swap(a.v[i1], a.v[j]);
		std::swap(b.v[i1], b.v[j]);

		// Scale row j to have a unit diagonal
		if (a.v[j].values[j]==0.) {
			PRINT_LOG(TYPE_DEBUG, _T("Mat4::inverse: singular matrix; can't invert"));
		}
		b.v[j] /= a.v[j].values[j];
		a.v[j] /= a.v[j].values[j];

		// Eliminate off-diagonal elems in col j of a, doing identical ops to b
		for (i=0; i<4; i++)
			if (i!=j) {
				b.v[i] -= b.v[j]*a.v[i].values[j];
				a.v[i] -= a.v[j]*a.v[i].values[j];
			}
	}
    return b;
}

// Funcion para crear una matrix de sobras
template<class _T>
void Mat4<_T>::createShadowMatrix(Vec4<_T> planeNormal, Vec4<_T> lightPos) {
	// Se calcula el producto punto de plano normal y la posicion de la luz
	float dotProduct = dot4(planeNormal, lightPos);

	m[0]  = dotProduct	- lightPos.x * planeNormal.x;
	m[4]  = 0.0f		- lightPos.x * planeNormal.y;
	m[8]  = 0.0f		- lightPos.x * planeNormal.z;
	m[12] = 0.0f		- lightPos.x * planeNormal.w;

	m[1]  = 0.0f		- lightPos.y * planeNormal.x;
	m[5]  = dotProduct	- lightPos.y * planeNormal.y;
	m[9]  = 0.0f		- lightPos.y * planeNormal.z;
	m[13] = 0.0f		- lightPos.y * planeNormal.w;

	m[2]  = 0.0f		- lightPos.z * planeNormal.x;
	m[6]  = 0.0f		- lightPos.z * planeNormal.y;
	m[10] = dotProduct	- lightPos.z * planeNormal.z;
	m[14] = 0.0f		- lightPos.z * planeNormal.w;

	m[3]  = 0.0f		- lightPos.w * planeNormal.x;
	m[7]  = 0.0f		- lightPos.w * planeNormal.y;
	m[11] = 0.0f		- lightPos.w * planeNormal.z;
	m[15] = dotProduct	- lightPos.w * planeNormal.w;
}

// Funcion para crear una matrix de billboard alineada a los ejes, a partir de un vector de rotacion
template<class _T>
void Mat4<_T>::createAxisAlignedBBMatrix(Vec3<_T> v) {
	float pi    = 3.141592654f;
    float theta = -180 * atan2f(m[8], m[10]) / pi;
    float d     = v.x*v.x + v.y*v.y + v.z*v.z;
    float ct    = cosf(theta * (pi/180.0f));
    float st    = sinf(theta * (pi/180.0f));

    // Normalize
    if (d > 0) {
	    d = 1 / d;
	    v.x *= d;
	    v.y *= d;
	    v.z *= d;
    }

    // Clear out the view matrix passed in
    m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

    //---------------------------------------------
    // R = uu' + cos(theta)*(I-uu') + sin(theta)*S
    //
    // S =  0  -z   y    u' = (x, y, z)
    //	    z   0  -x
    //	   -y   x   0
    //---------------------------------------------

     m[0] = v.x*v.x + ct*(1-v.x*v.x) + st*0;
     m[4] = v.x*v.y + ct*(0-v.x*v.y) + st*-v.z;
     m[8] = v.x*v.z + ct*(0-v.x*v.z) + st*v.y;

     m[1] = v.y*v.x + ct*(0-v.y*v.x) + st*v.z;
     m[5] = v.y*v.y + ct*(1-v.y*v.y) + st*0;
     m[9] = v.y*v.z + ct*(0-v.y*v.z) + st*-v.x;

     m[2] = v.z*v.x + ct*(0-v.z*v.x) + st*-v.y;
     m[6] = v.z*v.y + ct*(0-v.z*v.y) + st*v.x;
     m[10]= v.z*v.z + ct*(1-v.z*v.z) + st*0;
}

END_NAMESPACE(Math);
END_PROJECT_NAMESPACE();

#endif  // MATH_MAT4_H__
