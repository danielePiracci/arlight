uniform sampler2D base_map;

void main() {
  // 
  vec4 color = texture2D(base_map, gl_TexCoord[0].st);
  
  // 
  float graycolor = (77.0 * color.r + 151.0 * color.g + 28.0 * color.b) / 256.0;
  
  //
  gl_FragColor = vec4(vec3(graycolor), 1.0);
}
