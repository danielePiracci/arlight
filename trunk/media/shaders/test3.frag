//uniform vec3 BaseColor;
//uniform float SpecularPercent;
//uniform float DiffusePercent;

vec3 BaseColor = vec3(0.1, 0.1, 0.1);
float SpecularPercent = 0.8; // 1; //0.05;
float DiffusePercent = 0.2;

uniform samplerCube SpecularEnvMap;
uniform samplerCube DiffuseEnvMap;

varying vec3 ReflectDir;
varying vec3 Normal;


uniform sampler2D BaseMap;

void main() {
  // Agregado por mi.....
  vec3 test_color = texture2D(BaseMap, vec2(gl_TexCoord[0]));
  BaseColor = test_color;

  // Look up environment map values in cube maps
  vec3 diffuseColor = vec3(textureCube(DiffuseEnvMap, normalize(Normal)));
  vec3 specularColor = vec3(textureCube(SpecularEnvMap, normalize(ReflectDir)));

  // Add lighting to base color and mix
  vec3 color = mix(BaseColor, diffuseColor*BaseColor, DiffusePercent);
  color = mix(color, specularColor + color, SpecularPercent);
  
  // Added...
  //vec3 envColor = vec3(1.0, 1.0, 1.0);
  
  //gl_FragColor = vec4(envColor, 1.0);
  gl_FragColor = vec4(color, 1.0);
  
  //vec3 test_color = texture2D(BaseMap, vec2(gl_TexCoord[0]));
  //gl_FragColor = vec4(test_color, 1.0);
  
  //gl_FragColor = texture2D(BaseMap, vec2(gl_TexCoord[0]));
  //gl_FragColor = texture2D(BaseMap, normalize(Normal).yz);
}
