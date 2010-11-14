// TODO: tratar de implmentar el shader con la ultima especificacion de GLSL.

//#version 140

/*
uniform Transformation {
    mat4 projection_matrix;
    mat4 modelview_matrix;
};
*/

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

in vec3 vertex;

in vec4 MultiTexCoord0;

//out vec2 TexCoord; // utilizar un arreglo en el caso de que sean varias texturas.

/*
void main() {
  //TexCoord = gl_MultiTexCoord0;
  //gl_Position = ftransform();
 // gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0);
  gl_Position = modelview_matrix * vec4(vertex, 1.0);
  TexCoord = MultiTexCoord0.st;
}
*/
void main() {
  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_Position = ftransform();
}
