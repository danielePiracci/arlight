uniform samplerCube uCubeTexture; 

varying vec3 vView;
varying vec3 vNormal;
varying vec3 vReflected;

void main()
{
   gl_TexCoord[0] = gl_MultiTexCoord0;
   gl_TexCoord[1] = gl_MultiTexCoord0;
   // gl_TexCoord[1].xyz = gl_Vertex.xyz;
	//gl_TexCoord[0] = gl_MultiTexCoord0;

	// Calcular el vector normal y el vector ojo
	vNormal = normalize(gl_Normal * gl_NormalMatrix);

	// El vector ojo esta apuntando desde el ojo al vertice
	vView = vec3(gl_Vertex * gl_ModelViewMatrix);

	// Interpolar el vector reflejado 
	vReflected = reflect(vView, vNormal);
	
	gl_Position = ftransform(); 
}