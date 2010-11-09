uniform sampler2D colorMap;
uniform sampler2D envMap;

void main (void)
{
	vec4 color = texture2D( colorMap, gl_TexCoord[0].st);
	//vec4 color = vec4(0.0, 0.0, 0.0, 1.0); // yo
	vec4 env = texture2D( envMap, gl_TexCoord[1].st);

	//gl_FragColor = color + env*0.4;
	gl_FragColor = env;
	//gl_FragColor = color + env*0.6; //yo
}
