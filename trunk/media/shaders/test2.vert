varying vec3 ReflectDir;
varying vec3 Normal;

void main() {
  gl_Position = ftransform();
  //Normal = normalize(gl_NormalMatrix * gl_Normal);  // - yo
  Normal = -normalize(gl_NormalMatrix * gl_Normal);
  vec4 pos = gl_ModelViewMatrix * gl_Vertex;
  vec3 eyeDir = pos.xyz;
  //ReflectDir = reflect(eyeDir, Normal); // - yo
  ReflectDir = -reflect(eyeDir, Normal);
  
  gl_TexCoord[0]  = gl_MultiTexCoord0;
  gl_TexCoord[1]  = gl_MultiTexCoord0;
}
