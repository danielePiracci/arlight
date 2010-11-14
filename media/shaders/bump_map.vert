//
uniform vec3 light_position;

// The inverse tangent to the geometry.
attribute vec3 tangent;

// The inverse binormal to the geometry
attribute vec3 binormal;

//
varying vec3 light_dir;
//varying vec3 view_dir;

void main() {

  // Construct a 3x3 matrix from the geometry’s inverse tangent, binormal, and normal
  mat3 rotmat = mat3(tangent, binormal, gl_Normal);

  // Rotate the light into tangent space
  light_dir = rotmat * normalize(light_position);
  
  // Normalize the light.
  normalize(light_dir); 

  // Use the first set of texture coordinates in the fragment shader.
  gl_TexCoord[0] = gl_MultiTexCoord0;
  
  // Put the vertex in the position passed.
  gl_Position = ftransform();
}
