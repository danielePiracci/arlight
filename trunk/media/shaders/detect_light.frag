// TODO: pasar imagen en scala de grises.

//uniform sampler2D base_map;
uniform sampler2D env_map;

varying vec3 normal;

void main (void)
{
	//vec4 color = texture2D( colorMap, gl_TexCoord[0].st);
	//vec4 color = vec4(0.0, 0.0, 0.0, 1.0); // yo
	vec4 env = texture2D(env_map, gl_TexCoord[1].st);

	//if (env.x < 0.1) discard;
	//gl_FragColor = color + env*0.4;
	//gl_FragColor = env;
	//gl_FragColor = color + env*0.6; //yo
	//gl_FragColor = vec4(1, 0, 0, 1);
	
	// 
	vec3 norm = normalize(normal);
	//gl_FragColor = vec4(norm * env.x, 1);
	//gl_FragColor = vec4(norm * env.x, 1);
	//if (norm.x < 0) gl_FragColor = vec4(1, 0, 0, 1);
	//else gl_FragColor = vec4(0, 0, 0, 1);
	
	vec3 tmp = norm * env.x;
	//vec3 tmp = norm;
	//vec3 tmp = vec3(-1, 0, 0);
	tmp = tmp * 0.5 + 0.5;
	//tmp.x = tmp.x + 0.6;
	
	//gl_FragColor = vec4(norm.x * 0.5 + 0.5, 0, 0, 1);
	//gl_FragColor = vec4(tmp.x, 0, 0, 1);
	
	//gl_FragColor = vec4(tmp.x, tmp.y, 0, 1);
	gl_FragColor = vec4(tmp, 1);
	
	//if (env.x < 0.7) gl_FragColor = vec4(0);
}
