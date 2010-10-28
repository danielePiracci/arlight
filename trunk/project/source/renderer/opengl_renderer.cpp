/// \file renderer/opengl_renderer.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/08/09
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Renderer class, 
/// declared at renderer/opengl_renderer.h.
#include "renderer/opengl_renderer.h"
#include "renderer/opengl_mesh_renderer.h"
#include "FreeImage.h"
//#include "glew.h"

BEGIN_PROJECT_NAMESPACE();

OpenGLRenderer::OpenGLRenderer() {
  // TODO: verificar si necesito hacer algo al terminar..
  // Initialize the use of FreeImage
  FreeImage_Initialise(FALSE);


}

OpenGLRenderer::~OpenGLRenderer() {
  // Release all the resources used on textures.
  ReleaseTextures();
}

boost::shared_ptr<MeshRenderer> OpenGLRenderer::GetNewMeshRenderer() const {
  return boost::shared_ptr<MeshRenderer> (new OpenGLMeshRenderer());
}

void OpenGLRenderer::LoadTexture(const std::string& file_path) {
  // Check if the texture is not on memory and if so load it.
  if (texture_manager_.GetTexture(file_path) == NULL) {
    // Check the file signature and deduce its format.
    FREE_IMAGE_FORMAT file_format = FreeImage_GetFileType(file_path.c_str(), 0);

    // If the file don't have signature try to guess the file format from the 
    // file extension.
    if (file_format == FIF_UNKNOWN) {
      file_format = FreeImage_GetFIFFromFilename(file_path.c_str());
      // TODO: print a warning message on the log.
      printf("warning - textures\n");
    }

    // Check that the plugin has reading capabilities and if so load the file 
    // otherwise report an error on the log.
    FIBITMAP* bitmap = NULL;
	if ((file_format != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(file_format))
      bitmap = FreeImage_Load(file_format, file_path.c_str(), 0);
    else
      // TODO: print a message on the log.
      printf("error - textures\n");

    // Check if the load was successful.
    if (bitmap) {

      glEnable(GL_TEXTURE_2D);

      // Genereta a new texture name.
      GLuint texture_name = 0;
      glGenTextures(1, &texture_name);

      // TODO: esta linea creo que se puede borrar.
      glBindTexture(GL_TEXTURE_2D, texture_name);

      // Calculate the number of bytes uses per pixel.
      GLuint kNumberOfComponents = (FreeImage_GetBPP(bitmap) + 7) / 8;

      // Set image's pixel format.
      GLuint pixel_format = 0;
      switch (kNumberOfComponents) {
        case 1: pixel_format = GL_LUMINANCE; break;
        case 2: break; // TODO: Report an error on the log.
        case 3: pixel_format = GL_BGR; break;
        case 4: pixel_format = GL_BGRA; break;
        default: break; // TODO: Report an error on the log.
      }

      // Create the 2D mipmap.
      gluBuild2DMipmaps(GL_TEXTURE_2D, kNumberOfComponents, 
                        FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 
                        pixel_format, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap));

      // Check if the texture was generated sucessful.
      if (glIsTexture(texture_name) == GL_TRUE)
        // Add the new texture to the texture manager.
        texture_manager_.AddTexture(file_path, new GLuint(texture_name));
      else
        // Report the error on the log.
        // TODO: print a message on the log instead.
        printf("error - texture\n");

      // TODO: Set all the parameter options of the texture here.
      // TODO: Try to do the previous settings on another place.

      // TODO: creo que esta linea se puede borrar.
      glBindTexture(GL_TEXTURE_2D, 0);
      glDisable(GL_TEXTURE_2D);

      // Unload the image file.
      FreeImage_Unload(bitmap);
    }
  }
}

void OpenGLRenderer::ReleaseTextures() {
  // Iterate over the textures and release all the memory used on this.
  const int kNumberOfTextures = texture_manager_.size();
  for (int i = 0; i < kNumberOfTextures; ++i) {
    const std::string& texture_name = texture_manager_.GetNextTextureName();
    glDeleteTextures(1, texture_manager_.GetTexture(texture_name)->handler());
    texture_manager_.RemoveTexture(texture_name);
  }
}

END_PROJECT_NAMESPACE();
