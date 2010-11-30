// Image to be blurred.
uniform sampler2D base_map;

uniform vec2 offset[16];
uniform float weight[16];

void main() {
  vec4 color = vec4(0.0);
  for (int i = 0; i < 16; i++){
    vec4 tmp = texture2D(base_map, gl_TexCoord[0].st + offset[i]);
    color += weight[i] * tmp;
  }
  color.a = 1.0;
  gl_FragColor = color;
}
