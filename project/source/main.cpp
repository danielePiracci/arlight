/*
 *  simpleLite.c
 *
 *  Some code to demonstrate use of gsub_lite's argl*() functions.
 *  Shows the correct GLUT usage to read a video frame (in the idle callback)
 *  and to draw it (in the display callback).
 *
 *  Press '?' while running for help on available key commands.
 *
 *  Copyright (c) 2001-2007 Philip Lamb (PRL) phil@eden.net.nz. All rights reserved.
 *
 *	Rev		Date		Who		Changes
 *	1.0.0	20040302	PRL		Initial version, simple test animation using GLUT.
 *	1.0.1	20040721	PRL		Correctly sets window size; supports arVideoDispOption().
 *
 */
/*
 * 
 * This file is part of ARToolKit.
 * 
 * ARToolKit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * ARToolKit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ARToolKit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */


// ============================================================================
//	Includes
// ============================================================================

#include <stdio.h>
#include <stdlib.h>					// malloc(), free()

#include "opengl_includes.h"



#include "renderer\opengl_renderer.h"

#include "mesh\mesh_obj.h"

#include "base/locator_inl.h"

#include "shader/shader.h"

#include "renderer/frame_buffer.h"

#include "math/matrix.h"

#include "collision_detection/bounding_box.h"

#include "ctime"

#include "shader/post_process_effect.h"

////////////////////////////////////////////
//// Pruebas para agregar las texturas ...

// TODO: hacer que el objeto no desaparezca tan facilmente cuando no se detecta.

// TODO: implementar un archivo de configuracion con todos los parametros, como por ejemplo
// los tamaños de las texturas, etc... y por ejemplo si utilizar shadows, etc...
// estos valores deben ser definidos en hard code en la applicacion, pero tambien pueden ser 
// redefinidos en el archivo....

DissertationProject::OpenGLRenderer renderer;

//// Prueba para cargar un modelo.
//DissertationProject::MeshObj mesh_test;
boost::shared_ptr<DissertationProject::MeshObj> mesh_test;

boost::shared_ptr<DissertationProject::MeshObj> mesh_sphere;

std::vector<boost::shared_ptr<DissertationProject::MeshObj> > mesh_list;

bool use_mesh_list = false;

bool display_hud = true;

void LoadMeshList();
void DisplayMeshList();
void ReleaseMeshList();

//DissertationProject::Shader shader_test;
boost::shared_ptr<DissertationProject::Shader> shader_test;
boost::shared_ptr<DissertationProject::Shader> convolution_shader;

// Prueba para hacer render to texture.
boost::shared_ptr<DissertationProject::FrameBuffer> frame_buffer;
void RenderToTexture();

// Prueba para generar el heiht map.
boost::shared_ptr<DissertationProject::Shader> grayscale_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> grayscale_framebuffer;
void RenderGrayscaleToTexture();
boost::shared_ptr<DissertationProject::PostProcessEffect> grayscale_effect;

// Prueba para calcular el normal map.
boost::shared_ptr<DissertationProject::Shader> normalmap_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> normalmap_framebuffer;
void RenderNormalMapToTexture();
boost::shared_ptr<DissertationProject::PostProcessEffect> normalmap_effect;

// Prueba para capturar la esfera.
boost::shared_ptr<DissertationProject::FrameBuffer> camera_framebuffer;  // to store the image captured by the camera.
boost::shared_ptr<DissertationProject::FrameBuffer> camera_framebuffer2; // to store the sub-image, where only appears the sphere.
void RenderCameraToTexture(GLdouble *m, GLdouble *p);

DissertationProject::vec3f coord;
DissertationProject::BoundingBox bb;

// Prueba para generar la textura con la mascara.
boost::shared_ptr<DissertationProject::Shader> mask_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> mask_framebuffer;
void RenderMaskToTexture();
boost::shared_ptr<DissertationProject::PostProcessEffect> mask_effect;

// prueba para generar shadow maps.
// TODO: esto en realidad deberia llamarse; soft shadows.
boost::shared_ptr<DissertationProject::Shader> shadowmap_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> shadowmap_framebuffer;
boost::shared_ptr<DissertationProject::FrameBuffer> shadowmap_framebuffer2;
void GenerateShadowMap(GLdouble *modelView, GLdouble *projection);
boost::shared_ptr<DissertationProject::FrameBuffer> frame_buffer2;

boost::shared_ptr<DissertationProject::Shader> modulation_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> modulation_framebuffer;


// prueba para cargar el shader de convolucion...
// Se debe cambiar el nombre de este shader a convolution, blur es temporal.
boost::shared_ptr<DissertationProject::Shader> blur_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> blur_framebuffer;
boost::shared_ptr<DissertationProject::PostProcessEffect> blur_effect;
void ApplyBlurEffectToShadows();
boost::shared_ptr<DissertationProject::FrameBuffer> blur_framebuffer_tmp;

// To swap between framebuffers during tests.
boost::shared_ptr<DissertationProject::FrameBuffer> frame_test;


// prueba para aplicar la textura de sombras sobre la textura de la escena.
boost::shared_ptr<DissertationProject::Shader> apply_shadow_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> apply_shadow_framebuffer;
boost::shared_ptr<DissertationProject::PostProcessEffect> apply_shadow_effect;
void ApplyShadowsToFinalImage();

// Prueba para detectar la fuente de luz.
boost::shared_ptr<DissertationProject::Shader> detect_light_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> detect_light_framebuffer;
boost::shared_ptr<DissertationProject::PostProcessEffect> detect_light_effect;
void DetectLightSource();
boost::shared_ptr<DissertationProject::FrameBuffer> detect_light_framebuffer_tmp;


// Prueba para generar el render de la geometria en un frame buffer aparte.
boost::shared_ptr<DissertationProject::FrameBuffer> scene_framebuffer;
void RenderSceneToFrameBuffer(GLdouble *modelView, GLdouble *projection);


//DissertationProject::vec3f lightPosition(2.0f, 3.0f,-2.0f);
//DissertationProject::vec3f lightPosition(0.0f, 5.0f, 4.0f);
DissertationProject::vec3f lightPosition(0.0f, 2.0f, 1.0f);
//DissertationProject::vec3f lightPos(0, 0, 5.0f);
DissertationProject::vec3f lightPos(0, 0, 8.0f);

DissertationProject::vec3f DetectedLightPos(0, 0, 0.0f);


// prueba para poder hacer swap de los shaders.
boost::shared_ptr<DissertationProject::Shader> temp_shader;

// prueba para poder hacer render con una luz normal.
boost::shared_ptr<DissertationProject::Shader> light_shader;


/// Prueba para desplegar HUD.
void RenderHUD(int found, bool display_hud, bool light_detect);
void RenderRotatingMesh();
void RenderRotatingMesh2();
void LoadData();
void RenderConvolution();
////////////////////////////////////////////


//#ifdef __APPLE__
//#  include <GLUT/glut.h>
//#else
//#  include <GL/glut.h>
//#  include "glut.h"
//#endif


#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>

// ============================================================================
//	Constants
// ============================================================================

#define VIEW_SCALEFACTOR		0.025		// 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
#define VIEW_DISTANCE_MIN		0.1			// Objects closer to the camera than this will not be displayed.
#define VIEW_DISTANCE_MAX		100.0		// Objects further away from the camera than this will not be displayed.

// ============================================================================
//	Global variables
// ============================================================================

// Preferences.
static int prefWindowed = TRUE;
static int prefWidth = 640;					// Fullscreen mode width.
static int prefHeight = 480;				// Fullscreen mode height.
static int prefDepth = 32;					// Fullscreen mode bit depth.
static int prefRefresh = 0;					// Fullscreen mode refresh rate. Set to 0 to use default rate.

// Image acquisition.
static ARUint8		*gARTImage = NULL;

// Marker detection.
static int			gARTThreshhold = 100;
static long			gCallCountMarkerDetect = 0;

// Transformation matrix retrieval.
static double		gPatt_width     = 80.0;	// Per-marker, but we are using only 1 marker.
static double		gPatt_centre[2] = {0.0, 0.0}; // Per-marker, but we are using only 1 marker.
static double		gPatt_trans[3][4];		// Per-marker, but we are using only 1 marker.
static int			gPatt_found = FALSE;	// Per-marker, but we are using only 1 marker.
static int			gPatt_id;				// Per-marker, but we are using only 1 marker.

// Drawing.
static ARParam		gARTCparam;
static ARGL_CONTEXT_SETTINGS_REF gArglSettings = NULL;
static int gDrawRotate = FALSE;
static float gDrawRotateAngle = 0;			// For use in drawing.









//////////////////////////////////
// NOTE: ESTO ES NUEVO, LO AGREGUE SOLO PARA PODER HACER EL HUD.
void ViewOrtho(int x, int y)							// Set Up An Ortho View
{
	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
	glOrtho( 0, x , y , 0, -1, 1 );				// Select Ortho Mode
	glMatrixMode(GL_MODELVIEW);					// Select Modelview Matrix
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
}

void ViewPerspective(void)							// Set Up A Perspective View
{
	glMatrixMode( GL_PROJECTION );					// Select Projection
	glPopMatrix();							// Pop The Matrix
	glMatrixMode( GL_MODELVIEW );					// Select Modelview
	glPopMatrix();							// Pop The Matrix
}
///////////////////////////////////////////






// ============================================================================
//	Functions
// ============================================================================

// Something to look at, draw a rotating colour cube.
static void DrawCube(void)
{

 // glEnable(GL_TEXTURE_2D);
//glBindTexture(GL_TEXTURE_2D, 1);

	// Colour cube data.
	static GLuint polyList = 0;
	float fSize = 0.5f;
	long f, i;	
	const GLfloat cube_vertices [8][3] = {
	{1.0, 1.0, 1.0}, {1.0, -1.0, 1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0},
	{1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0} };
	const GLfloat cube_vertex_colors [8][3] = {
	//{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
	//{1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0} };
	{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0},
	{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0} };
	GLint cube_num_faces = 6;
	const short cube_faces [6][4] = {
	{3, 2, 1, 0}, {2, 3, 7, 6}, {0, 1, 5, 4}, {3, 0, 4, 7}, {1, 2, 6, 5}, {4, 5, 6, 7} };
	
    //const GLfloat cube_textcoord [8][3] = {
	//{1.0, 1.0, 1.0}, {1.0, -1.0, 1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0},
	//{1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0} };
	
   
	if (!polyList) {
		polyList = glGenLists (1);
		glNewList(polyList, GL_COMPILE);
		glBegin (GL_QUADS);
		for (f = 0; f < cube_num_faces; f++)
			for (i = 0; i < 4; i++) {
				glColor3f (cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
			}
		glEnd ();
		glColor3f (0.0, 0.0, 0.0);
		for (f = 0; f < cube_num_faces; f++) {
			glBegin (GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
			glEnd ();
		}
		glEndList ();
	}
	
	glPushMatrix(); // Save world coordinate system.
	glTranslatef(0.0, 0.0, 5.5); // Place base of cube on marker surface.
	glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glScalef(3, 3, 3);
	glDisable(GL_LIGHTING);	// Just use colours.
	glCallList(polyList);	// Draw the cube.
	glPopMatrix();	// Restore world coordinate system.
	


  
  //glBindTexture(GL_TEXTURE_2D, 0);
  //glDisable(GL_TEXTURE_2D);
}

static void DrawCubeUpdate(float timeDelta)
{
	if (gDrawRotate) {
		gDrawRotateAngle += timeDelta * 45.0f; // Rotate cube at 45 degrees per second.
		if (gDrawRotateAngle > 360.0f) gDrawRotateAngle -= 360.0f;
	}
}

static int setupCamera(const char *cparam_name, char *vconf, ARParam *cparam)
{	
    ARParam			wparam;
	int				xsize, ysize;

    // Open the video path.
    if (arVideoOpen(vconf) < 0) {
    	fprintf(stderr, "setupCamera(): Unable to open connection to camera.\n");
    	return (FALSE);
	}
	
    // Find the size of the window.
    if (arVideoInqSize(&xsize, &ysize) < 0) return (FALSE);
    fprintf(stdout, "Camera image size (x,y) = (%d,%d)\n", xsize, ysize);
	
	// Load the camera parameters, resize for the window and init.
    if (arParamLoad(cparam_name, 1, &wparam) < 0) {
		fprintf(stderr, "setupCamera(): Error loading parameter file %s for camera.\n", cparam_name);
        return (FALSE);
    }
    arParamChangeSize(&wparam, xsize, ysize, cparam);
    fprintf(stdout, "*** Camera Parameter ***\n");
    arParamDisp(cparam);
	
    arInitCparam(cparam);

	if (arVideoCapStart() != 0) {
    	fprintf(stderr, "setupCamera(): Unable to begin camera data capture.\n");
		return (FALSE);		
	}
	
	return (TRUE);
}

static int setupMarker(const char *patt_name, int *patt_id)
{
	// Loading only 1 pattern in this example.
	if ((*patt_id = arLoadPatt(patt_name)) < 0) {
		fprintf(stderr, "setupMarker(): pattern load error !!\n");
		return (FALSE);
	}

	return (TRUE);
}

// Report state of ARToolKit global variables arFittingMode,
// arImageProcMode, arglDrawMode, arTemplateMatchingMode, arMatchingPCAMode.
static void debugReportMode(const ARGL_CONTEXT_SETTINGS_REF arglContextSettings)
{
	if (arFittingMode == AR_FITTING_TO_INPUT) {
		fprintf(stderr, "FittingMode (Z): INPUT IMAGE\n");
	} else {
		fprintf(stderr, "FittingMode (Z): COMPENSATED IMAGE\n");
	}
	
	if (arImageProcMode == AR_IMAGE_PROC_IN_FULL) {
		fprintf(stderr, "ProcMode (X)   : FULL IMAGE\n");
	} else {
		fprintf(stderr, "ProcMode (X)   : HALF IMAGE\n");
	}
	
	if (arglDrawModeGet(arglContextSettings) == AR_DRAW_BY_GL_DRAW_PIXELS) {
		fprintf(stderr, "DrawMode (C)   : GL_DRAW_PIXELS\n");
	} else if (arglTexmapModeGet(arglContextSettings) == AR_DRAW_TEXTURE_FULL_IMAGE) {
		fprintf(stderr, "DrawMode (C)   : TEXTURE MAPPING (FULL RESOLUTION)\n");
	} else {
		fprintf(stderr, "DrawMode (C)   : TEXTURE MAPPING (HALF RESOLUTION)\n");
	}
		
	if (arTemplateMatchingMode == AR_TEMPLATE_MATCHING_COLOR) {
		fprintf(stderr, "TemplateMatchingMode (M)   : Color Template\n");
	} else {
		fprintf(stderr, "TemplateMatchingMode (M)   : BW Template\n");
	}
	
	if (arMatchingPCAMode == AR_MATCHING_WITHOUT_PCA) {
		fprintf(stderr, "MatchingPCAMode (P)   : Without PCA\n");
	} else {
		fprintf(stderr, "MatchingPCAMode (P)   : With PCA\n");
	}
}

static void cleanup(void)
{
	arglCleanup(gArglSettings);
	arVideoCapStop();
	arVideoClose();

  // To release all the resources.
  ReleaseMeshList();
  DissertationProject::Locator::Release();

  mesh_sphere.reset();

  // Delete shaders.
  // TODO: tener un shader manager, de tal manera de poder eliminarlos todos facilmetne.
  shader_test.reset();
  convolution_shader.reset();
  grayscale_shader.reset();
  normalmap_shader.reset();
  mask_shader.reset();
  temp_shader.reset();
  light_shader.reset();
  blur_shader.reset();
  apply_shadow_shader.reset();
  detect_light_shader.reset();

  frame_buffer.reset();
  grayscale_framebuffer.reset();
  normalmap_framebuffer.reset();
  camera_framebuffer.reset();
  camera_framebuffer2.reset();
  mask_framebuffer.reset();
  frame_buffer2.reset();
  shadowmap_framebuffer.reset();
  shadowmap_framebuffer2.reset();
  modulation_framebuffer.reset();
  blur_framebuffer.reset();
  blur_framebuffer_tmp.reset();
  apply_shadow_framebuffer.reset();
  detect_light_framebuffer.reset();
  detect_light_framebuffer_tmp.reset();

  mask_effect.reset();
  normalmap_effect.reset();
  grayscale_effect.reset();
  blur_effect.reset();
  apply_shadow_effect.reset();
  detect_light_effect.reset();
}

static void processSpecialKeys(int key, int x, int y) {
  static int cnt = 0;
  
  switch (key) {
    case GLUT_KEY_LEFT:
      lightPosition.x -= 0.1;
      lightPos.x -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      lightPosition.x += 0.1;
      lightPos.x += 0.1;
      break;
    case GLUT_KEY_UP:
      lightPosition.y -= 0.1;
      lightPos.y -= 0.1;
      break;
    case GLUT_KEY_DOWN:
      lightPosition.y += 0.1;
      lightPos.y += 0.1;
      break;
    case GLUT_KEY_F1:
      //frame_test = cnt % 2 ? blur_framebuffer : modulation_framebuffer;
      //  frame_test = cnt % 2 ? blur_framebuffer : apply_shadow_framebuffer;
      display_hud = !display_hud;
        cnt++;
      break;
    default:
      break;
  };
}

static void Keyboard(unsigned char key, int x, int y)
{
	int mode, threshChange = 0;
	
	switch (key) {
		case 0x1B:						// Quit.
		case 'Q':
		case 'q':
			cleanup();
			exit(0);
			break;
		case ' ':
			//gDrawRotate = !gDrawRotate;
            std::swap(temp_shader, shader_test);
			break;
		case 'C':
		case 'c':
			mode = arglDrawModeGet(gArglSettings);
			if (mode == AR_DRAW_BY_GL_DRAW_PIXELS) {
				arglDrawModeSet(gArglSettings, AR_DRAW_BY_TEXTURE_MAPPING);
				arglTexmapModeSet(gArglSettings, AR_DRAW_TEXTURE_FULL_IMAGE);
			} else {
				mode = arglTexmapModeGet(gArglSettings);
				if (mode == AR_DRAW_TEXTURE_FULL_IMAGE)	arglTexmapModeSet(gArglSettings, AR_DRAW_TEXTURE_HALF_IMAGE);
				else arglDrawModeSet(gArglSettings, AR_DRAW_BY_GL_DRAW_PIXELS);
			}
			fprintf(stderr, "*** Camera - %f (frame/sec)\n", (double)gCallCountMarkerDetect/arUtilTimer());
			gCallCountMarkerDetect = 0;
			arUtilTimerReset();
			debugReportMode(gArglSettings);
			break;
		case '-':
			threshChange = -5;
			break;
		case '+':
		case '=':
			threshChange = +5;
			break;
		case 'D':
		case 'd':
			arDebug = !arDebug;
			break;
		case '?':
		case '/':
			printf("Keys:\n");
			printf(" q or [esc]    Quit demo.\n");
			printf(" c             Change arglDrawMode and arglTexmapMode.\n");
			printf(" - and +       Adjust threshhold.\n");
			printf(" d             Activate / deactivate debug mode.\n");
			printf(" ? or /        Show this help.\n");
			printf("\nAdditionally, the ARVideo library supplied the following help text:\n");
			arVideoDispOption();
			break;

        default:
			break;
	}
	if (threshChange) {
		gARTThreshhold += threshChange;
		if (gARTThreshhold < 0) gARTThreshhold = 0;
		if (gARTThreshhold > 255) gARTThreshhold = 255;
		printf("Threshhold changed to %d.\n", gARTThreshhold);
	}
}

static void mainLoop(void)
{
	static int ms_prev;
	int ms;
	float s_elapsed;
	ARUint8 *image;

	ARMarkerInfo    *marker_info;					// Pointer to array holding the details of detected markers.
    int             marker_num;						// Count of number of markers detected.
    int             j, k;
	
	// Find out how long since mainLoop() last ran.
	ms = glutGet(GLUT_ELAPSED_TIME);
	s_elapsed = (float)(ms - ms_prev) * 0.001;
	if (s_elapsed < 0.01f) return; // Don't update more often than 100 Hz.
	ms_prev = ms;
	
	// Update drawing.
	DrawCubeUpdate(s_elapsed);
	
	// Grab a video frame.
	if ((image = arVideoGetImage()) != NULL) {
		gARTImage = image;	// Save the fetched image.
		
		gCallCountMarkerDetect++; // Increment ARToolKit FPS counter.
		
		// Detect the markers in the video frame.
		if (arDetectMarker(gARTImage, gARTThreshhold, &marker_info, &marker_num) < 0) {
			exit(-1);
		}
		
		// Check through the marker_info array for highest confidence
		// visible marker matching our preferred pattern.
		k = -1;
		for (j = 0; j < marker_num; j++) {
			if (marker_info[j].id == gPatt_id) {
				if (k == -1) k = j; // First marker detected.
				else if(marker_info[j].cf > marker_info[k].cf) k = j; // Higher confidence marker detected.
			}
		}
		
		if (k != -1) {
			// Get the transformation between the marker and the real camera into gPatt_trans.
			arGetTransMat(&(marker_info[k]), gPatt_centre, gPatt_width, gPatt_trans);
			gPatt_found = TRUE;
		} else {
			gPatt_found = FALSE;
		}
		
		// Tell GLUT the display has changed.
		//glutPostRedisplay();
	}
glutPostRedisplay();
}

//
//	This function is called on events when the visibility of the
//	GLUT window changes (including when it first becomes visible).
//
static void Visibility(int visible)
{
	if (visible == GLUT_VISIBLE) {
		glutIdleFunc(mainLoop);
	} else {
		glutIdleFunc(NULL);
	}
}

//
//	This function is called when the
//	GLUT window is resized.
//
static void Reshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Call through to anyone else who needs to know about window sizing here.
}

void CalculateFps2() {
  static clock_t last = clock();
  static int fps = 0;
  static std::string message;

  clock_t current = clock();
  if (current - last >= 1000) {
    //printf("FPS: %d\n", fps);
    char buffer[100];
    sprintf(buffer, " FPS: %d\n", fps);
    message = buffer;
    fps = 0;
    last = current;
  }
  fps++;

   // TODO: colocar estos mensajes 

  // Pintar mensajes de texto
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    ///glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);
    glPushAttrib(GL_VIEWPORT_BIT);
    //gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    gluOrtho2D(0, 640, 480, 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    const int kTittleHeight = 15;

    glRasterPos2f(10, kTittleHeight + 22);
    for(unsigned int i=0; i<message.size(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, message[i]);

    //Print text
    std::string message2 = "<<<<<< >>>>>>>";
    glRasterPos2f(10, kTittleHeight + 10);
    for(unsigned int i=0; i<message2.size(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, message2[i]);

    //reset matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void CalculateFps() {
  static clock_t last = clock();
  static int fps = 0;

  clock_t current = clock();
  if (current - last >= 1000) {
    printf("FPS: %d\n", fps);
    fps = 0;
    last = current;
  }
  fps++;
}

void displayGeometry1() {
  //glPushMatrix();
  //  glTranslatef(0, 0, 1);

  //  if (use_mesh_list) glScalef(0.25, 0.25, 0.25);
  //  else glScalef(2, 2, 2);

  //  glRotatef(90, 1, 0, 0);

  //  DisplayMeshList();
  //glPopMatrix();

  // prueba para incluir las transformaciones en la matrix de la luz.
  glPushMatrix();
    glTranslatef(0, 0, 1);

    if (use_mesh_list) glScalef(0.25, 0.25, 0.25);
    else glScalef(2, 2, 2);

    glRotatef(90, 1, 0, 0);

    glActiveTexture(GL_TEXTURE7);
    glMatrixMode(GL_TEXTURE);

    glPushMatrix();
      glTranslatef(0, 0, 1);
      if (use_mesh_list) glScalef(0.25, 0.25, 0.25);
      else glScalef(2, 2, 2);
      glRotatef(90, 1, 0, 0);

      DisplayMeshList();
    glPopMatrix();

    // restore to default values.
    glActiveTexture(GL_TEXTURE0);
    glMatrixMode(GL_MODELVIEW);
    
  glPopMatrix();
}

void displayGeometry2() {
  glPushMatrix();
    //glTranslatef(0, -1, 0);
    //glScalef(2, 2, 2);
    glRotatef(90, 1, 0, 0);

    glActiveTexture(GL_TEXTURE7);
    glMatrixMode(GL_TEXTURE);

    glPushMatrix();
      glRotatef(90, 1, 0, 0);

      glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-10, 0, -10);
        glNormal3f(0, 1, 0);
        glVertex3f(-10, 0, 10);
        glNormal3f(0, 1, 0);
        glVertex3f(10, 0, 10);
        glNormal3f(0, 1, 0);
        glVertex3f(10, 0, -10);
      glEnd();
    glPopMatrix();

    // restore to default values.
    glActiveTexture(GL_TEXTURE0);
    glMatrixMode(GL_MODELVIEW);

  glPopMatrix();
}

void DrawLights(GLdouble *m, GLdouble *p) {


  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  //glLoadMatrixd(p);    

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  //glLoadMatrixd(m);    


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 640.0 / 480, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

  //// Prueba para pintar la luz
  glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, 0, -3);
    glScalef(0.25, 0.25, 0.25);
    //mesh_sphere->drawSurface(0);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(DetectedLightPos.x, DetectedLightPos.y, DetectedLightPos.z);
    //glTranslatef(DetectedLightPos.x, DetectedLightPos.y, -3);
    glScalef(0.25, 0.25, 0.25);
    //mesh_sphere->drawSurface(0);
  glPopMatrix();
  /////

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void defaultGometryDisplay(int geometries) {
  boost::shared_ptr<DissertationProject::TextureManager> textures = DissertationProject::Locator::GetTextureManager();

  glActiveTexture(GL_TEXTURE0);
  //glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  textures->EnableTexture("base_map");

  glActiveTexture(GL_TEXTURE1);
  //glEnable(GL_TEXTURE_CUBE_MAP_EXT);
  //textures->EnableTexture("env_map");
  //textures->EnableTexture("env");
  mask_framebuffer->Bind();

  glActiveTexture(GL_TEXTURE2);
  textures->EnableTexture("diff_env_map");

  shader_test->enable();

  shader_test->setUniform1i("BaseMap", 0);

  // para test 2
  shader_test->setUniform1i("DiffuseEnvMap", 2);
  shader_test->setUniform1i("SpecularEnvMap", 1);

  /// para sem.frag
  shader_test->setUniform1i("colorMap", 0);
  shader_test->setUniform1i("envMap", 1);

  /// para multitexturing
  shader_test->setUniform1i("myTexture1", 0);
  shader_test->setUniform1i("myTexture2", 1);

  // para cube_test.frag
  shader_test->setUniform1i("uCubeTexture", 1);

  if (geometries & (1<<0)) displayGeometry1();

  shader_test->disable();

  //glBindTexture(GL_TEXTURE_2D, 0);
  //glDisable(GL_TEXTURE_2D);

  //glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, 0);
  //glDisable(GL_TEXTURE_CUBE_MAP_EXT);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  glDisable(GL_TEXTURE_CUBE_MAP);
    
  //glActiveTexture(GL_TEXTURE1);
  //glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  //glDisable(GL_TEXTURE_CUBE_MAP);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  if (geometries & (1<<1)) displayGeometry2();
}

//
// This function is called when the window needs redrawing.
//
static void Display(void) {
  // TODO: crear una clase timer para poder hacer pruebas de cuanto se demora ciertas 
  // tareas en mi codigo, luego utilizar estos logs en el documento que escriba.

  // NOTE: recordar que voy a cambiar la funcion de visibility para poder hacer cosas en tiempo real.
  // pero de alguna manera tengo que controlar que lo que mando a pintar solo debe ser actualizado 
  // con esa ultima imagen que fue capturada, por lo que podria meter eso uno de mis frame buffers.

    GLdouble p[16];
	GLdouble m[16];

    // parche para que el objeto nunca desaparezca
	static GLdouble prev_m[16];
    static GLdouble prev_p[16];
	
	// Select correct buffer for this context.
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers for new frame.
	
	arglDispImage(gARTImage, &gARTCparam, 1.0, gArglSettings);	// zoom = 1.0.
	arVideoCapNext();

    // Prueba para guardar la imagen.
    camera_framebuffer->Bind();
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 640, 480);
    glBindTexture(GL_TEXTURE_2D, 0);

//	gARTImage = NULL; // Image data is no longer valid after calling arVideoCapNext().
				
	// Projection transformation.
	arglCameraFrustumRH(&gARTCparam, VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, p);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(p);
	glMatrixMode(GL_MODELVIEW);
		
	// Viewing transformation.
	glLoadIdentity();
	// Lighting and geometry that moves with the camera should go here.
	// (I.e. must be specified before viewing transformations.)
	//none

    // parche para que el objeto nunca desaparezca.
	if (gPatt_found) {
      arglCameraViewRH(gPatt_trans, m, VIEW_SCALEFACTOR);
	  glLoadMatrixd(m);
      memcpy(prev_m, m, sizeof(m));
      memcpy(prev_p, p, sizeof(p));
    } else {
      glLoadMatrixd(prev_m);
    }

    // Prueba para generar la textura con la esfera. Solo es actualizada la 
    // textura si el patron es detectado.
    if (gPatt_found) {
      RenderCameraToTexture(prev_m, p);
    }

	if (gPatt_found) {
    // if (true) {
	
		// Calculate the camera position relative to the marker.
		// Replace VIEW_SCALEFACTOR with 1.0 to make one drawing unit equal to 1.0 ARToolKit units (usually millimeters).
		arglCameraViewRH(gPatt_trans, m, VIEW_SCALEFACTOR);
		glLoadMatrixd(m);

		// All lighting and geometry to be drawn relative to the marker goes here.
		//DrawCube();
        //defaultGometryDisplay();

	} // gPatt_found
	
	// Any 2D overlays go here.
	//none
	
    // prueba para pintar un skybox...
    //RenderRotatingMesh2();

    ////////////////////////////////////
    // NOTE: PRueba para pintar los HUD de la aplicacion.
    // TODO: hacer que los hud se desplieguen a travez de un manager que se 
    // encargue de hacer esta funcionalidad. Tener en cuenta que el tamaño de 
    // la ventana es importante al mommento de hacer el viewOrtho, por lo que 
    // este valor deberia ser accessible desde cualquier punto de la aplicacion.

    // Prueba para montar la imagen de la camara en una textura.
    // RenderCameraToTexture(prev_m, p);

    // Prueba para aplicar la mascara a la textura.
    RenderMaskToTexture();

    //RenderRotatingMesh();

    // Prueba para generar el render de la escena en un buffer aparte.
    RenderSceneToFrameBuffer(prev_m, prev_p);

    // Prueba para probar el shader de convolution.
    //RenderConvolution();

    // Prueba para render to texture.
//    RenderToTexture();

    // prueba para generar el shadow map.
    GenerateShadowMap(prev_m, prev_p);

    // Prueba para calcular el grayscale.
    RenderGrayscaleToTexture();

    // prueba para generar el normal map.
    //RenderNormalMapToTexture();

    // 
    DetectLightSource();
    /////////////////////////////////////

    /// Prueba para desplegar HUD del programa.
    //RenderHUD(gPatt_found, display_hud, false);
    RenderHUD(gPatt_found, false, display_hud);

    // prueba para desplegar las fuentes de luz.
    DrawLights(prev_m, prev_p);

    //CalculateFps();
    //CalculateFps2();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
    ///////////////////////////////////////////
    // NOTE: prueba para cargar las texturas //
    // Initialize the services on the application.
    DissertationProject::Locator::Initilize();
    DissertationProject::Locator::Register(boost::shared_ptr<DissertationProject::OpenGLRenderer> (new DissertationProject::OpenGLRenderer()));
    ///////////////////////////////////////////


	char glutGamemode[32];
	char *cparam_name = "../../Data/camera_para.dat";
	char *vconf = "";
	//char *patt_name  = "Data/patt.hiro";
    char *patt_name  = "../../Data/patt.sample1";
	
	// ----------------------------------------------------------------------------
	// Library inits.
	//
	glutInit(&argc, argv);

	// ----------------------------------------------------------------------------
	// Hardware setup.
	//

	if (!setupCamera(cparam_name, vconf, &gARTCparam)) {
		fprintf(stderr, "main(): Unable to set up AR camera.\n");
		exit(-1);
	}

	// ----------------------------------------------------------------------------
	// Library setup.
	//

	// Set up GL context(s) for OpenGL to draw into.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	if (!prefWindowed) {
		if (prefRefresh) sprintf(glutGamemode, "%ix%i:%i@%i", prefWidth, prefHeight, prefDepth, prefRefresh);
		else sprintf(glutGamemode, "%ix%i:%i", prefWidth, prefHeight, prefDepth);
		glutGameModeString(glutGamemode);
		glutEnterGameMode();
	} else {
		glutInitWindowSize(prefWidth, prefHeight);
		glutCreateWindow(argv[0]);
	}

	// Setup ARgsub_lite library for current OpenGL context.
	if ((gArglSettings = arglSetupForCurrentContext()) == NULL) {
		fprintf(stderr, "main(): arglSetupForCurrentContext() returned error.\n");
		cleanup();
		exit(-1);
	}
	debugReportMode(gArglSettings);
	glEnable(GL_DEPTH_TEST);
	arUtilTimerReset();
	
	// Load marker(s).
	if (!setupMarker(patt_name, &gPatt_id)) {
		fprintf(stderr, "main(): Unable to set up AR marker.\n");
		cleanup();
		exit(-1);
	}
	
	// Register GLUT event-handling callbacks.
	// NB: mainLoop() is registered by Visibility.
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutVisibilityFunc(Visibility);
	glutKeyboardFunc(Keyboard);
    glutSpecialFunc(processSpecialKeys);
	
    
    // NOTE: glew debe ser inicializado despues de inicializar glut
    // Initialize the use of glew
	if (GLEW_OK != glewInit()) 
       printf("glewinit fail!.\n");

    // Load the data related to the application.
    LoadData();

	glutMainLoop();
}

void LoadData() {
  // TODO: crear una variable de entorno, la cual define el punto de entrada de los archivos, 
  // luego todas las direcciones son castedas a esta direccion global.

  //// prueba para crear el frame buffer.
  frame_buffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_BGRA, true));
//frame_buffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1, 1));

 // frame_buffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(256, 256, GL_DEPTH_COMPONENT, false));

  //////////////////////////////////////////////
  //// Pruebas para cargar las texturas.
  //renderer.LoadTexture("../../media/textures/skin.tif");
  //renderer.LoadTexture("../../media/textures/box.bmp");
  //renderer.LoadTexture("../../media/textures/logo2.png");
  //renderer.LoadTexture("../../media/textures/uffizi_probe.hdr");
  //renderer.LoadTexture("../../media/textures/cube/cube_face_posx.bmp");
  //renderer.LoadCubeTexture("../../media/textures/..");

  boost::shared_ptr<DissertationProject::TextureManager> textures = DissertationProject::Locator::GetTextureManager();
  //textures->RegisterTexture2D("base_map", "../../media/textures/box.bmp");
  //textures->RegisterTexture2D("base_map", "../../media/textures/skin.tif");
  textures->RegisterTexture2D("logo", "../../media/textures/logo2.png");
  textures->RegisterTexture2D("env", "../../media/textures/env3.jpg");
  textures->RegisterTexture2D("base_map", "../../media/textures/env3.jpg");
  textures->RegisterTexture2D("mask", "../../media/textures/mask.png");

  //textures->RegisterTextureCubeMap("env_map", "../../media/textures/cube2/opensea.png");
  //textures->RegisterTextureCubeMap("env_map", "../../media/textures/cube/cube_face.bmp");
  textures->RegisterTextureCubeMap("env_map", "../../media/textures/cubeSpe/cube_face.bmp");
  textures->RegisterTextureCubeMap("diff_env_map", "../../media/textures/cubeDiff/cube_face.bmp");


  //////////////////////////////////////////////
  //// Pruebas para cargar los meshes.
  // TODO: crear una variable global que defina el path de la aplicacion actual.
  mesh_test = boost::shared_ptr<DissertationProject::MeshObj> (new DissertationProject::MeshObj());
 // mesh_test->Load("../../media/mesh/cube.obj");
 // mesh_test->Load("../../media/mesh/sphere.obj");
 //  mesh_test->Load("../../media/mesh/apple.obj");
  mesh_test->Load("../../media/mesh/bigguy.obj");
  LoadMeshList();

  mesh_sphere = boost::shared_ptr<DissertationProject::MeshObj> (new DissertationProject::MeshObj());
  mesh_sphere->Load("../../media/mesh/sphere.obj");
                                                                                                                                                                                                         
  //////////////////////////////////////////////
  //// Pruebas para cargar los shaders.
  shader_test = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
   
  //shader_test->openVertexP("../../media/shaders/test.vert");
  //shader_test->openFragmentP("../../media/shaders/test.frag");

  //shader_test->openVertexP("../../media/shaders/test2.vert");
  //shader_test->openFragmentP("../../media/shaders/test2.frag");

  //shader_test->openVertexP("../../media/shaders/test3.vert");
  //shader_test->openFragmentP("../../media/shaders/test3.frag");

  //shader_test->openVertexP("../../media/shaders/point_light.vert");
  //shader_test->openFragmentP("../../media/shaders/point_light.frag");

  //shader_test->openVertexP("../../media/shaders/toon_shading.vert");
  //shader_test->openFragmentP("../../media/shaders/toon_shading.frag");

  //shader_test->openVertexP("../../media/shaders/texture_light.vert");
  //shader_test->openFragmentP("../../media/shaders/texture_light.frag");

  shader_test->openVertexP("../../media/shaders/sem.vert");
  shader_test->openFragmentP("../../media/shaders/sem.frag");

  //shader_test->openVertexP("../../media/shaders/light1.vert");
  //shader_test->openFragmentP("../../media/shaders/light1.frag");

  //shader_test->openVertexP("../../media/shaders/multitexturing.vert");
  //shader_test->openFragmentP("../../media/shaders/multitexturing.frag");

  //shader_test->openVertexP("../../media/shaders/cube_test.vert");
  //shader_test->openFragmentP("../../media/shaders/cube_test.frag");

  shader_test->load();

  // prueba para poder hacer swap de los shaders.
  temp_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  temp_shader->openVertexP("../../media/shaders/test3.vert");
  temp_shader->openFragmentP("../../media/shaders/test3.frag");
  temp_shader->load();


  // prueba para cargar el shader de convolution.
  convolution_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  convolution_shader->openVertexP("../../media/shaders/convolution.vert");
  convolution_shader->openFragmentP("../../media/shaders/convolution.frag");

  convolution_shader->load();
  

  // Crear la data para el grayscale shader.
  grayscale_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  grayscale_shader->openVertexP("../../media/shaders/grayscale.vert");
  grayscale_shader->openFragmentP("../../media/shaders/grayscale.frag");
  grayscale_shader->load();
  
  //grayscale_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(256, 256, GL_BGRA, true));
  
  boost::shared_ptr<DissertationProject::Texture> base_map = DissertationProject::Locator::GetTextureManager()->GetTexture("base_map");
  grayscale_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(base_map->width(), base_map->height(), GL_BGRA, true));
  grayscale_effect = boost::shared_ptr<DissertationProject::PostProcessEffect> (new DissertationProject::PostProcessEffect(grayscale_shader, grayscale_framebuffer));

  // prueba para crear el shader y el framebuffer para generar el normal map.
  normalmap_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  normalmap_shader->openVertexP("../../media/shaders/gen_normal_map.vert");
  normalmap_shader->openFragmentP("../../media/shaders/gen_normal_map.frag");
  normalmap_shader->load();
  normalmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(base_map->width(), base_map->height(), GL_BGRA, true));
  normalmap_effect = boost::shared_ptr<DissertationProject::PostProcessEffect> (new DissertationProject::PostProcessEffect(normalmap_shader, normalmap_framebuffer));

  // prueba para capturar la imagen de la camara.
  camera_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));
  camera_framebuffer2 = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(128, 128, GL_BGRA, true));

  // prueba para generar la textura con la mascara.
  mask_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  mask_shader->openVertexP("../../media/shaders/apply_mask.vert");
  mask_shader->openFragmentP("../../media/shaders/apply_mask.frag");
  mask_shader->load();  
  mask_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(128, 128, GL_BGRA, true));
  mask_effect = boost::shared_ptr<DissertationProject::PostProcessEffect> (new DissertationProject::PostProcessEffect(mask_shader, mask_framebuffer));


  // prueba para generar el shadowmap.
  shadowmap_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  shadowmap_shader->openVertexP("../../media/shaders/shadow_map.vert");
  shadowmap_shader->openFragmentP("../../media/shaders/shadow_map.frag");
  shadowmap_shader->load();  
 // shadowmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_DEPTH_COMPONENT));
//  shadowmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(512, 512, GL_DEPTH_COMPONENT));
 // shadowmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(128, 128, GL_BGRA, true));
 //shadowmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));

 //shadowmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(256, 256, GL_BGRA, true));
 shadowmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_DEPTH_COMPONENT));
 shadowmap_framebuffer2 = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_DEPTH_COMPONENT));

  frame_buffer2 = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_BGRA, true));
  

  modulation_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  modulation_shader->openVertexP("../../media/shaders/modulation.vert");
  modulation_shader->openFragmentP("../../media/shaders/modulation.frag");
  modulation_shader->load();  
  //modulation_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_BGRA, true));
  modulation_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));

  // TODO: recordar colocar este chequeo en los shaders!!.
  //if (glCreateShaderObjectARB == 0)
  //  printf("Error: shader\n");

  // prrueba para utilizar un shader de luz normal.
  light_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  light_shader->openVertexP("../../media/shaders/point_light.vert");
  light_shader->openFragmentP("../../media/shaders/point_light.frag");
  light_shader->load();  


  // prueba para generar la textura con blur.
  blur_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  blur_shader->openVertexP("../../media/shaders/blur.vert");
  blur_shader->openFragmentP("../../media/shaders/blur.frag");
  blur_shader->load();  
  //blur_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_BGRA, true));
  blur_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));
  blur_effect = boost::shared_ptr<DissertationProject::PostProcessEffect> (new DissertationProject::PostProcessEffect(blur_shader, blur_framebuffer));
  //blur_framebuffer_tmp = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_BGRA, true));
  blur_framebuffer_tmp = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));


  frame_test = blur_framebuffer;

  // prueba componer las imagenes del render final junto con el de las sombras.
  apply_shadow_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  apply_shadow_shader->openVertexP("../../media/shaders/apply_shadow.vert");
  apply_shadow_shader->openFragmentP("../../media/shaders/apply_shadow.frag");
  apply_shadow_shader->load();  
  //apply_shadow_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(1024, 1024, GL_BGRA, true));
  apply_shadow_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));
  apply_shadow_effect = boost::shared_ptr<DissertationProject::PostProcessEffect> (new DissertationProject::PostProcessEffect(apply_shadow_shader, apply_shadow_framebuffer));
  
  scene_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));


  // prueba para detectar la fuente de luz.
  detect_light_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  detect_light_shader->openVertexP("../../media/shaders/detect_light.vert");
  detect_light_shader->openFragmentP("../../media/shaders/detect_light.frag");
  detect_light_shader->load();  
  detect_light_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(128, 128, GL_BGRA, true));
  detect_light_framebuffer_tmp = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(128, 128, GL_BGRA, true));
  detect_light_effect = boost::shared_ptr<DissertationProject::PostProcessEffect> (new DissertationProject::PostProcessEffect(detect_light_shader, detect_light_framebuffer));
}

// Prueba para detectar la fuente de luz
void DetectLightSource() {


  detect_light_framebuffer->Enable();

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //camera_framebuffer2->Bind();
    grayscale_framebuffer->Bind();

    glTranslatef(0, 0, -1.4);
  
    detect_light_shader->enable();
      detect_light_shader->setUniform1i("env_map", 0);

      mesh_sphere->drawSurface(0);
      //DisplayMeshList();

    detect_light_shader->disable();

  ///////////////////////////////////////////////////////////////////
  // Try to read the data.
  const int kWidth = detect_light_framebuffer->width();
  const int kHeight = detect_light_framebuffer->height();

  //GLbyte pixels[4 * kWidth * kHeight];
  //GLbyte pixels[4 * 128 * 128];
  //glReadPixels(0, 0, kWidth, kHeight, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

  GLfloat pixels[4 * 128 * 128];
  glReadPixels(0, 0, kWidth, kHeight, GL_BGRA, GL_FLOAT, pixels);

  int cnt = 0;
  DissertationProject::vec3f v(0, 0, 0);
  for (int i = 0; i < kHeight; ++i) {
    for (int j = 0; j < kWidth; ++j) {
      if (pixels[(i * kWidth + j) * 4 + 3] < 0.1) continue;
      v.r += (pixels[(i * kWidth + j) * 4 + 2] - 0.5) * 2;
      v.g += (pixels[(i * kWidth + j) * 4 + 1] - 0.5) * 2;
      v.b += (pixels[(i * kWidth + j) * 4 + 0] - 0.5) * 2;
      cnt++;
    }
  }

  

  //v *= 1.0 / (kWidth * kHeight);
  v *= 1.0 / cnt;
  v.y *= -1;

  //printf("%.4f %.4f %.4f\n", v.r, v.g, v.b);

//v.normalize();

  //DetectedLightPos = v * 5;
  //DetectedLightPos.x = 5 * v.x;

  

  DetectedLightPos.z = 3 + v.y * 10;
  DetectedLightPos.x = v.x * 10;
  DetectedLightPos.y = v.z * 2;


/*
DetectedLightPos.x = v.x * 5;
//DetectedLightPos.y = 0.5 + v.y;
DetectedLightPos.y = v.y * 5;
DetectedLightPos.z = 1;
*/

/*
DetectedLightPos = v;
DetectedLightPos.y += 1.0;
DetectedLightPos.z = 1; 
*/

//DetectedLightPos = DissertationProject::vec3f(0, 8, 3);

  ///////////////////////////////////////////////////////////////////


  detect_light_framebuffer->Disable();


}

void RenderRotatingMesh2() {
    glLoadIdentity();
    
shader_test->enable();

shader_test->setUniform1i("uCubeTexture", 1);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, 1);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_CUBE_MAP, 2);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glTranslatef(1.2, -0.8, -5);
//glTranslatef(0, 0, -5);

    static float rot = 0;
    rot += 5;
    //glRotatef(rot, 0, 1, 0);
    //glRotatef(180, 0, 0, 1);

   glScalef(50, 50, 50);
    
    mesh_test->drawSurface(0);

    glDisable(GL_BLEND);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, 0);

shader_test->disable();	
}

void RenderRotatingMesh() {
    //glDisable(GL_LIGHTING);

    glLoadIdentity();

    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(1.2, -0.8, -5);

    static float rot = 0;
    rot += 5;
    glRotatef(rot, 0, 1, 0);

    
    mesh_test->drawSurface(0);

    glDisable(GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void RenderConvolution() {
  boost::shared_ptr<DissertationProject::TextureManager> textures =
      DissertationProject::Locator::GetTextureManager();

    glEnable(GL_TEXTURE_2D);
    //textures->EnableTexture("env");
    //textures->EnableTexture("base_map");
    frame_buffer->Bind();
//grayscale_framebuffer->Bind();

convolution_shader->enable();

//GLfloat m[16];

// TODO: provar la version de shaders actual con los cambios que hice, es 
// decir utilizando el convolution_shader, por que antes se lo pasaba al otro shader.
//glMatrixMode(GL_PROJECTION);
//glGetFloatv(GL_PROJECTION_MATRIX, m);
//convolution_shader->setUniformMatrix4fv("projection_matrix", m, true);

//convolution_shader->setUniform1i("KernelSize", 1);
//GLfloat KernelValue[] = {
//  1.0, 1.0, 1.0, 1.0
//};
//convolution_shader->setUniform4fv("KernelValue", 1, KernelValue);

// revisar por que aparece ese brillo.
convolution_shader->setUniform1i("KernelSize", 9);
GLfloat KernelValue[] = {
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0,
  1.0, 1.0, 1.0, 1.0
};
convolution_shader->setUniform4fv("KernelValue", 9, KernelValue);

const float step_w = 1.0/128; /// 1/width
const float step_h = 1.0/128;  /// 1/height

GLfloat Offset[] = {
  -step_w, -step_h,  0.0, -step_h,  step_w, -step_h,
  -step_w, 0.0,      0.0, 0.0,      step_w, 0.0,
  -step_w, step_h,   0.0, step_h,   step_w, step_h
};
convolution_shader->setUniform2fv("Offset", 9, Offset);
//glMatrixMode(GL_MODELVIEW);
//glGetFloatv(GL_MODELVIEW_MATRIX, m);
//convolution_shader->setUniformMatrix4fv("modelview_matrix", m, false);

convolution_shader->setUniform1i("BaseImage", 0);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    ViewOrtho(640, 480);
    
    glTranslatef(384, 352, 0);

    glColor4f(1, 1, 1, 1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 1);
      glVertex2f(0, 0);
      glTexCoord2f(1, 1);
      glVertex2f(128, 0);
      glTexCoord2f(1, 0);
      glVertex2f(128, 128);
      glTexCoord2f(0, 0);
      glVertex2f(0, 128);
    glEnd();
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    ViewPerspective();

convolution_shader->disable();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

// TODO: este metodo debe llamarse UpdateSphereTexture o algo por el estilo.
void RenderCameraToTexture(GLdouble *m, GLdouble *p) {
  // Calculate the texture's coordinates.
  DissertationProject::mat4d modelview(m);
  DissertationProject::mat4d projection(p);

  modelview = DissertationProject::Math::transpose(modelview);
  projection = DissertationProject::Math::transpose(projection);

  DissertationProject::mat4d pm = projection * modelview;

  std::vector<DissertationProject::vec3f> points;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      for (int k = -1; k <= 1; ++k) {
        // Generate the point.
        DissertationProject::vec4d point(i, j, k, 1);

        const double kSphereSize = 0.13; //0.10; //0.14;

        // scale the point
        point *= kSphereSize;
        point.w = 1;

        // Translate the point.
        point += DissertationProject::vec4d(0, -1.5, kSphereSize, 0);

        DissertationProject::vec4d position = pm * point;
        if (position.w > 0) position /= position.w;
        position = position * 0.5 + 0.5;
        points.push_back(DissertationProject::vec3f (position.x, position.y, 0));
      }
    }
  }

  bb.Init(points[0]);
  const int kNumberOfPoints = static_cast<int> (points.size());
  for (int i = 0; i < kNumberOfPoints; ++i)
    bb.Update(points[i]);

  // Mode debug...
  //printf("%.2f %.2f  -  %.2f %.2f\n", bb.min_point().x, bb.min_point().y, bb.max_point().x, bb.max_point().y);

  if (bb.min_point().x < 0 || bb.max_point().x > 1 ||
      bb.min_point().y < 0 || bb.max_point().y > 1) return;


  camera_framebuffer2->Enable();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // verificar si no tengo que colocar esto de otra manera.
  const int kWidth = camera_framebuffer2->width();
  const int kHeight = camera_framebuffer2->height();
  glOrtho(0, kWidth, kHeight, 0, -1, 1);

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_TEXTURE_2D);
  camera_framebuffer->Bind();

   glColor4f(1, 1, 1, 1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(bb.min_point().x, bb.max_point().y);
      glVertex2f(0, 0);
      glTexCoord2f(bb.max_point().x, bb.max_point().y);
      glVertex2f(kWidth, 0);
      glTexCoord2f(bb.max_point().x, bb.min_point().y);
      glVertex2f(kWidth, kHeight);
      glTexCoord2f(bb.min_point().x, bb.min_point().y);
      glVertex2f(0, kHeight);
    glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  camera_framebuffer2->Disable();

//  

//  glClearColor(0, 0, 0, 1);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glDrawBuffer(GL_BACK);
//gArglSettings = arglSetupForCurrentContext();
 /* glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 1);
*/
  //arglDispImage(gARTImage, &gARTCparam, 1.0, gArglSettings);	// zoom = 1.0.

/*
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
 */

}

/////////////////////////////////////////////////
// To generate de data of a gaussian filter...
float GaussianDistribution(float x, float y, float rho) {
  rho *= rho;
  const float kPi = 2.0 * acos(0.0);
  float g = 1.0f / sqrt(2.0f * kPi * rho);
  return g * exp((x * x + y * y) / (-2.0f * rho));
}

void GetGaussianOffsets(const float texelsz[2], float offset[16][2], float weight[16], bool bHorizontal) {
  const float kBlurSize = 3.0;

  // Get the center texel offset and weight
  weight[0] = 1.0f * GaussianDistribution(0.0f, 0.f, kBlurSize);
  offset[0][0] = offset[0][1] = 0.0f;

  // Get the offsets and weights for the remaining taps
  if (bHorizontal) {
    for( int i = 1; i < 15; i += 2 ) {
      offset[i][0] = float(i) * texelsz[0];
      offset[i][1] = 0.0f;
      offset[i+1][0] = float(-i) * texelsz[0];
      offset[i+1][1] = 0.0f;
      weight[i] = 2.0f * GaussianDistribution(i, 0.0f, kBlurSize);
      weight[i+1] = 2.0f * GaussianDistribution(i + 1.0f, 0.0f, kBlurSize);
    }
  } else {
    for( int i = 1; i < 15; i += 2 ) {
      offset[i][0] = 0.0f;
      offset[i][1] = float(i) * texelsz[1];
      offset[i+1][0] = 0.0f;
      offset[i+1][1] = float(-i) * texelsz[1];
      weight[i] = 2.0f * GaussianDistribution(0.0f, i, kBlurSize);
      weight[i+1] = 2.0f * GaussianDistribution(0.0f, i + 1.0f, kBlurSize);
    }
  }
}

void GenerateOffsetArray(int size, float step, GLfloat offset[][2]) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      offset[i * size + j][0] = (j - size / 2) * step;
      offset[i * size + j][1] = (i - size / 2) * step;
    }
  }
}

void GenerateKernelArray(int size, float step, GLfloat *kernel) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      kernel[i * size + j] = step;
    }
  }
}

void ApplyBlurEffectToShadows() {
  ////GLfloat KernelValue[] = {
  ////  1.0, 1.0, 1.0,
  ////  1.0, 1.0, 1.0,
  ////  1.0, 1.0, 1.0
  ////};

  ////GLfloat KernelValue[] = {
  ////  1.0/9, 1.0/9, 1.0/9,
  ////  1.0/9, 1.0/9, 1.0/9,
  ////  1.0/9, 1.0/9, 1.0/9
  ////};

  ///*GLfloat KernelValue[] = {
  //  0, 1.0/5, 0,
  //  1.0/5, 1.0/5, 1.0/5,
  //  0, 1.0/5, 0
  //};*/

  //GLfloat KernelValue[49];

  //GenerateKernelArray(7, 1.0 / 49.0, KernelValue);

  ////const float step_w = 1.0/128; /// 1/width
  ////const float step_h = 1.0/128;  /// 1/height
  //const float step_w = 1.0 / modulation_framebuffer->width(); /// 1/width
  //const float step_h = 1.0 / modulation_framebuffer->height();  /// 1/height

  ////GLfloat Offset[][2] = {
  ////  {-step_w, -step_h},  {0.0, -step_h},  {step_w, -step_h},
  ////  {-step_w, 0.0},      {0.0, 0.0},      {step_w, 0.0},
  ////  {-step_w, step_h},   {0.0, step_h},   {step_w, step_h}
  ////};

  //GLfloat Offset[49][2];
  //GenerateOffsetArray(7, step_w, Offset);

  //glActiveTexture(GL_TEXTURE0);
  //modulation_framebuffer->Bind();

  //blur_effect->Enable();
  //  blur_effect->shader()->setUniform1i("base_map", 0);

  //  blur_effect->shader()->setUniform1i("KernelSize", 49);
  //  blur_effect->shader()->setUniform1fv("KernelValue", 49, KernelValue);
  //  blur_effect->shader()->setUniform2fv("Offset", 49, &Offset[0][0]);

  //  //blur_shader->setUniform1i("base_map", 0);
  //blur_effect->Disable();

  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D, 0);

//////////
  GLfloat h_offset[16][2], h_weight[16];
  GLfloat v_offset[16][2], v_weight[16];

  memset(h_weight, 0, sizeof(h_weight));
  memset(v_weight, 0, sizeof(v_weight));
  memset(h_offset, 0, sizeof(h_offset));
  memset(v_offset, 0, sizeof(v_offset));

  const float texel_size[2] = { 1.0 / blur_effect->frame_buffer()->width(),
                            1.0 / blur_effect->frame_buffer()->height() };

  GetGaussianOffsets(texel_size, h_offset, h_weight, true);
  GetGaussianOffsets(texel_size, v_offset, v_weight, false);

  ////
  // First pass, horizontal blur.
  glActiveTexture(GL_TEXTURE0);
  modulation_framebuffer->Bind();
  //camera_framebuffer->Bind();

  blur_effect->Enable();
    blur_effect->shader()->setUniform1i("base_map", 0);
    blur_effect->shader()->setUniform1fv("weight", 16, &h_weight[0]);
    blur_effect->shader()->setUniform2fv("offset", 16, &h_offset[0][0]);
  blur_effect->Disable();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);

  ////
  // Store the changes in modulation, TODO: use a different texture...
  glActiveTexture(GL_TEXTURE0);
  blur_framebuffer_tmp->Bind();

  blur_framebuffer->Enable();
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, blur_framebuffer->width(), blur_framebuffer->height());
  blur_framebuffer->Disable();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);

  ////
  // Second pass, vertical blur.
  glActiveTexture(GL_TEXTURE0);
  //modulation_framebuffer->Bind();
  blur_framebuffer_tmp->Bind();

  blur_effect->Enable();
    blur_effect->shader()->setUniform1i("base_map", 0);
    blur_effect->shader()->setUniform1fv("weight", 16, &v_weight[0]);
    blur_effect->shader()->setUniform2fv("offset", 16, &v_offset[0][0]);
  blur_effect->Disable();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void ApplyShadowsToFinalImage() {
  glActiveTexture(GL_TEXTURE0);
  //frame_buffer->Bind();
  scene_framebuffer->Bind();

  glActiveTexture(GL_TEXTURE1);
  blur_framebuffer_tmp->Bind();

  apply_shadow_effect->Enable();
    apply_shadow_effect->shader()->setUniform1i("base_map", 0);
    apply_shadow_effect->shader()->setUniform1i("shadow_map", 1);
  apply_shadow_effect->Disable();

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawShadowTestScene(float angle) {
  glColor4f(1, 1, 1, 1.0f);

glPushMatrix();

  glRotatef(angle, 0, 1, 0);
 // glTranslatef(0, 0, -2);

  //static float angle = 0;
  //angle += 1;
  //glRotatef(angle, 0, 1, 0);
  //glScalef(2, 2, 2);

  glActiveTexture(GL_TEXTURE7);
  glMatrixMode(GL_TEXTURE);
  glPushMatrix();
    // concatening all matrix into one.
    glRotatef(angle, 0, 1, 0);

    DisplayMeshList();

  glPopMatrix();
  // restore to default values.
  glActiveTexture(GL_TEXTURE0);
  glMatrixMode(GL_MODELVIEW);

glPopMatrix();

  // Pintar un plano....
glPushMatrix();
  //glTranslatef(0, -1, 0);
  //glScalef(2, 2, 2);
  /*glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-1, 0, -1);
    glNormal3f(0, 1, 0);
    glVertex3f(-1, 0, 1);
    glNormal3f(0, 1, 0);
    glVertex3f(1, 0, 1);
    glNormal3f(0, 1, 0);
    glVertex3f(1, 0, -1);
  glEnd();*/

  glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-2, -0.5, -2);
    glNormal3f(0, 1, 0);
    glVertex3f(-2, -0.5, 2);
    glNormal3f(0, 1, 0);
    glVertex3f(2, -0.5, 2);
    glNormal3f(0, 1, 0);
    glVertex3f(2, -0.5, -2);
  glEnd();

glPopMatrix();
}

void RenderToTexture() {
  static float angle2 = 0;
  angle2 += 1;

//return;
  frame_buffer->Enable();
  
// Init -> TODO: hacer esto en otra parte.
  GLfloat lightProjectionMatrix[16], lightViewMatrix[16];
  GLfloat cameraProjectionMatrix[16], cameraViewMatrix[16];

  //DissertationProject::vec3f cameraPosition(-2.5f, 3.5f,-2.5f);
DissertationProject::vec3f cameraPosition(0, 1, 2);
  //DissertationProject::vec3f lightPosition(2.0f, 3.0f,-2.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);

  glLoadIdentity();
  gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);

  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 1.0f, 8.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);

  glLoadIdentity();
  gluLookAt(lightPosition.x, lightPosition.y, lightPosition.z,
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f);
//  glRotatef(angle2, 0, 1, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);

    //First pass - from light's point of view
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(lightProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(lightViewMatrix);

    //Use viewport the same size as the shadow map
   // glViewport(0, 0, shadowMapSize, shadowMapSize);

    //Draw back faces into the shadow map
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    //Disable color writes, and use flat shading for speed
    glShadeModel(GL_FLAT);
    glColorMask(0, 0, 0, 0);

   DrawShadowTestScene(angle2);

shadowmap_framebuffer->Bind();
glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowmap_framebuffer->width(), shadowmap_framebuffer->height());

shadowmap_framebuffer2->Bind();
glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowmap_framebuffer->width(), shadowmap_framebuffer->height());
glBindTexture(GL_TEXTURE_2D, 0);

    //restore states
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glColorMask(1, 1, 1, 1);

    //2nd pass - Draw from camera's point of view
    //glClearColor(0, 1, 0, 1);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(cameraProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(cameraViewMatrix);

   // glViewport(0, 0, windowWidth, windowHeight);

   light_shader->enable();
     DrawShadowTestScene(angle2);
   light_shader->disable();

//frame_buffer2->Bind();
//glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowmap_framebuffer->width(), shadowmap_framebuffer->height());
//glBindTexture(GL_TEXTURE_2D, 0);

frame_buffer->Disable();

 
  /// Third past, in order to have the second one in a different texture. # en otras palabras no hace falta realizar la segunda pasada.

  ////////
  // Setup texture matrix.
  const GLfloat bias[16] = {0.5, 0.0, 0.0, 0.0,
                            0.0, 0.5, 0.0, 0.0,
                            0.0, 0.0, 0.5, 0.0,
                            0.5, 0.5, 0.5, 1.0};

  glActiveTexture(GL_TEXTURE7);


  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glLoadMatrixf(bias);

  // concatening all matrix into one.
  glMultMatrixf(lightProjectionMatrix);
  glMultMatrixf(lightViewMatrix);
  //glRotatef(angle2, 0, 1, 0);

  // restore to default values.
  glActiveTexture(GL_TEXTURE0);

  glMatrixMode(GL_MODELVIEW);
  ////

/*
frame_buffer2->Enable();
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(cameraProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(cameraViewMatrix);

    //glRotatef(angle2, 0, 1, 0);

   // glViewport(0, 0, windowWidth, windowHeight);

   shadowmap_framebuffer->Bind();


// NOTE: si quiero que no se afecte la textura con el depth buffer quitar estas lineas...
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

   shadowmap_shader->enable();

   mask_shader->setUniform1i("shadow_map", 0); // utilizar depth map instead.

   //light_shader->enable();
     DrawShadowTestScene(angle2);
   //light_shader->disable();
   shadowmap_shader->disable();

   glBindTexture(GL_TEXTURE_2D, 0);

frame_buffer2->Disable();
*/

//////////////////// prueba para generar la imagen de modulation
// Esta parte deberia estar dentro de un metodo que sea el que genera el shadow map.
modulation_framebuffer->Enable();
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(cameraProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(cameraViewMatrix);

   // glViewport(0, 0, windowWidth, windowHeight);

   shadowmap_framebuffer->Bind();

// NOTE: si quiero que no se afecte la textura con el depth buffer quitar estas lineas...
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

   modulation_shader->enable();

   modulation_shader->setUniform1i("shadow_map", 0); // utilizar depth map instead.
   DrawShadowTestScene(angle2);

   modulation_shader->disable();


   glBindTexture(GL_TEXTURE_2D, 0);

modulation_framebuffer->Disable();

//////////////////////

 glDisable(GL_CULL_FACE);

  // Aplicar el filtro blur a la textura con las sombras.
  ApplyBlurEffectToShadows();

  // Componer la imagen final, agregar las sombras al objeto final.
  ApplyShadowsToFinalImage();

return;
///////////////////////////////
  frame_buffer->Enable();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 1, 4);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

 /* glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  //gluPerspective(45, 1.0, 0.01, 100);
glOrtho(0.0, 256.0, 0.0, 256.0, -1.0, 1.0); 
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();


  glClearColor(0, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
glEnable(GL_DEPTH_TEST);
*/
  //glEnable(GL_DEPTH_TEST);
  glClearColor(0, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glPushMatrix();

  glColor4f(1, 1, 1, 1.0f);
  glTranslatef(0, 0, -2);

  static float angle = 0;
  angle += 1;
  glRotatef(angle, 1, 1, 1);

  DisplayMeshList();

   /* //glTranslatef(-0.5, -0.5, -4);
    glTranslatef(0, -0.2, -4);
    glColor4f(1, 1, 1, 1.0f);

    glBegin(GL_QUADS);
      glTexCoord2f(0, 1);
      glVertex2f(0, 0);
      glTexCoord2f(1, 1);
      glVertex2f(1, 0);
      glTexCoord2f(1, 0);
      glVertex2f(1, 1);
      glTexCoord2f(0, 0);
      glVertex2f(0, 1);
    glEnd();
*/
//  glPopMatrix();

shadowmap_framebuffer->Bind();
glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 256, 256);
glBindTexture(GL_TEXTURE_2D, 0);

  frame_buffer->Disable();
}

// The function receive the current modelview and projection matrix of the camera.
void GenerateShadowMap(GLdouble *modelView, GLdouble *projection) {
  GLfloat lightProjectionMatrix[16], lightViewMatrix[16];

  //DissertationProject::vec3f lightPos(0, -2.0f, 4.0f);
  // prueba para rotar las sombras automaticamente.
/*
  static float dir = -1;
  static float cnt = -2;
  lightPos.x = 3 * std::sin(cnt);
  lightPos.y = 3 * std::cos(cnt);

  cnt += 0.0125 * dir;
  if (cnt <= -4) dir = 1;
  if (cnt >= -2) dir = -1;
*/

  // Init matrix's
  //glMatrixMode(GL_PROJECTION);
glMatrixMode(GL_MODELVIEW);
  //glLoadMatrixf(lightProjectionMatrix);
  //glLoadMatrixd(projection);
  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 1.0f, 40.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);

  glMatrixMode(GL_MODELVIEW);
  //glLoadMatrixf(lightViewMatrix);
  glLoadIdentity();
  glLoadMatrixd(modelView);
  //glTranslatef(0, 0, -5);
  
 
  gluLookAt(DetectedLightPos.x, DetectedLightPos.y, DetectedLightPos.z,
 //gluLookAt(lightPos.x, lightPos.y, lightPos.z,
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f);

  //glTranslatef(0, 0, -4);

  //glMultMatrixd(modelView);
  
  // definir posicion de la luz con respecto a la escena.
//  glRotatef(45, 1, 0, 0);

//  glTranslatef(0, -1, -4);
//  glRotatef(-90, 1, 0, 0);

  glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);

/*  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 1.0f, 20.0f);

  glLoadMatrixd(modelView);
*/

  frame_buffer->Enable();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(lightProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(lightViewMatrix);

  // Draw back faces into the shadow map
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  // Disable color writes, and use flat shading for speed
  glShadeModel(GL_FLAT);
  glColorMask(0, 0, 0, 0);

  glColor3f(1, 0, 0);
  displayGeometry1();
  glColor3f(1, 1, 1);
  displayGeometry2();

shadowmap_framebuffer->Bind();
glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowmap_framebuffer->width(), shadowmap_framebuffer->height());

shadowmap_framebuffer2->Bind();
glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowmap_framebuffer->width(), shadowmap_framebuffer->height());
glBindTexture(GL_TEXTURE_2D, 0);

  // restore states
  glCullFace(GL_BACK);
  glDisable(GL_CULL_FACE);

  glShadeModel(GL_SMOOTH);
  glColorMask(1, 1, 1, 1);

/*
    //2nd pass - Draw from camera's point of view
    // esta parte tiene que hacerce con otro frame buffer que sea de la misma 
    // resolucion de la pantalla.
    //glClearColor(0, 1, 0, 1);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT); 
    //glMatrixMode(GL_PROJECTION);
    //glLoadMatrixd(projection);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(modelView);

   //light_shader->enable();
   //  DrawShadowTestScene(angle2);
   //light_shader->disable();

  
  light_shader->enable();
    glColor3f(1, 0, 0);
    displayGeometry1();
    glColor3f(1, 1, 1);
    displayGeometry2();
  light_shader->disable();
*/

  frame_buffer->Disable(); 

  // TODO: hacer un blend entre el render de la geometria y la imagen de background. y luego copiar esa imagen de nuevo.
  // o simplemente hacer el rende completamente en el frame buffer principal.


  /// Third past, in order to have the second one in a different texture. # en 
  /// otras palabras no hace falta realizar la segunda pasada.
  ////////
  // Setup texture matrix.
  const GLfloat bias[16] = {0.5, 0.0, 0.0, 0.0,
                            0.0, 0.5, 0.0, 0.0,
                            0.0, 0.0, 0.5, 0.0,
                            0.5, 0.5, 0.5, 1.0};

  glActiveTexture(GL_TEXTURE7);
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glLoadMatrixf(bias);

  // concatening all matrix into one.
  glMultMatrixf(lightProjectionMatrix);
  glMultMatrixf(lightViewMatrix);
  //glRotatef(angle2, 0, 1, 0);

  // restore to default values.
  glActiveTexture(GL_TEXTURE0);

  glMatrixMode(GL_MODELVIEW);
  ////

  modulation_framebuffer->Enable();
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: aca el render debe ser con el aspect ratio adecuado.
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(projection);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);


    glMatrixMode(GL_MODELVIEW);
    //glLoadMatrixf(cameraViewMatrix);
    glLoadIdentity();
    glLoadMatrixd(modelView);

    glActiveTexture(GL_TEXTURE0);
    shadowmap_framebuffer->Bind();

    // NOTE: si quiero que no se afecte la textura con el depth buffer quitar estas lineas...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

    modulation_shader->enable();
      modulation_shader->setUniform1i("shadow_map", 0); // utilizar depth map instead.
      //DrawShadowTestScene(angle2);
      glColor3f(1, 0, 0);
      displayGeometry1();
      glColor3f(1, 1, 1);
      displayGeometry2();
    modulation_shader->disable();

    glBindTexture(GL_TEXTURE_2D, 0);

  modulation_framebuffer->Disable();


  // Aplicar el filtro blur a la textura con las sombras.
  ApplyBlurEffectToShadows();

  // Componer la imagen final, agregar las sombras al objeto final.
  ApplyShadowsToFinalImage();
}

void RenderSceneToFrameBuffer(GLdouble *modelView, GLdouble *projection) {
  scene_framebuffer->Enable();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
    const GLfloat kAspect = scene_framebuffer->width() * 1.0 / scene_framebuffer->height();
    gluPerspective(45.0f, kAspect, 0.1f, 100.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(modelView);

    glColor3f(1, 1, 1);
    defaultGometryDisplay(1);

  scene_framebuffer->Disable();
}

void RenderMaskToTexture() {
  glActiveTexture(GL_TEXTURE0);
  camera_framebuffer2->Bind();

  glActiveTexture(GL_TEXTURE1);
  DissertationProject::Locator::GetTextureManager()->EnableTexture("mask");

  mask_effect->Enable();
    mask_effect->shader()->setUniform1i("base_map", 0);
    mask_effect->shader()->setUniform1i("mask_map", 1);  
  mask_effect->Disable();

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderNormalMapToTexture() {
  glActiveTexture(GL_TEXTURE0);
  grayscale_framebuffer->Bind();

  normalmap_effect->Enable();
    normalmap_effect->shader()->setUniform1i("height_map", 0);
    normalmap_effect->shader()->setUniform1f("height_map_width", grayscale_framebuffer->width());
    normalmap_effect->shader()->setUniform1f("height_map_height", grayscale_framebuffer->height());
  normalmap_effect->Disable();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderGrayscaleToTexture() {
  glActiveTexture(GL_TEXTURE0);
  camera_framebuffer2->Bind();

  grayscale_effect->Enable();
    grayscale_effect->shader()->setUniform1i("base_map", 0);
  grayscale_effect->Disable();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

/*void RenderQuad(int x, int y, int size) {
  glColor4f(1, 1, 1, 1.0f);

  glPushMatrix();
    glTranslatef(x, y, 0);    
    glBegin(GL_QUADS);
      glTexCoord2f(0, 1);
      glVertex2f(0, 0);
      glTexCoord2f(1, 1);
      glVertex2f(size, 0);
      glTexCoord2f(1, 0);
      glVertex2f(size, size);
      glTexCoord2f(0, 0);
      glVertex2f(0, size);
    glEnd();
  glPopMatrix();    
}
*/

void RenderQuad(int x, int y, int width, int height) {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  glPushMatrix();
    glTranslatef(x, y, 0);    
    glBegin(GL_QUADS);
      glTexCoord2f(0, 1);
      glVertex2f(0, 0);
      glTexCoord2f(1, 1);
      glVertex2f(width, 0);
      glTexCoord2f(1, 0);
      glVertex2f(width, height);
      glTexCoord2f(0, 0);
      glVertex2f(0, height);
    glEnd();
  glPopMatrix();    
}


/// Test to render a HUD...
void RenderHUD(int found, bool display_hud, bool light_detect) {

  boost::shared_ptr<DissertationProject::TextureManager> textures = DissertationProject::Locator::GetTextureManager();
  
  glEnable(GL_TEXTURE_2D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  ViewOrtho(640, 480);


  // Render geometry over the layer.
  if (found) {
    //scene_framebuffer->Bind();
    apply_shadow_framebuffer->Bind();
    RenderQuad(0, 0, 640, 480);
    //RenderQuad(512, 352, 128, 128);
  }

  if (display_hud) {
  // 1st test.
  //textures->EnableTexture("logo");
  //textures->EnableTexture("env");
  //textures->EnableTexture("base_map");
  //mask_framebuffer->Bind();
  //frame_buffer->Bind();
  //camera_framebuffer2->Bind();
  shadowmap_framebuffer2->Bind();
  RenderQuad(0, 352, 128, 128);

  // 2nd test.
  //grayscale_framebuffer->Bind();
  //mask_framebuffer->Bind();
  //frame_buffer->Bind();
  //modulation_framebuffer->Bind();
  //blur_framebuffer->Bind();
  modulation_framebuffer->Bind();
  RenderQuad(128, 352, 128, 128);

  // 3rd test.
  //grayscale_framebuffer->Bind();
  //normalmap_framebuffer->Bind();
  //shadowmap_framebuffer2->Bind();
  //modulation_framebuffer->Bind();
  //blur_framebuffer->Bind();
  //frame_test->Bind();
  //frame_buffer->Bind();
  //RenderQuad(0, 0, 512);
  //frame_buffer->Bind();
  scene_framebuffer->Bind();
  RenderQuad(256, 352, 128, 128);

  // 4th test.
  //frame_buffer2->Bind();
  apply_shadow_framebuffer->Bind();
  RenderQuad(384, 352, 128, 128);
  //RenderQuad(0, 0, 512);

  detect_light_framebuffer->Bind();
  RenderQuad(512, 352, 128, 128);
  }

  if (light_detect) {
    // prueba solo para pintar las fuentes
    //grayscale_framebuffer->Bind();
    //RenderQuad(384, 352, 128, 128);
    detect_light_framebuffer->Bind();
    RenderQuad(512, 352, 128, 128);
  }

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  ViewPerspective();

  glDisable(GL_BLEND);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void LoadMeshList() {
  if (!use_mesh_list) return;
  for (int i = 0; i <= 20; ++i) {
    boost::shared_ptr<DissertationProject::MeshObj> temp =
        boost::shared_ptr<DissertationProject::MeshObj> (new DissertationProject::MeshObj());
    char buffer[100]; sprintf(buffer, "../../media/mesh/bigguy/bigguy_%02d.obj", i);
    temp->Load(buffer);
    mesh_list.push_back(temp);
  }
}

void ReleaseMeshList() {
  const int kNumberOfMeshes = static_cast<int> (mesh_list.size());
  for (int i = 0; i < kNumberOfMeshes; ++i) mesh_list[i].reset();
  mesh_list.clear();
}

void DisplayMeshList() {
  if (use_mesh_list) {
    static int frame = 0, cnt = 0, dir = 1; 
    if (cnt == 1) { 
      frame = frame + dir, cnt = 0;
      if (frame == 0 || frame == 20) dir *= -1;
    }
    mesh_list[frame]->drawSurface(0);
    cnt++;
  } else {
    mesh_test->drawSurface(0);
  }
}
