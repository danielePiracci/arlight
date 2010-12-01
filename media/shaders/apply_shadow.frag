
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
  //gl_FragColor = base_color * shadow_color;
  if (shadow_color.r != 1 && base_color.a == 0) gl_FragColor = vec4(0, 0, 0, 1 - shadow_color);
  else gl_FragColor = base_color * shadow_color;
}
