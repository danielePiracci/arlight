/// \file shader/effect.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/29
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Effect class, 
/// declared at shader/PostProcessEffect.h.
#include "shader/effect.h"

BEGIN_PROJECT_NAMESPACE();

Effect::Effect(const boost::shared_ptr<Shader>& shader) : shader_(shader) { }

Effect::~Effect() {
  shader_.reset();  
}

void Effect::Enable() {
  shader_->enable();
}

void Effect::Disable() {
  shader_->disable();
}

END_PROJECT_NAMESPACE();
