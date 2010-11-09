

void main(void) {
  // la segunda linea deberia tener la textura de coordenada de 1, pero en el codigo no esta definida de esta manera.
  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_TexCoord[1] = gl_MultiTexCoord0;
  
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 
}
