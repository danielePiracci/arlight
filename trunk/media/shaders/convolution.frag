// implementar con la ultima version de la especificacion.
//#version 140

// maximum size supported by this shader.
const int MaxKernelSize = 25;

// array of offsets ofr accessing the base image.
uniform vec2 Offset[MaxKernelSize];

// Size of kernel (width * height) for this execution.
uniform int KernelSize;

// Value for each location in the convolution kernel.
uniform vec4 KernelValue[MaxKernelSize];

// Image to be convolved.
uniform sampler2D BaseImage;

// Texture coordinate output from vertex shader.
//in vec2 TexCoord;

// Fragment shader output.
//out vec4 FragColor;

void main() {
  int i;
  vec4 sum = vec4(0.0);
  for (i = 0; i < KernelSize; i++) {
    vec4 tmp = texture2D(BaseImage, gl_TexCoord[0].st + Offset[i]);
	sum += tmp * KernelValue[i];
  }
  sum /= KernelSize; //yo
  
  gl_FragColor = sum;
  //gl_FragColor = texture2D(BaseImage, gl_TexCoord[0].st);
  //gl_FragColor = vec4(1, 0, 0, 1);
  //vec4 test = texture2D(BaseImage, gl_TexCoord[0].st + Offset[4]) * KernelValue[4];
  //test += texture2D(BaseImage, gl_TexCoord[0].st + Offset[4]) * KernelValue[4];
  //gl_FragColor = texture2D(BaseImage, gl_TexCoord[0].st + Offset[4]) * KernelValue[4];
  //gl_FragColor = test / 2.0;
  
  // test to generate normal map.
  // primera parte para pasar la imagen a gris.
  vec4 top = texture2D(BaseImage, gl_TexCoord[0].st + Offset[1]);
  vec4 bottom = texture2D(BaseImage, gl_TexCoord[0].st + Offset[7]);
  vec4 left = texture2D(BaseImage, gl_TexCoord[0].st + Offset[3]);
  vec4 right = texture2D(BaseImage, gl_TexCoord[0].st + Offset[5]);
  
  float topg = ((top.r + top.g + top.b) / 3.0);
  float bottomg = ((bottom.r + bottom.g + bottom.b) / 3.0);
  float leftg = ((left.r + left.g + left.b) / 3.0);
  float rightg = ((right.r + right.g + right.b) / 3.0);
  
  vec3 zz = vec3(topg - bottomg, rightg - leftg, 1.0);
  zz = normalize(zz);
  zz = (zz * 0.5) + 0.5;
  
  gl_FragColor = vec4(vec3(zz), 1.0);
  
  // en el caso de que quiera hacer iluminacion de esto
  zz = (zz - 0.5) * 2.0;
  
  vec3 lightDir = vec3(0.2, -1, 0.3);
  lightDir = normalize(lightDir);
  float intensity = max(dot(lightDir, normalize(zz)), 0.0);
  vec4 current = texture2D(BaseImage, gl_TexCoord[0].st + Offset[4]);
  gl_FragColor = current * intensity;
  
  /*
  float sz = (bottomg - topg);
  float tz = (right - left);
  
  float mod_ = sqrt(sz * sz + tz * tz + 1);
  
  vec3 zz = vec3(-sz / mod_, -tz / mod_, 1.0 / mod_);
  */
  
  //vec4 test = 
  //gl_FragColor = vec4(vec3(topg), 1.0);
  //gl_FragColor = vec4(vec3(zz), 1.0);
}



/*#version 140

// maximum size supported by this shader.
const int MaxKernelSize = 25;

// array of offsets ofr accessing the base image.
uniform vec2 Offset[MaxKernelSize];

// Size of kernel (width * height) for this execution.
uniform int KernelSize;

// Value for each location in the convolution kernel.
uniform vec4 KernelValue[MaxKernelSize];

// Image to be convolved.
uniform sampler2D BaseImage;

// Texture coordinate output from vertex shader.
in vec2 TexCoord;

// Fragment shader output.
out vec4 FragColor;

void main() {
  int i;
  vec4 sum = vec4(0.0);
  for (i = 0; i < KernelSize; i++) {
    vec4 tmp = texture(BaseImage, TexCoord.st + Offset[i]);
	sum += tmp * KernelValue[i];
  }
  
  //FragColor = sum;
  //FragColor = texture(BaseImage, TexCoord.st);
  FragColor = vec4(1, 0, 0, 1);
}
*/

/*
#define KERNEL_SIZE 9

uniform sampler2D colorMap;

uniform float width;
uniform float height;
uniform float kernel[KERNEL_SIZE];

const float step_w = 1.0/width;
const float step_h = 1.0/height;
const vec2 offset[KERNEL_SIZE] = {
  vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h),
  vec2(-step_w, 0.0),     vec2(0.0, 0.0),     vec2(step_w, 0.0),
  vec2(-step_w, step_h),  vec2(0.0, step_h),  vec2(step_w, step_h)
};

void main(void) {
   int i = 0;
   vec4 sum = vec4(0.0);

   for(i=0; i<KERNEL_SIZE; i++) {
    vec4 tmp = texture2D(colorMap, gl_TexCoord[0].st + offset[i]);
    sum += tmp * kernel[i];
    sum.a = 1.0;
   }

   gl_FragColor = sum;
}
*/
