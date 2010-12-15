// TODO: este shader deberia recibir el bias del shadow por parametro,
// de esta forma puedo jugar desde la aplicacion para lograr mejores efectos.

uniform sampler2DShadow shadow_map;
varying vec4 ShadowCoord;

void main() {
  float sum;

  ShadowCoord.z += ShadowCoord.w * 0.0005;
	
  //sum  = textureProjOffset(shadow_map, ShadowCoord, ivec2(0, 0));
  sum = textureProjOffset(shadow_map, ShadowCoord, ivec2(-1, -1));
  sum += textureProjOffset(shadow_map, ShadowCoord, ivec2( 1, -1));
  sum += textureProjOffset(shadow_map, ShadowCoord, ivec2(-1,  1));
  sum += textureProjOffset(shadow_map, ShadowCoord, ivec2( 1,  1));

  sum *= 0.25;
	
	//sum  = textureProjOffset(shadow_map, ShadowCoord, ivec2(0, 0));
  //if (sum > 0) sum = 1;
	
  //vec2 shadowScaleBias = vec2(0.6, 0.4);
  //sum = sum * shadowScaleBias.x + shadowScaleBias.y;
  
  //if (sum != 1.0) sum = min(sum, 0.5);
  //if (sum != 1.0) sum = 0.4;

  //if (sum < 1) sum = sum * 0.05 + 0.8;
  //if (sum < 1) sum = sum * 0.05 + 0.8;
  if (sum < 1) sum = sum * 0.05 + 0.6;
  //if (sum < 1) sum = sum * 0.2 + 0.2;
  gl_FragColor = vec4(sum, sum, sum, 1.0);
  //gl_FragColor = vec4(sum, 0, 0, 1.0);
}
