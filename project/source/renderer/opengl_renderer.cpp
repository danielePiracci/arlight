/// \file renderer/opengl_renderer.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/08/09
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Renderer class, 
/// declared at renderer/opengl_renderer.h.
#include "renderer/opengl_renderer.h"
#include "renderer/opengl_mesh_renderer.h"
#include "texture/opengl_texture.h"

#include "FreeImage.h"

BEGIN_PROJECT_NAMESPACE();

OpenGLRenderer::OpenGLRenderer() {
  // TODO: verificar si necesito hacer algo al terminar..
  // Initialize the use of FreeImage
  FreeImage_Initialise();
}

OpenGLRenderer::~OpenGLRenderer() {
  // Release all the resources used on textures.
  FreeImage_DeInitialise();
}

boost::shared_ptr<MeshRenderer> OpenGLRenderer::GetNewMeshRenderer() const {
  return boost::shared_ptr<MeshRenderer> (new OpenGLMeshRenderer());
}

boost::shared_ptr<Texture> OpenGLRenderer::GetNewTexture() const {
  return boost::shared_ptr<Texture> (new OpenGLTexture());
}

END_PROJECT_NAMESPACE();
