/// \file shader/shader.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2006/04/24
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Shader class, 
/// declared at shader/shader.h.
#include "shader/shader.h"
#include "cstdio"
#include "string"

BEGIN_PROJECT_NAMESPACE();

Shader::Shader() { }

Shader::~Shader() { }

//funcion para inicializar los shaders por defecto
void Shader::init()
{
	//se inicializan los shaders
	strcpy(vertexP,"");
	strcpy(fragmentP,"");

	//se inicializa la ruta de los archivos
	strcpy(vPath,"");
	strcpy(fPath,"");
}

//funcion para inicializar los shaders con la ruta del vertex y fragmet program
void Shader::init(char* _vPath, char* _fPath)
{
	//se inicializan los shaders
	strcpy(vertexP,"");
	strcpy(fragmentP,"");

	//se inicializa la ruta de los archivos
	strcpy(vPath, _vPath);
	strcpy(fPath, _fPath);

	//se cargan el vertex y fragment program
	if(!readFile(vPath,VERTEX_SHADER))
		printf("error: No se pudo abrir el vertex program!\n");
	if(!readFile(fPath,FRAGMENT_SHADER))
		printf("error: No se pudo abrir el fragment program!\n");
}

//funcion para habilitar el uso de shaders
void Shader::enable()
{ 
	glUseProgramObjectARB(hProgram); 
}

//funcion para deshabilitar el uso de shaders
void Shader::disable()
{ 
	glUseProgramObjectARB(0);  
}

//funcion para leer los program y almacenarlos en sus respectivo shader
bool Shader::readFile(char* path, const int &type)
{
	FILE* f;	
		
	//se trasta de abrir el archivo
	if(!(f = fopen(path,"r")))	return false;	//ocurrio un error al abrir el archivo
					
	char aux[255];
		
	//se inicializa el vertex o el fragment program 
	if(type == VERTEX_SHADER)	
		strcpy(vertexP,"");
	else // type == FRAGMENT_SHADER	
		strcpy(fragmentP,"");
		
	//se realiza la lectura del archivo
	while(fgets(aux,256,f)!=NULL)
	{
		if(type == VERTEX_SHADER) 
			strcat(vertexP,aux);
		else // type == FRAGMENT_SHADER  
			strcat(fragmentP,aux);	
	}
		
	fclose(f);	//se cierra el archivo

	return true;	//la lectura del archivo fue exitosa
}

//funcion para cargar el vertex program
void Shader::openVertexP(char* _vPath)
{
	//se almacena la ruta del vertex program
	strcpy(vPath, _vPath);

	//se tratan de cargar el vertex program
	if(!readFile(vPath,VERTEX_SHADER))
		printf("error: No se pudo abrir el vertex program!\n");
}

//funcion para cargar el fragment program
void Shader::openFragmentP(char* _fPath)
{
	//se almacena la ruta del fragment program
	strcpy(fPath, _fPath);

	//se tratan de cargar el fragment program
	if(!readFile(fPath,FRAGMENT_SHADER))
		printf("error: No se pudo abrir el fragment program!\n");
}

//funcion para compilar y enlazar los shaders
void Shader::load()
{
	resetLog();		//se reinicia el log

	//se verifica que este cargado el vertex y el fragment
	if(strcmp(vertexP,"") == 0)
		printf("error: falta cargar el vertex shader!\n");
	else if(strcmp(fragmentP,"") == 0)
		printf("error: falta cargar el fragment shader!\n");
	else
	{
       if (glCreateShaderObjectARB == 0)
         printf("Error: shader\n");

		//se crea el handle para el vertex y para el fragment
        //hVertex = glCreateShader(GL_VERTEX_SHADER_ARB);
		hVertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		hFragment = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
		const char* vv = vertexP;
		const char* ff = fragmentP;

		//se carga el codigo del vertex y fragment en sus handles
		glShaderSourceARB(hVertex, 1, &vv, NULL);
		glShaderSourceARB(hFragment, 1, &ff, NULL);
		
		//se compila el vertex y fragment
		glCompileShaderARB(hVertex);
		glCompileShaderARB(hFragment);

		//se crea el handle que une al fragment y al vertex
		hProgram = glCreateProgramObjectARB();
		glAttachObjectARB(hProgram, hFragment);
		glAttachObjectARB(hProgram, hVertex);

		//se enlaza el programa
		glLinkProgramARB(hProgram);

		//se verifica si no ocurrieron errores
		if(!checkError())
		{ 
			printf("error: ocurrio un error al compilar y enlazar los shaders\n");
			//WinExec("notepad.exe \"shaderLog.txt\"",SW_SHOW);
		}
	}
}

//para verificar si no ocurrieron errores en la compilacion o en en enlace
bool Shader::checkError()
{
	int status = 0;	//se inicializa el status

	//para saber si ocurrio un problema al compilar el vertex program
	glGetObjectParameterivARB(hVertex,GL_OBJECT_COMPILE_STATUS_ARB,&status);
	if(!status)	printLog(hVertex,"VERTEX COMPILE");

	//para saber si ocurrio un proble al enlazar el vertex porgram
	glGetObjectParameterivARB(hVertex,GL_OBJECT_LINK_STATUS_ARB,&status);
	if(!status)	printLog(hVertex,"VERTEX LINK");

	//para saber si ocurrio un problema al compilar el fragment program
	glGetObjectParameterivARB(hFragment,GL_OBJECT_COMPILE_STATUS_ARB,&status);
	if(!status)	printLog(hFragment,"FRAGMENT COMPILE");
	
	//para saber si ocurrio un problema al enlazar al frgamet program
	glGetObjectParameterivARB(hFragment,GL_OBJECT_LINK_STATUS_ARB,&status);
	if(!status)	printLog(hFragment,"FRAGMENT LINK");
	
	//para saber si ocurrio un problema al enlazar el program
	glGetObjectParameterivARB(hProgram,GL_OBJECT_LINK_STATUS_ARB,&status);
	if(!status)	printLog(hProgram,"PROGRAM LINK");

	//se verifica si ocurrio algun error
	if(!status) return false;
	return true;
}

//funcion para imprimir en el log de los shaders el resultado de la compilacion y el enlace
void Shader::printLog(GLhandleARB h, char* type)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char* infoLog;

	//se obtiene el tamaño del log
	glGetObjectParameterivARB(h, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);
	
	if(infologLength > 0)	//si el tamaño es mayor a 0
	{
		//se reserva el espacio para el log
		infoLog = (char*) malloc(infologLength);
		
		//se obtiene la informacion del log
		glGetInfoLogARB(h, infologLength, &charsWritten, infoLog);

		FILE* f = fopen("shaderLog.txt", "a+");	//se abre el log de los shaders
		fprintf(f,"***%s***\n",type);	//se imprime el typo de error
		fprintf(f,"%s", infoLog);		//se imprime la informacion del log			
		fprintf(f,"************************\n\n");
		fclose(f);						//se cierra el log de los shaders

		free(infoLog);	//se libera el espacio de memoria
	}
}

//funcion para inicializar el log de los shaders
void Shader::resetLog()
{
	FILE *f;
	f=fopen("shaderLog.txt","w");	//se abre el log de los shaders
	fprintf(f,"%s","");				//se inicializa el log
	fclose(f);						//se cierra el log
}

//funcion para visualizar el vertex program shader
void Shader::showVertexProgram()
{
	char aux[256];

	strcpy(aux,"notepad.exe \"");
	strcat(aux,vPath);
	strcat(aux,"\"");

	//se verifica que este cargado el shader
	if(strcmp(vPath,"")==0)
		printf("error: no hay ningun vertex shader cargado!\n");
//	else	
//		WinExec(aux,SW_SHOW);
}

//funcion para visualizar el fragment program shader
void Shader::showFragmentProgram()
{
	char aux[256];

	strcpy(aux,"notepad.exe \"");
	strcat(aux,fPath);
	strcat(aux,"\"");

	//se verifica que este cargado el shader
	if(strcmp(fPath,"")==0)
		printf("error: no hay ningun fragment shader cargado!\n");
//	else	
//		WinExec(aux,SW_SHOW);
}

//funcion para verificar si el hardware soporta shader
void Shader::support()
{
	m_bSupport = GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader;
}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform1i(char *name, const int &x)
{
	glUniform1iARB(glGetUniformLocationARB(hProgram,name),x);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform1f(char *name, const float &x)
{
	glUniform1fARB(glGetUniformLocationARB(hProgram,name),x);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform2f(char *name, const float &x, const float &y)
{
	glUniform2fARB(glGetUniformLocationARB(hProgram,name),x,y);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform3f(char *name, const float &x, const float &y, const float &z)
{
	glUniform3fARB(glGetUniformLocationARB(hProgram,name),x,y,z);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform4f(char *name, const float &x, const float &y, const float &z, const float &w)
{
	glUniform4fARB(glGetUniformLocationARB(hProgram,name),x,y,z,w);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
//void CSHADER::setUniform3f(char *name, const VEC2 &v)
//{
//	glUniform3fARB(glGetUniformLocationARB(hProgram,name),v.x,v.y);
//}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform3f(char *name, const vec3f &v)
{
	glUniform3fARB(glGetUniformLocationARB(hProgram,name),v.x,v.y,v.z);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
//void SHADER::setUniform4f(char *name, const VEC4 &v)
//{
//	glUniform3fARB(glGetUniformLocationARB(hProgram,name),v.x,v.y,v.z,v.w);
//}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform3fv(char *name, float v[])
{
	glUniform3fARB(glGetUniformLocationARB(hProgram,name),v[0],v[1],v[2]);
}

//funcion para ajustar el valor de una variable uniform dentro del shader
void Shader::setUniform4fv(char *name, float v[])
{
	glUniform4fARB(glGetUniformLocationARB(hProgram,name),v[0],v[1],v[2],v[3]);
}

void Shader::setUniform2fv(char *name, int count, float v[]) {
  glUniform2fv(glGetUniformLocationARB(hProgram,name), count, v);
}

void Shader::setUniform4fv(char *name, int count, float v[]) {
  glUniform4fv(glGetUniformLocationARB(hProgram,name), count, v);
}

// Funciton...
void Shader::setUniformMatrix4fv(char *name, float m[], bool transpose) {
  glUniformMatrix4fv(glGetUniformLocationARB(hProgram,name), 1, transpose, m);
}

//funcion para ajustar el valor de una variable atrribute dentro del shader
void Shader::setAttrib1f(char *name, const float &x)
{
	//glVertexAttrib1fARB(glGetUniformLocationARB(hProgram,name),x);
	glVertexAttrib1fARB(glGetAttribLocationARB(hProgram,name),x);
}

//funcion para ajustar el valor de una variable atrribute dentro del shader
void Shader::setAttrib3f(char *name, const vec3f &v)
{
	//glVertexAttrib1fARB(glGetUniformLocationARB(hProgram,name),x);
	glVertexAttrib3fARB(glGetAttribLocationARB(hProgram,name),v.x,v.y,v.z);
}

//funcion para ajustar el valor de una variable atrribute dentro del shader
void Shader::setAttrib3f(char *name, const float &x, const float &y, const float &z)
{
	//glVertexAttrib1fARB(glGetUniform.LocationARB(hProgram,name),x);
	glVertexAttrib3fARB(glGetAttribLocationARB(hProgram,name),x,y,z);
	//glVertexAttrib3fARB(glGetUniformLocationARB(hProgram,name),x,y,z);
	//revizar en la carpeta de attribute para buscar como se hace
}

//funcion para ajustar el valor de una variable atrribute dentro del shader
void Shader::setAttrib3fv(char *name, const float &x, const float &y, const float &z)
{
	float fv[3];
	fv[0]=x;	fv[0]=y;	fv[0]=z;
	glVertexAttrib3fvARB(glGetAttribLocationARB(hProgram,name),fv);
}

//funcion para ajustar el valor de una variable atrribute dentro del shader
//nota: la variable index debe ser 1,7 o >16 por las otras estan reservadas por ejemplo para
//parasarle al shader el vertice, normales, coordenadeas de textura, etc
//otra cosa importante es llamar antes a la funcion glBindAttribLocation(hProgram, index, name);
void Shader::setAttrib3f(const int &index, const float &x, const float &y, const float &z)
{
	glVertexAttrib3fARB(index,x,y,z);
}

//nota: mejor crear una lista donde se almacena el valor index con su respectivo nombre asociado
//de tal manera de cuando llame  a esta funcion haga el swaping para buscar el index, ya que es
//mas natural llamr a la funcion con el nombre del parametro

END_PROJECT_NAMESPACE();
