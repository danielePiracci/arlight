// TODO: create a default vertex shader, for common use in many effects.

void main() {
  // 
  gl_TexCoord[0] = gl_MultiTexCoord0;
  
  //
  gl_Position = ftransform();
}
