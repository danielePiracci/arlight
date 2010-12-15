/// \file renderer/opengl_renderer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/08/09
/// \version 1.0
/// 
/// \brief This file declares the DissertationProject::OpenGLRenderer class, 
/// which implement the basic functionalities of a opengl renderer.
#ifndef OPENGL_RENDERER_H__
#define OPENGL_RENDERER_H__

#include "global.h"
#include "renderer/renderer.h"
#include "texture/texture_manager.h"
#include "opengl_includes.h"
#include "math/vector.h"
#include "string"

// TODO: implement a state manager to improve the performance of the application.

BEGIN_PROJECT_NAMESPACE();

class OpenGLRenderer : public Renderer {
 public:
  /// \brief Standard constructor.
  OpenGLRenderer();

  /// \brief Default destructor.
  ~OpenGLRenderer();

  /// \brief Method to get a new mesh renderer object.
  virtual boost::shared_ptr<MeshRenderer> GetNewMeshRenderer() const;

  /// \brrief Method to get a new texture object.
  virtual boost::shared_ptr<Texture> GetNewTexture() const;

  // Method draw an sprite.
  // TODO: implement.
  void DrawSprite(const std::string& texture);

 private:
  DISALLOW_COPY_AND_ASSIGN(OpenGLRenderer);
};

END_PROJECT_NAMESPACE();

#endif  // OPENGL_RENDERER_H__
