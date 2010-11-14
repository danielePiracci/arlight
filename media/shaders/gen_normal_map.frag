//
uniform sampler2D height_map;

//
uniform float height_map_width;
uniform float height_map_height;

void main() {
  // 
  float top =    texture2D(height_map, gl_TexCoord[0].st + vec2(0, -1.0 / height_map_height));
  float bottom = texture2D(height_map, gl_TexCoord[0].st + vec2(0, 1.0 / height_map_height));
  float left =   texture2D(height_map, gl_TexCoord[0].st + vec2(-1.0 / height_map_width, 0));
  float right =  texture2D(height_map, gl_TexCoord[0].st + vec2(1.0 / height_map_width, 0));
  
  //
  vec3 zz = vec3(top - bottom, right - left, 1.0);
  zz = normalize(zz);
  zz = (zz * 0.5) + 0.5;
  
  //
  gl_FragColor = vec4(vec3(zz), 1.0);
}
