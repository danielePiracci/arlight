/// \file light/light.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Light class, 
/// declared at light/light.h.
#include "light/light_inl.h"
//#include "game/game.h"

BEGIN_PROJECT_NAMESPACE();

Light::Light()
    : type_(DIRECTIONAL),
      index_(0),
      range_(100000),
      constant_attenuation_(0),
      linear_attenuation_(0.0001f),
      quadratic_attenuation_(0.00000001f) { }

Light::Light(int type,
             const vec3f& position,
             const vec3f& direction,
             const vec4f& ambient,
             const vec4f& diffuse,
             const vec4f& specular)
    : index_(0),
      type_(type),
      position_(position),
      direction_(direction), 
      ambient_(ambient),
      diffuse_(diffuse),
      specular_(specular),
      range_(1000),
      constant_attenuation_(0.5f),
      linear_attenuation_(0.01f),
      quadratic_attenuation_(0.00001f) { }

Light::~Light() { }

void Light::Enable() {
//  GAME_RENDERER.EnableLight(*this);
}

void Light::Disable() {
//  GAME_RENDERER.DisableLight(*this);
}

END_PROJECT_NAMESPACE();
