/// \file shader/effect.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/29
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Effect class, 
/// which implement the basic functionalities of a effect.
#ifndef EFFECT_H__
#define EFFECT_H__

#include "global.h"
#include "shader/shader.h"

#include "boost/shared_ptr.hpp"

BEGIN_PROJECT_NAMESPACE();

class Effect {
 public:
  /// \brief Standard constructor.
  Effect(const boost::shared_ptr<Shader>& shader);

  /// \brief Default destructor.
  virtual ~Effect();

  /// \brief Method to start the use of the material.
  virtual void Enable();

  /// \brief Method to stop the use of the material.
  virtual void Disable();

  // 
  boost::shared_ptr<Shader> shader() const { return shader_; }

 protected:
  // TODO: cambiar esto para que incluya los shaders separados como tal, es 
  // decir el efecto se encargara de compilarlos juntos.
  boost::shared_ptr<Shader> shader_;

  // boost::shared_ptr<Shader> vertex_shader_;
  // boost::shared_ptr<Shader> fragment_shader_;
  // boost::shared_ptr<Shader> geometry_shader_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Effect);
};

END_PROJECT_NAMESPACE();

#endif  // EFFECT_H__
