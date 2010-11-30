 //#version 140

//uniform sampler2DShadow shadow_map;

//out vec4 FragColor;

//uniform sampler2D base_map;

//void main() {
  //float shade_factor = textureProj(shadow_map, gl_TexCoord[0]);
  //shade_factor = shade_factor * 0.25 + 0.75;
  
  //FragColor = vec4(1, 0, 0, 1);
  //gl_FragColor = vec4(1, 0, 0, 1);
  //vec4 color = vec4(1, 0, 0, 1);
//  gl_FragColor = vec4(shade_factor * color.rgb, color.a);

  //vec3 test_color = texture2D(base_map, vec2(gl_TexCoord[0]));

  //gl_FragColor = vec4(test_color, 1);
//  gl_FragColor = vec4(1, 0, 0, 1);
//}

// segunda prueba.
//uniform sampler2D shadow_map;
//
//varying vec4 ShadowCoord;
//
//void main() {	
//  vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
//		
//  // Used to lower moiré pattern and self-shadowing
//  shadowCoordinateWdivide.z += 0.0005;
//  
//  float distanceFromLight = texture2D(shadow_map, shadowCoordinateWdivide.st).z;
//  float shadow = 1.0;
//  if (ShadowCoord.w > 0.0)
//    shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;

//  gl_FragColor = shadow * gl_Color;
//  //gl_FragColor = vec4(1, 0, 0, 1);
//  gl_FragColor = vec4(shadow * gl_Color.rgb, 1.0);
//}

/*
//uniform sampler2D shadow_map;
uniform sampler2DShadow shadow_map;
varying vec4 ShadowCoord;

void main() {
	vec3 color = vec3(1, 1, 1);
	color *= shadow2DProj(shadow_map, ShadowCoord).r;
	gl_FragColor = vec4(color, 1);
}
*/
/*
#version 140
uniform sampler2DShadow shadow_map;
varying vec4 ShadowCoord;
out vec4 FragColor;
void main () {
  float shade_factor = textureProj(shadow_map, ShadowCoord);
  shade_factor = shade_factor * 0.25 + 0.75;
  //shade_factor = shade_factor;
  
  vec4 color = vec4(1, 1, 1, 1);
  FragColor = vec4(shade_factor * color.rgb, color.a);
}
*/

// base shadow mapping.
/*
uniform sampler2D shadow_map;
varying vec4 ShadowCoord;

void main() {	
	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
	
	// Used to lower moiré pattern and self-shadowing
	//shadowCoordinateWdivide.z += 0.0005;
	shadowCoordinateWdivide.z -= 0.005;
	
	float distanceFromLight = texture2D(shadow_map, shadowCoordinateWdivide.st).z;
	
	
	float shadow = 1.0;
	if (ShadowCoord.w > 0.0)
		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.2 : 1.0 ;
	
	
	gl_FragColor =	 shadow * gl_Color;
	gl_FragColor = vec4(shadow * gl_Color.rgb, 1.0);
  
}
*/



varying vec4 diffuse, ambientGlobal, ambient;
varying vec3 normal, lightDir, halfVector;
varying float dist;

uniform sampler2DShadow shadow_map;
varying vec4 ShadowCoord;

void main() {
	vec3 n, halfV, viewV, ldir;
	float NdotL, NdotHV;
	vec4 color = ambientGlobal;
	float att;
	
	/* a fragment shader can't write a varying variable, hence we need
	a new variable to store the normalized interpolated normal */
	n = normalize(normal);
	
	/* compute the dot product between normal and normalized lightdir */
	NdotL = max(dot(n, normalize(lightDir)), 0.0);

	if (NdotL > 0.0) {
		att = 1.0 / (gl_LightSource[0].constantAttenuation +
				gl_LightSource[0].linearAttenuation * dist +
				gl_LightSource[0].quadraticAttenuation * dist * dist);
		color += att * (diffuse * NdotL + ambient);
	
		
		halfV = normalize(halfVector);
		NdotHV = max(dot(n, halfV), 0.0);
		color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * 
						pow(NdotHV, gl_FrontMaterial.shininess);
	}

	//gl_FragColor = color;
	
	///
	// calculate the shadow using shadow mapping.
//	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
	//vec4 shadowCoordinateWdivide = ShadowCoord;
	
	// Used to lower moiré pattern and self-shadowing
//	shadowCoordinateWdivide.z += 0.0005;
	//shadowCoordinateWdivide.z -= 0.01;
//	shadowCoordinateWdivide.z -= 0.015;
	//shadowCoordinateWdivide.z -= 0.85;
	
/*	float distanceFromLight = texture2D(shadow_map, shadowCoordinateWdivide.st).z;
	
	
	float shadow = 1.0;
	if (ShadowCoord.w > 0.0)
		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.2 : 1.0 ;
	
	gl_FragColor = vec4(shadow * color.rgb, 1.0);*/
	
	/*
	vec3 coord = 0.5 * (ShadowCoord.xyz / ShadowCoord.w + 1.0);
	//float shadow = texture2D(shadow_map, coord).r;
	float shadow = shadow2D(shadow_map, coord).r;
	shadow = shadow * 0.8 + 0.2;
	gl_FragColor = vec4(shadow * color.rgb, 1.0);*/
	
	/*
	// este funciona del carajo!!
	//vec3 color = vec3(1, 1, 1);
	//ShadowCoord -= ShadowCoord.w * 0.0005;
	//ShadowCoord.z -= ShadowCoord.w * 0.005;
	//ShadowCoord.z -= 0.005;
	float shadow = shadow2DProj(shadow_map, ShadowCoord).r;
	shadow = shadow * 0.8 + 0.2;
	gl_FragColor = vec4(shadow * color.rgb, 1.0);
	*/
	
	/*
	// Mucho mejor
	//ShadowCoord.z -= 0.005;
	float shadeFactor = textureProj(shadow_map, ShadowCoord);
	//shadeFactor = shadeFactor * 0.25 + 0.75;
	shadeFactor = shadeFactor * 0.8 + 0.2;
	gl_FragColor = vec4(shadeFactor * color.rgb, color.a);
	*/
	
	//ShadowCoord.z -= 0.0005;
	
	
	
	float sum;
	
	/*
	vec2 coord = ShadowCoord.xy / ShadowCoord.w;
	
	if (coord.x > 0 && coord.x < 1 &&
	    coord.y > 0 && coord.y < 1) {
	*/
	ShadowCoord.z += ShadowCoord.w * 0.0005;
	
	//sum  = textureProjOffset(shadow_map, ShadowCoord, ivec2(0, 0));
	sum = textureProjOffset(shadow_map, ShadowCoord, ivec2(-1, -1));
	sum += textureProjOffset(shadow_map, ShadowCoord, ivec2( 1, -1));
	sum += textureProjOffset(shadow_map, ShadowCoord, ivec2(-1,  1));
	sum += textureProjOffset(shadow_map, ShadowCoord, ivec2( 1,  1));
	
	//float shadeFactor = textureProj(shadow_map, ShadowCoord);
	//shadeFactor = shadeFactor * 0.25 + 0.75;
	//shadeFactor = shadeFactor * 0.8 + 0.2;
	//gl_FragColor = vec4(shadeFactor * color.rgb, color.a);
	
	
	sum *= 0.25;
	
	//if (sum > 0) sum = 1;
	
	vec2 shadowScaleBias = vec2(0.6, 0.4);
	
	sum = sum * shadowScaleBias.x + shadowScaleBias.y;
	/*
	} else {
	  sum = 1.0;
	}*/
	
	//if (sum != 1.0) min(sum, 0.6);
	gl_FragColor = vec4(sum * color.rgb, color.a);
	
}
