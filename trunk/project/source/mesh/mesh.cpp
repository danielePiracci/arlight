/// \file mesh/mesh.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Mesh class, 
/// declared at mesh/mesh.h.
#include "mesh/mesh.h"
#include "base/locator_inl.h"

BEGIN_PROJECT_NAMESPACE();

Mesh::Mesh() {
  mesh_renderer_ = Locator::GetRenderer()->GetNewMeshRenderer();
}

Mesh::~Mesh() {
  mesh_renderer_.reset();
}

void Mesh::Render(bool apply_material) {
  mesh_renderer_->Render();
}

END_PROJECT_NAMESPACE();
