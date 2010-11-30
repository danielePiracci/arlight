/// \file shader/shader.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2006/04/24
/// \version 1.0
// 
/// \brief This file declares the DissertationProject::Shader class, which 
/// implement the basic functionalities of a shader.
#ifndef __SHADER_H__
#define __SHADER_H__

// TODO: implementar el unload del shader....

#include "opengl_includes.h"
//#include "basic-includes.h"
#include "math/vector.h"

BEGIN_PROJECT_NAMESPACE();

enum	//para identificar el tipo de shader
{
	VERTEX_SHADER = 1,
	FRAGMENT_SHADER
};

class Shader {
 public:
  /// \brief Standard constructor.
  Shader();

  /// \brief Default destructor.
  ~Shader();

	GLhandleARB hVertex;	//handle del vertex program
	GLhandleARB hFragment;	//handle del fragment program
	GLhandleARB hProgram;	//handle del program
	
	//char vertexP[2048];		//vertex program
	//char fragmentP[2048];	//fragment program
    char vertexP[8096];		//vertex program
	char fragmentP[8096];	//fragment program
	
	char vPath[256];		//ruta donde esta el programa del vertex shader
	char fPath[256];		//ruta donde esta el programa del fragment shader

	bool m_bSupport;		//para saber si hardware soporta shaders	


	///funciones

	void init();							//funcion para iniclizar el shader por defecto
	void init(char* _vPath, char* _fPath);	//para inicializar el shader con la ruta de los program

	void load();		//funcion para cargar los shaders y compilarlos
	
	void enable();		//funcion para habilitar el uso de shader
    void disable();		//funcion para deshabilitar el uso de shader

	void support();		//funcion para verificar si el hardware soporta shaders

	void openVertexP(char* _vPath);		//funcion para cargar el vertex program
	void openFragmentP(char* _fPath);	//funcion para cargar el fragment program

	bool readFile(char* path, const int &type);	//funcion para leer los shaders

	void showVertexProgram();	//funcion para visualizar el vertex program cargado
	void showFragmentProgram();	//funcion para visualizar el fragment program cargado
	
	void resetLog();	//funcion para inicializar el log de los shaders
	
	bool checkError();	//para verfificar si ocurrio un error en la compilacion o en el enlace de los shaders
	void printLog(GLhandleARB h, char* type);	//para imprimir en el log de los shaders el resultado de la compilacion y del enlace 
	
	
	//funciones para ajustar los parametros del shader
	void setUniform1i(char *name, const int &x);
	
	void setUniform1f(char *name, const float &x);
	void setUniform2f(char *name, const float &x, const float &y);
	void setUniform3f(char *name, const float &x, const float &y, const float &z);
	void setUniform4f(char *name, const float &x, const float &y, const float &z, const float &w);

	//void setUniform3f(char *name, const VEC2 &v);
	void setUniform3f(char *name, const vec3f &v);
	//void setUniform4f(char *name, const VEC4 &v);

	void setUniform3fv(char *name, float v[]);
	void setUniform4fv(char *name, float v[]);

    void setUniform1fv(char *name, int count, float v[]);
    void setUniform2fv(char *name, int count, float v[]);
    void setUniform4fv(char *name, int count, float v[]);

    void setUniformMatrix4fv(char *name, float m[], bool transpose = false);
   

	void setAttrib1f(char *name, const float &x);
	void setAttrib3f(char *name, const vec3f &v);

	void setAttrib3f(char *name, const float &x, const float &y, const float &z);
	void setAttrib3fv(char *name, const float &x, const float &y, const float &z);
	void setAttrib3f(const int &index, const float &x, const float &y, const float &z);
	//nota hacer los que faltan despues!!!

 private:
  DISALLOW_COPY_AND_ASSIGN(Shader);
};

END_PROJECT_NAMESPACE();

#endif __SHADER_H__
