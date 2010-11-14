
//
uniform sampler2D base_map;
uniform sampler2D normal_map;

//
varying vec3 light_dir;
//varying vec3 view_dir;

//
//const float DiffuseFactor = 1.0;
//const float SpecularFactor = 0.9;
//const float shininess = 128.0;	//1024

void main() {
  // Get the color of the texture and the normal map.
  vec3 base_color = vec3(texture2D(base_map, vec2(gl_TexCoord[0])));
  vec3 normal_color = vec3(texture2D(normal_map, vec2(gl_TexCoord[0])));

  // Expand the bump-map into a normalized signed vector.
  normal_color = (normal_color -0.5) * 2.0;
  
  // Find the dot product between the light direction and the normal.
  float NdotL = max(dot(normal_color, light_dir), 0.0);
  
  // Calculate the final color gl_FragColor.
  gl_FragColor = NdotL * base_color;
}
