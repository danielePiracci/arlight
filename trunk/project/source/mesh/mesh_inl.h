/// \file mesh/mesh_inl.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the inline functions of the 
/// DissertationProject::Mesh class, declared at mesh/mesh.h.
#ifndef MESH_INL_H__
#define MESH_INL_H__

#include "mesh.h"
#include "game/game.h"

BEGIN_PROJECT_NAMESPACE();

template<typename Handler>
Mesh<Handler>::Mesh() : handler_(0) { }

template<typename Handler>
Mesh<Handler>::Mesh(Handler* handler) : handler_(handler) { }

template<typename Handler>
Mesh<Handler>::~Mesh() {
  if (handler_) handler_->Release();
}

template<typename Handler>
Handler* Mesh<Handler>::handler() const {
  return handler_;
}

template<typename Handler>
void Mesh<Handler>::Render(bool apply_material) {
  GAME_RENDERER.RenderMesh(*this, apply_material);
}

template<typename Handler>
void Mesh<Handler>::AddMaterial(const boost::shared_ptr<Material>& material) {
  materials_.push_back(material);
}

template<typename Handler>
void Mesh<Handler>::EnableMaterial(int index) {
  if (index >= 0 && index < NumberOfMaterials()) {
    materials_[index]->Enable();
  }
}

template<typename Handler>
void Mesh<Handler>::DisableMaterial(int index) {
  if (index >= 0 && index < NumberOfMaterials()) {
    materials_[index]->Disable();
  }
}

template<typename Handler>
int Mesh<Handler>::NumberOfMaterials() const {
  return static_cast<int>(materials_.size());
}

END_PROJECT_NAMESPACE();

#endif  // MESH_INL_H__
