/// \file base/component.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/31
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Component class, 
/// which define the basic functionalities of a componet.
#ifndef COMPONENT_H__
#define COMPONENT_H__

#include "global.h"

BEGIN_PROJECT_NAMESPACE();

class Component {
 public:
  /// \brief Standard constructor.
  Component();

  /// \brief Default destructor.
  virtual ~Component();

  /// \brief Method to initialize the services.
  virtual void Initialize() = 0;
   
  /// \brief Method to release all the services.
  virtual void Release() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Component);
};

END_PROJECT_NAMESPACE();

#endif  // COMPONENT_H__
