
// Function to calculate the spherical map coordinates.
void SetCoord(int index, vec3 v) {
  float m = 2.0 * sqrt(v.x*v.x + v.y*v.y + (v.z+1.0)*(v.z+1.0) );
  gl_TexCoord[index].s = v.x/m + 0.5;
  gl_TexCoord[index].t = v.y/m + 0.5;
}

void main() {
  //
  gl_Position = ftransform();
  gl_TexCoord[0] = gl_MultiTexCoord0;
  
  //
  vec3 u = normalize(vec3(gl_ModelViewMatrix * gl_Vertex));
  vec3 n = normalize(gl_NormalMatrix * gl_Normal);
  vec3 r = reflect(u, n);
  
  // Update texture coordinates.
  SetCoord(1, n);
  SetCoord(2, r);
}
