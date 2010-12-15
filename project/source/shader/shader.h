/// \file shader/shader.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2006/04/24
/// \version 1.0
// 
/// \brief This file declares the DissertationProject::Shader class, which 
/// implement the basic functionalities of a shader.
#ifndef __SHADER_H__
#define __SHADER_H__

#include "opengl_includes.h"
#include "math/vector.h"

BEGIN_PROJECT_NAMESPACE();

// To identify the shader type.
enum {

	VERTEX_SHADER = 1,
	FRAGMENT_SHADER
};

class Shader {
 public:
  /// \brief Standard constructor.
  Shader();

  /// \brief Default destructor.
  ~Shader();

  // Methods to initialize the shader.
  void init();
  void init(char* _vPath, char* _fPath);

  // Methods to load and compile the shaders.
  void load();
	
  // Methods to enable/disable the shader.
  void enable();
  void disable();

  // Method to check if the hardware support shaders.
  void support();

  // Method to load the vertex and frament programs.
  void openVertexP(char* _vPath);
  void openFragmentP(char* _fPath);

  // Method to read the files with the shaders.
  bool readFile(char* path, const int &type);

  // Method to vizualize the vertex and frament program.
  void showVertexProgram();
  void showFragmentProgram();

  // Method to initialize the log of the shaders.
  void resetLog();

  // Method to check if an error arise during the compilation or linkif of the shaders.
  bool checkError();

  // Method to print to a log the result of the compilation and link of the shaders.
  void printLog(GLhandleARB h, char* type);

  // Methods to set the parameters of the shader.
  void setUniform1i(char *name, const int &x);
	
  void setUniform1f(char *name, const float &x);
  void setUniform2f(char *name, const float &x, const float &y);
  void setUniform3f(char *name, const float &x, const float &y, const float &z);
  void setUniform4f(char *name, const float &x, const float &y, const float &z, const float &w);

  void setUniform3f(char *name, const vec3f &v);

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
  // TODO: implement the rest of the methods.

 private:
  // Shader attributes.
  GLhandleARB hVertex;   // Vertex program handler.
  GLhandleARB hFragment; // Fragment program handler.
  GLhandleARB hProgram;  // Program handler.
	
  char vertexP[8096];    // Vertex program.
  char fragmentP[8096];	 // Fragment program.
	
  char vPath[256];       // Path where the vextex program is stored.
  char fPath[256];       // Path where the fragment program is stored.

  bool m_bSupport;       // Flag to know if the hardware support shaders.

  DISALLOW_COPY_AND_ASSIGN(Shader);
};

END_PROJECT_NAMESPACE();

#endif __SHADER_H__
