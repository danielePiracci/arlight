
float diffuse_percent = 0.1;
float specular_percent = 0.9;

uniform sampler2D base_map;
uniform sampler2D diffuse_map;
uniform sampler2D specular_map;

void main() {

  //vec3 base_color = vec3(1.0, 1.0, 1.0);
  vec3 base_color = vec3(0.0, 0.0, 0.0);
  //vec3 base_color = vec3(0.9, 0.9, 0.9);
  
  // Look up environment map values in cube maps
  //vec3 base_color = texture2D(base_map, gl_TexCoord[0].st);
  //vec3 diffuse_color = texture2D(diffuse_map, normalize(Normal));
  //vec3 specular_color = texture2D(specular_map, normalize(ReflectDir));
  vec3 diffuse_color = texture2D(diffuse_map, gl_TexCoord[1].st);
  vec3 specular_color = texture2D(specular_map, gl_TexCoord[2].st);

  // Add lighting to base color and mix
  vec3 color = mix(base_color, diffuse_color * base_color, diffuse_percent);
  color = mix(color, specular_color + color, specular_percent);
  
  gl_FragColor = vec4(color, 1.0);  
}
