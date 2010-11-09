uniform samplerCube uCubeTexture; 

varying vec3 vView;
varying vec3 vNormal;
varying vec3 vReflected;

void main()
{
	// Samplear del cubo dado el vector reflejado de la superficie
	// GLSL practicamente hace el resto :)
	gl_FragColor = textureCube(uCubeTexture, vReflected);
	//gl_FragColor = vec4(1, 0, 0, 1);
}