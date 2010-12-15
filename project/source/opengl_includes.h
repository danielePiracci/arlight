#ifndef __OPENGL_INCLUDES_H__
#define __OPENGL_INCLUDES_H__

#include "windows.h"
#include "glew.h"

// To avoid errors with the redefinition of exit.
#define GLUT_BUILDING_LIB
	#include "glut.h"
#undef GLUT_BUILDING_LIB

#endif __OPENGL_INCLUDES_H__
