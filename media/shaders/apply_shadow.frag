
// NOTE: This frament shader can be used with the default vertex shader program.
// NOTE: this shader is equivalent to apply mask.

//
uniform sampler2D base_map;
uniform sampler2D shadow_map;

void main() {
  //
  vec4 base_color = texture2D(base_map, gl_TexCoord[0].st);
  vec4 shadow_color = texture2D(shadow_map, gl_TexCoord[0].st);
  
  //
  gl_FragColor = base_color * shadow_color;
  //gl_FragColor = vec4(1, 0, 0, 1);
}
