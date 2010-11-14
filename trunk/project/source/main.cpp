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

#include "ctime"

////////////////////////////////////////////
//// Pruebas para agregar las texturas ...

// TODO: hacer que el objeto no desaparezca tan facilmente cuando no se detecta.


DissertationProject::OpenGLRenderer renderer;

//// Prueba para cargar un modelo.
//DissertationProject::MeshObj mesh_test;
boost::shared_ptr<DissertationProject::MeshObj> mesh_test;

std::vector<boost::shared_ptr<DissertationProject::MeshObj> > mesh_list;

bool use_mesh_list = false;

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

// Prueba para calcular el normal map.
boost::shared_ptr<DissertationProject::Shader> normalmap_shader;
boost::shared_ptr<DissertationProject::FrameBuffer> normalmap_framebuffer;
void RenderNormalMapToTexture();


// Prueba para capturar la esfera.
boost::shared_ptr<DissertationProject::FrameBuffer> camera_framebuffer;
void RenderCameraToTexture();

/// Prueba para desplegar HUD.
void RenderHUD();
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

  // Delete shaders.
  // TODO: tener un shader manager, de tal manera de poder eliminarlos todos facilmetne.
  shader_test.reset();
  convolution_shader.reset();
  grayscale_shader.reset();
  normalmap_shader.reset();

  frame_buffer.reset();
  grayscale_framebuffer.reset();
  normalmap_framebuffer.reset();
  camera_framebuffer.reset();
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
			gDrawRotate = !gDrawRotate;
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

//
// This function is called when the window needs redrawing.
//
static void Display(void) {
  // TODO: crear una clase timer para poder hacer pruebas de cuanto se demora ciertas 
  // tareas en mi codigo, luego utilizar estos logs en el documento que escriba.

  // NOTE: recordar que voy a cambiar la funcion de visibility para poder hacer cosas en tiempo real.
  // pero de alguna manera tengo que controlar que lo que mando a pintar solo debe ser actualizado 
  // con esa ultima imagen que fue capturada, por lo que podria meter eso uno de mis frame buffers.

/*
  glDrawBuffer(GL_BACK);
CalculateFps();
glutSwapBuffers();

return;
*/

/*
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 640.0 / 480.0, 0.01, 100);
  //glOrtho(0, 640, 0, 480, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  RenderToTexture();

  glLoadIdentity();
  glColor4f(1, 1, 1, 1.0f);
  glTranslatef(0, 0, -4);
  static float angle = 0;
  angle += 2;
  glRotatef(angle, 1, 1, 0);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 1);

  DisplayMeshList();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glutSwapBuffers();


  CalculateFps();

return;
*/

    GLdouble p[16];
	GLdouble m[16];
	
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

    // parche para que el objeto nunca desaparezca
	static GLdouble prev_m[16];

	if (gPatt_found) {
      arglCameraViewRH(gPatt_trans, m, VIEW_SCALEFACTOR);
	  glLoadMatrixd(m);
      memcpy(prev_m, m, sizeof(m));
    } else {
      glLoadMatrixd(prev_m);
    }

	//if (gPatt_found) {
    if (true) {
	
		// Calculate the camera position relative to the marker.
		// Replace VIEW_SCALEFACTOR with 1.0 to make one drawing unit equal to 1.0 ARToolKit units (usually millimeters).
		arglCameraViewRH(gPatt_trans, m, VIEW_SCALEFACTOR);
		glLoadMatrixd(m);

		// All lighting and geometry to be drawn relative to the marker goes here.
		//DrawCube();

//////////////////////////////////////////////////
////Definicion del material
//// TODO: ver como funciona esto bien realmente.
///

GLfloat ambient[] = {0.1f, 0.1f, 0.1f};
GLfloat diffuse[] = {0.8f, 0.8f, 0.8f};
GLfloat specular[] = {0.7f, 0.7f, 0.7f};
GLfloat emission[] = {0.0f, 0.0f, 0.0f};

// Ver si deberia colocarlo solo en el front o en el back tambien.
//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//glMaterialfv(GL_FRONT, GL_EMISSION, emission);

//glEnable ( GL_COLOR_MATERIAL ) ;
//glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
/////////////////////////////////////////////////

//glEnable(GL_LIGHTING);
//glEnable(GL_LIGHT0);

GLfloat ambientl[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffusel[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specularl[] = {1.0f, 1.0f, 1.0f, 1.0f};
//GLfloat attenuationl[] = {1.0f, 0.0f, 0.0f};
GLfloat attenuationl[] = {0.1f, 0.0f, 0.0f};
GLfloat positionl[] = {4, 4, 4, 1};

  /*glLightfv(GL_LIGHT0, GL_AMBIENT, ambientl);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusel);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularl);
  glLightfv(GL_LIGHT0, GL_POSITION, positionl);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuationl[0]);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, attenuationl[1]);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuationl[2]);
*/


boost::shared_ptr<DissertationProject::TextureManager> textures = DissertationProject::Locator::GetTextureManager();


shader_test->enable();

glActiveTexture(GL_TEXTURE0);
//glEnable(GL_TEXTURE_2D);
textures->EnableTexture("base_map");


glActiveTexture(GL_TEXTURE1);
//glEnable(GL_TEXTURE_CUBE_MAP_EXT);
textures->EnableTexture("env_map");
//textures->EnableTexture("env");

glActiveTexture(GL_TEXTURE2);
textures->EnableTexture("diff_env_map");

//glPushMatrix();

  glTranslatef(0, 0, 1);

if (use_mesh_list) glScalef(0.25, 0.25, 0.25);
else glScalef(2, 2, 2);

glRotatef(90, 1, 0, 0);

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

DisplayMeshList();


//glPopMatrix();

    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);

    //glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, 0);
    //glDisable(GL_TEXTURE_CUBE_MAP_EXT);

glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
glDisable(GL_TEXTURE_CUBE_MAP);
    
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
glDisable(GL_TEXTURE_CUBE_MAP);

//glActiveTexture(GL_TEXTURE1);
//glBindTexture(GL_TEXTURE_2D, 0);
//glDisable(GL_TEXTURE_2D);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_TEXTURE_2D);

shader_test->disable();	

//glDisable(GL_LIGHT0);
//glDisable(GL_LIGHTING);

	} // gPatt_found
	
	// Any 2D overlays go here.
	//none
	

  // prueba para pintar un skybox...
  //RenderRotatingMesh2();

    ////////////////////////////////////
    /// NOTE: PRueba para pintar los HUD de la aplicacion.
    
    // TODO: hacer que los hud se desplieguen a travez de un manager que se 
    // encargue de hacer esta funcionalidad. Tener en cuenta que el tamaño de 
    // la ventana es importante al mommento de hacer el viewOrtho, por lo que 
    // este valor deberia ser accessible desde cualquier punto de la aplicacion.


//    RenderRotatingMesh();

    /// Prueba para desplegar HUD del programa.
    RenderHUD();

    // Prueba para probar el shader de convolution.
    RenderConvolution();

    // Prueba para render to texture.
    RenderToTexture();

    // Prueba para calcular el grayscale.
    RenderGrayscaleToTexture();

    // prueba para generar el normal map.
    RenderNormalMapToTexture();

    // Prueba para montar la imagen de la camara en una textura.
    RenderCameraToTexture();
    /////////////////////////////////////

	glutSwapBuffers();

CalculateFps();
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

// prueba para asegurar que los fps no estan siendo afectados por las tareas 
// que hago, sino mas bien que la ventana no esta siendo actualizada cuando 
// la camara no le envia una nueva imagen.
/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(prefWidth, prefHeight);
		glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
    glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	//glutVisibilityFunc(Visibility);
	glutKeyboardFunc(Keyboard);
	if (GLEW_OK != glewInit()) 
       printf("glewinit fail!.\n");

glutMainLoop();
return 0;*/
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
  frame_buffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(256, 256, GL_BGRA, true));
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
 // mesh_test->Load("../../media/mesh/apple.obj");
  mesh_test->Load("../../media/mesh/bigguy.obj");
  LoadMeshList();

                                                                                                                                                                                                         
  //////////////////////////////////////////////
  //// Pruebas para cargar los shaders.
  shader_test = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
   
  //shader_test->openVertexP("../../media/shaders/test.vert");
  //shader_test->openFragmentP("../../media/shaders/test.frag");

  //shader_test->openVertexP("../../media/shaders/test2.vert");
  //shader_test->openFragmentP("../../media/shaders/test2.frag");

  shader_test->openVertexP("../../media/shaders/test3.vert");
  shader_test->openFragmentP("../../media/shaders/test3.frag");

  //shader_test->openVertexP("../../media/shaders/point_light.vert");
  //shader_test->openFragmentP("../../media/shaders/point_light.frag");

  //shader_test->openVertexP("../../media/shaders/toon_shading.vert");
  //shader_test->openFragmentP("../../media/shaders/toon_shading.frag");

  //shader_test->openVertexP("../../media/shaders/texture_light.vert");
  //shader_test->openFragmentP("../../media/shaders/texture_light.frag");

  //shader_test->openVertexP("../../media/shaders/sem.vert");
  //shader_test->openFragmentP("../../media/shaders/sem.frag");

  //shader_test->openVertexP("../../media/shaders/light1.vert");
  //shader_test->openFragmentP("../../media/shaders/light1.frag");

  //shader_test->openVertexP("../../media/shaders/multitexturing.vert");
  //shader_test->openFragmentP("../../media/shaders/multitexturing.frag");

  //shader_test->openVertexP("../../media/shaders/cube_test.vert");
  //shader_test->openFragmentP("../../media/shaders/cube_test.frag");

  shader_test->load();

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


  // prueba para crear el shader y el framebuffer para generar el normal map.
  normalmap_shader = boost::shared_ptr<DissertationProject::Shader> (new DissertationProject::Shader());
  normalmap_shader->openVertexP("../../media/shaders/gen_normal_map.vert");
  normalmap_shader->openFragmentP("../../media/shaders/gen_normal_map.frag");
  normalmap_shader->load();
  normalmap_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(base_map->width(), base_map->height(), GL_BGRA, true));

  // prueba para capturar la imagen de la camara.
  camera_framebuffer = boost::shared_ptr<DissertationProject::FrameBuffer> (new DissertationProject::FrameBuffer(640, 480, GL_BGRA, true));

  // TODO: recordar colocar este chequeo en los shaders!!.
  //if (glCreateShaderObjectARB == 0)
  //  printf("Error: shader\n");
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

void RenderCameraToTexture() {
  camera_framebuffer->Enable();

//  glClearColor(0, 0, 0, 1);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glDrawBuffer(GL_BACK);
//gArglSettings = arglSetupForCurrentContext();
 /* glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 1);
*/
  arglDispImage(gARTImage, &gARTCparam, 1.0, gArglSettings);	// zoom = 1.0.

/*
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
 */

  camera_framebuffer->Disable();
}

void RenderToTexture() {
//return;
  frame_buffer->Enable();
  
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
  glTranslatef(0, 0, -4);

  static float angle = 0;
  angle += 7;
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

  frame_buffer->Disable();
}

void RenderNormalMapToTexture() {
  // NOTE: deberia definir el active texture con estas operaciones, 
  // simplemente para estar seguro sobre cual estoy trabajando.
  grayscale_framebuffer->Bind();

  normalmap_framebuffer->Enable();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // verificar si no tengo que colocar esto de otra manera.
  const int kWidth = normalmap_framebuffer->width();
  const int kHeight = normalmap_framebuffer->height();
  glOrtho(0, kWidth, kHeight, 0, -1, 1);

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();		

  normalmap_shader->enable();

  normalmap_shader->setUniform1i("height_map", 0);
  normalmap_shader->setUniform1f("height_map_width", grayscale_framebuffer->width());
  normalmap_shader->setUniform1f("height_map_height", grayscale_framebuffer->height());

    glColor4f(1, 1, 1, 1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 1);
      glVertex2f(0, 0);
      glTexCoord2f(1, 1);
      glVertex2f(kWidth, 0);
      glTexCoord2f(1, 0);
      glVertex2f(kWidth, kHeight);
      glTexCoord2f(0, 0);
      glVertex2f(0, kHeight);
    glEnd();

  normalmap_shader->disable();

  normalmap_framebuffer->Disable();
}

void RenderGrayscaleToTexture() {

  //DissertationProject::Locator::GetTextureManager()->EnableTexture("base_map");
  camera_framebuffer->Bind();

  grayscale_framebuffer->Enable();

  grayscale_shader->enable();
  
  convolution_shader->setUniform1i("base_map", 0);

  // Escribir de alguna manera estas transformaciones mas eficientemente.
  // Lo que podria hacer es meter estas cosas dentro de una clase, algo 
  // como post-processing effect.... pensar!...
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // verificar si no tengo que colocar esto de otra manera.
  const int kWidth = grayscale_framebuffer->width();
  const int kHeight = grayscale_framebuffer->height();
  glOrtho(0, kWidth, kHeight, 0, -1, 1);
  //glOrtho(0, kWidth, 0, kHeight, -1, 1);

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glTranslatef(0, 352, 0);
    //glTranslatef(0, kHeight, 0);

    glColor4f(1, 1, 1, 1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 1);
      glVertex2f(0, 0);
      glTexCoord2f(1, 1);
      glVertex2f(kWidth, 0);
      glTexCoord2f(1, 0);
      glVertex2f(kWidth, kHeight);
      glTexCoord2f(0, 0);
      glVertex2f(0, kHeight);
    glEnd();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();			

  grayscale_shader->disable();

  grayscale_framebuffer->Disable();

  glBindTexture(GL_TEXTURE_2D, 0);
}

/// Test to render a HUD...
void RenderHUD() {

boost::shared_ptr<DissertationProject::TextureManager> textures = DissertationProject::Locator::GetTextureManager();

//shader_test->enable();

    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 1);
    //textures->EnableTexture("logo");
    //textures->EnableTexture("env");
    textures->EnableTexture("base_map");

    //frame_buffer->Bind();
    camera_framebuffer->Bind();

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    ViewOrtho(640, 480);
    
glPushMatrix();
    glTranslatef(0, 352, 0);

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
glPopMatrix();    

glPushMatrix();
  grayscale_framebuffer->Bind();

    glTranslatef(128, 352, 0);

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
glPopMatrix();    


glPushMatrix();
  normalmap_framebuffer->Bind();

    glTranslatef(256, 352, 0);

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
glPopMatrix();    



    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    ViewPerspective();

    glDisable(GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

//shader_test->disable();

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

/*
#include "cstdio"

int main() {
  printf("Hola Mundo!!!\n");

  return 0;
}
*/


