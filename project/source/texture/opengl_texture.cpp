/// \file texture/opengl_texture.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/04
/// \version 1.0
///
/// \brief This file implements the DissertationProject::OpenGLTexture class, 
/// declared at texture/opengl_texture.h.
#include "texture/opengl_texture.h"

#include "FreeImage.h"

BEGIN_PROJECT_NAMESPACE();

OpenGLTexture::OpenGLTexture() : texture_name_(0) {
  glGenTextures(1, &texture_name_);
}

OpenGLTexture::~OpenGLTexture() {
  glDeleteTextures(1, &texture_name_);
}

void OpenGLTexture::LoadTexture(const std::string& file_path, unsigned int target) {
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
    // Calculate the number of bytes uses per pixel.
    GLuint kNumberOfComponents = (FreeImage_GetBPP(bitmap) + 7) / 8;

    // Set image's pixel format.
    GLuint pixel_format = 0;
    bool isHdr = false;
    switch (kNumberOfComponents) {
      case 1: pixel_format = GL_LUMINANCE; break;
      case 2: break; // TODO: Report an error on the log.
      case 3: pixel_format = GL_BGR; break;
      case 4: pixel_format = GL_BGRA; break;
      case 12: pixel_format = GL_RGB, kNumberOfComponents = 3, isHdr = true; break; // HDR image.
      default: break; // TODO: Report an error on the log.
    }

    width_ = FreeImage_GetWidth(bitmap);
    height_ = FreeImage_GetHeight(bitmap);

    // Create the 2D mipmap.
    //gluBuild2DMipmaps(GL_TEXTURE_2D, kNumberOfComponents, width_, height_, 
    //                  pixel_format, isHdr ? GL_UNSIGNED_INT : GL_UNSIGNED_BYTE,
    //                  FreeImage_GetBits(bitmap));

    glTexImage2D(target, 0, kNumberOfComponents, width_, height_, 0, 
                 pixel_format, isHdr ? GL_UNSIGNED_INT : GL_UNSIGNED_BYTE, 
                 FreeImage_GetBits(bitmap));

    // Check if the texture was generated sucessful.
    if (glIsTexture(texture_name_) != GL_TRUE)
      // Report the error on the log.
      // TODO: print a message on the log instead.
      printf("error - texture\n");

    // Unload the image file.
    FreeImage_Unload(bitmap);
  }
}


void OpenGLTexture::CreateTextureFromFile(const std::string& file_path) {
  texture_type_ = GL_TEXTURE_2D;

  Enable();

  LoadTexture(file_path, texture_type_);

  //
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  Disable();
}
  
void OpenGLTexture::CreateCubeTextureFromFile(const std::string& file_path) {
  texture_type_ = GL_TEXTURE_CUBE_MAP;

  Enable();

  const int kPosition = file_path.rfind(".");
  if (kPosition != file_path.npos) {

    char* texture_face[6] = {
      "_posx",
      "_negx",
      "_posy",
      "_negy",
      "_posz",
      "_negz"
    };

    GLenum cubeFaces[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT,
    };

    const std::string left_part = file_path.substr(0, kPosition);
    const std::string right_part = file_path.substr(kPosition);

    for (int i = 0; i < 6; ++i)
      LoadTexture(left_part + texture_face[i] + right_part, cubeFaces[i]);
  }

  //
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // 
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  //
  Disable();
}

void OpenGLTexture::CreateTextureFromMemory() {

}

void OpenGLTexture::Enable() {
  glBindTexture(texture_type_, texture_name_);
}

void OpenGLTexture::Disable() {
  glBindTexture(texture_type_, 0);
}

END_PROJECT_NAMESPACE();
