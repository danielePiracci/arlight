/// \file base/locator_inl.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/22
/// \version 1.0
///
/// \brief This file implements the inline functions of the 
/// DissertationProject::Locator class, declared at base/locator.h.
#ifndef LOCATOR_INL_H__
#define LOCATOR_INL_H__

#include "base/locator.h"
#include "renderer/null_renderer.h"

BEGIN_PROJECT_NAMESPACE();

void Locator::Initilize() {
  renderer_ = boost::shared_ptr<Renderer> (new NullRenderer());
  mesh_manager_ = boost::shared_ptr<MeshManager> (new MeshManager());
  texture_manager_ = boost::shared_ptr<TextureManager<int> > (new TextureManager<int>());
}

void Locator::Release() {
  renderer_.reset();
  mesh_manager_.reset();
  texture_manager_.reset();
}

void Locator::Register(const boost::shared_ptr<Renderer>& renderer) {
  if (renderer) renderer_ = renderer;
  else renderer_ = boost::shared_ptr<Renderer> (new NullRenderer());
}

void Locator::Register(const boost::shared_ptr<MeshManager>& mesh_manager) {
  mesh_manager_ = mesh_manager;
}

void Locator::Register(const boost::shared_ptr<TextureManager<int> >& texture_manager) {
  texture_manager_ = texture_manager;
}

boost::shared_ptr<Renderer>& Locator::GetRenderer() {
  return renderer_;
}

boost::shared_ptr<MeshManager>& Locator::GetMeshManager() {
  return mesh_manager_;
}

boost::shared_ptr<TextureManager<int> >& Locator::GetTextureManager() {
  return texture_manager_;
}

END_PROJECT_NAMESPACE();

#endif  // LOCATOR_INL_H__
