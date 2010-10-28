/// \file renderer/hud.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/04
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Hud class, 
/// which implement the basic functionalities of a Head-up Display.
#ifndef HUD_H__
#define HUD_H__

// TODO: esta clase deberia estar en otro lado, la que deberia estar aca es HUDRenderer.

#include "global.h"
//#include "math/vector.h"
//#include "string"

BEGIN_PROJECT_NAMESPACE();

class HUD{
 public:
  /// \brief Standard constructor.
  HUD();

  /// \brief Default destructor.
  ~HUD();

 private:

  DISALLOW_COPY_AND_ASSIGN(HUD);
};

END_PROJECT_NAMESPACE();

#endif  // HUD_H__
