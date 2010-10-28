/// \file material/material.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Material class, 
/// declared at material/material.h.
#include "material/material_inl.h"
//#include "game/game.h"

BEGIN_PROJECT_NAMESPACE();

Material::Material() { }

Material::Material(const std::string& name,
                   const std::string& file_path,
                   const vec4f& ambient,
                   const vec4f& diffuse, 
                   const vec4f& specular,
                   const vec4f& emissive) 
    : name_(name),
      texture_file_path_(file_path),
      ambient_(ambient),
      diffuse_(diffuse),
      specular_(specular),
      emissive_(emissive) { }

Material::~Material() { }

void Material::Enable() {
//  GAME_RENDERER.EnableMaterial(*this);
}

void Material::Disable() {
//  GAME_RENDERER.DisableMaterial(*this);
}

END_PROJECT_NAMESPACE();
