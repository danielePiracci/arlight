varying vec4 ShadowCoord;

void main() {
	gl_Position = ftransform();
	
	// Calculate the shadow mapping.
	ShadowCoord = gl_TextureMatrix[7] * gl_Vertex;
}
