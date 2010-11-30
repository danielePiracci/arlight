// NOTE: This frament shader can be used with the default vertex shader program.

//
uniform sampler2D base_map;
uniform sampler2D mask_map;

void main() {
  //
  vec4 base_color = texture2D(base_map, gl_TexCoord[0].st);
  vec4 mask_color = texture2D(mask_map, gl_TexCoord[0].st);
  
  //
  gl_FragColor = mask_color.w > 0 ? mask_color : base_color;
}
