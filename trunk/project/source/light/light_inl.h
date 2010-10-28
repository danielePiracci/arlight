/// \file light/light_inl.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
/// 
/// \brief This file implements the inline functions of the 
/// DissertationProject::Light class, declared at light/light.h.
#ifndef LIGHT_INL_H__
#define LIGHT_INL_H__

#include "light/light.h"

BEGIN_PROJECT_NAMESPACE();

void Light::set_ambient(const vec4f& ambient) {
  ambient_ = ambient;
}

void Light::set_diffuse(const vec4f& diffuse) {
  diffuse_ = diffuse;
}

void Light::set_specular(const vec4f& specular) {
  specular_ = specular;
}

void Light::set_position(const vec3f& position) {
  position_ = position;
}

void Light::set_direction(const vec3f& direction) {
  direction_ = direction;
}

void Light::set_type(int type) {
  type_ = type;
}

void Light::set_index(int index) {
  index_ = index;
}

void Light::set_range(float range) {
  range_ = range;
}

void Light::set_constant_attenuation(float constant_attenuation) {
  constant_attenuation_ = constant_attenuation;
}

void Light::set_linear_attenuation(float linear_attenuation) {
  linear_attenuation_ = linear_attenuation;
}

void Light::set_quadratic_attenuation(float quadratic_attenuation) {
  quadratic_attenuation_ = quadratic_attenuation;
}

vec4f Light::ambient() const {
  return ambient_;
}

vec4f Light::diffuse() const {
  return diffuse_;
}

vec4f Light::specular() const {
  return specular_;
}

vec3f Light::position() const {
  return position_;
}

vec3f Light::direction() const {
  return direction_;
}

int Light::type() const {
  return type_;
}

int Light::index() const {
  return index_;
}

float Light::range() const {
  return range_;
}

float Light::constant_attenuation() const {
  return constant_attenuation_;
}

float Light::linear_attenuation() const {
  return linear_attenuation_;
}

float Light::quadratic_attenuation() const {
  return quadratic_attenuation_;
}

END_PROJECT_NAMESPACE();

#endif  // LIGHT_INL_H__
