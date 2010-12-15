/// \file texture/opengl_texture.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/04
/// \version 1.0
///
/// \brief This file declares the DissertationProject::OpenGLTexture class, which 
/// implement the basic functionalities of a OpenGL texture.
#ifndef OPENGL_TEXTURE_H__
#define OPENGL_TEXTURE_H__

#include "global.h"
#include "texture/texture.h"
#include "opengl_includes.h"

#include "string"

BEGIN_PROJECT_NAMESPACE();

class OpenGLTexture : public Texture {
 public:
  /// \brief Standard constructor.
  OpenGLTexture();

  /// \brief Default destructor.
  ~OpenGLTexture();

  ///
  virtual void CreateTextureFromFile(const std::string& file_path);
  
  virtual void CreateCubeTextureFromFile(const std::string& file_path);

  ///
  virtual void CreateTextureFromMemory(int width, int height, void* pixels, bool depth_texture = false);

  virtual void Enable(); // should be inline

  virtual void Disable(); // should be inline

  /// \brief Accessor to the texture name.
  /// \return A GLuint with the texture name.
  inline GLuint TextureName() const { return texture_name_; }

 private:
  
  void LoadTexture(const std::string& file_path, unsigned int target);

  /// \brief
  GLuint texture_name_;

  /// \brief
  GLenum texture_type_;

  DISALLOW_COPY_AND_ASSIGN(OpenGLTexture);
};

END_PROJECT_NAMESPACE();

#endif  // OPENGL_TEXTURE_H__
