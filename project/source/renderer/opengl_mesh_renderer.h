/// \file renderer/opengl_mesh_renderer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/28
/// \version 1.0
///
/// \brief This file declares the DissertationProject::OpenGLMeshRenderer class, 
/// which implement the basic functionalities of a mesh renderer using OpenGL. 
/// This class should be used as a component for a Mesh class.
#ifndef OPENGL_MESH_RENDERER_H__
#define OPENGL_MESH_RENDERER_H__

#include "global.h"
#include "renderer/mesh_renderer.h"
#include "mesh/mesh.h"

BEGIN_PROJECT_NAMESPACE();

class OpenGLMeshRenderer : public MeshRenderer {
 public:
  /// \brief Standard constructor.
  OpenGLMeshRenderer();

  /// \brief Default destructor.
  ~OpenGLMeshRenderer();

  /// \brief Method to initialize the mesh renderer.
  virtual void Initialize();
   
  /// \brief Method to release all the resources used.
  virtual void Release();

  /// \brief Method to render the mesh.
  virtual void Render();

 private:
  DISALLOW_COPY_AND_ASSIGN(OpenGLMeshRenderer);
};

END_PROJECT_NAMESPACE();

#endif  // OPENGL_MESH_RENDERER_H__
