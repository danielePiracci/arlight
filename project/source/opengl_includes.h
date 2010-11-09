#ifndef __OPENGL_INCLUDES_H__
#define __OPENGL_INCLUDES_H__

//#define GLEW_STATIC
#include "windows.h"
//
#include "glew.h"
//	#include "glut.h"
//#include "gl.h"
//#include "glu.h"

//#define GLEW_STATIC

//para evitar el error con respecto a la redefinicion de exit
#define GLUT_BUILDING_LIB
	#include "glut.h"
#undef GLUT_BUILDING_LIB



#endif __OPENGL_INCLUDES_H__
