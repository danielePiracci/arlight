/// \file renderer/mesh_renderer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/28
/// \version 1.0
///
/// \brief This file declares the DissertationProject::MeshRenderer class, 
/// which implement the basic functionalities of a mesh renderer. This class 
/// should be used as a component for a Mesh class.
#ifndef MESH_RENDERER_H__
#define MESH_RENDERER_H__

#include "global.h"
#include "base/component.h"

BEGIN_PROJECT_NAMESPACE();

class MeshRenderer : public Component {
 public:
  /// \brief Standard constructor.
  MeshRenderer();

  /// \brief Default destructor.
  virtual ~MeshRenderer();

  /// \brief Method to initialize the mesh renderer.
  virtual void Initialize() = 0;
   
  /// \brief Method to release the resources used.
  virtual void Release() = 0;

  /// \brief Method to render the mesh.
  virtual void Render() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(MeshRenderer);
};

END_PROJECT_NAMESPACE();

#endif  // MESH_RENDERER_H__
