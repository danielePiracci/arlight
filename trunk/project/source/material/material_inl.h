/// \file material/material_inl.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the inline functions of the 
/// DissertationProject::Material class, declared at material/material.h.
#ifndef MATERIAL_INL_H__
#define MATERIAL_INL_H__

#include "material/material.h"
//#include "game/game.h"

BEGIN_PROJECT_NAMESPACE();

void Material::set_ambient(const vec4f& ambient) {
  ambient_ = ambient;
}

void Material::set_diffuse(const vec4f& diffuse) {
  diffuse_ = diffuse;
}

void Material::set_specular(const vec4f& specular) {
  specular_ = specular;
}

void Material::set_emissive(const vec4f& emissive) {
  emissive_ = emissive;
}  

void Material::set_name(const std::string& name) {
  name_ = name;
}  

void Material::set_texture_file_path(const std::string& texture_file_path) {
  texture_file_path_ = texture_file_path;
}

vec4f Material::ambient() const {
  return ambient_;
}

vec4f Material::diffuse() const {
  return diffuse_;
}

vec4f Material::specular() const {
  return specular_;
}

vec4f Material::emissive() const {
  return emissive_;
}

std::string Material::name() const {
  return name_;
}

std::string Material::texture_file_path() const {
  return texture_file_path_;
}

END_PROJECT_NAMESPACE();

#endif  // MATERIAL_INL_H__
