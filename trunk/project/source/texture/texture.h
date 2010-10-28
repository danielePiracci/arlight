/// \file texture/texture.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Texture class, which 
/// implement the basic functionalities of a texture.
#ifndef TEXTURE_H__
#define TEXTURE_H__

#include "global.h"

BEGIN_PROJECT_NAMESPACE();

// TODO: Implementar alguna manera de almacenar la informacion relacionada al 
// tamaño de la textura.

template<typename Handler>
class Texture {
 public:
  /// \brief Standard constructor.
  Texture();

  /// \brief Initializer constructor.
  Texture(Handler* handler);

  /// \brief Default destructor.
  ~Texture();

  /// \brief Accesor method to the handler of the texture.
  /// \return A pointer that contain the handler of the texture.
  ///
  /// The handler must contain a 'Release' a method that will called at the 
  /// end of the app to release the resources.
  Handler* handler() const;

 private:
  /// \brief Texture handler.
  Handler* handler_;

  DISALLOW_COPY_AND_ASSIGN(Texture);
};

template<typename Handler>
Texture<Handler>::Texture() : handler_(0) { }

template<typename Handler>
Texture<Handler>::Texture(Handler* handler) : handler_(handler) { }

template<typename Handler>
Texture<Handler>::~Texture() {
  if (handler_) delete handler_;
  handler_ = 0;
}

template<typename Handler>
Handler* Texture<Handler>::handler() const {
  return handler_;
}

END_PROJECT_NAMESPACE();

#endif  // TEXTURE_H__
