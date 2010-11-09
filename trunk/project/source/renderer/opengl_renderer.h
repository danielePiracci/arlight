/// \file renderer/opengl_renderer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/08/09
/// \version 1.0
/// 
/// \brief This file declares the DissertationProject::OpenGLRenderer class, 
/// which implement the basic functionalities of a opengl renderer.
#ifndef OPENGL_RENDERER_H__
#define OPENGL_RENDERER_H__

#include "global.h"
#include "renderer/renderer.h"
#include "texture/texture_manager.h"
#include "opengl_includes.h"
#include "math/vector.h"
#include "string"

// TODO: podria implementar el manejador de estados de esa manera mejorar el rendimiento de la aplicacion. esta entre mis cosas.

BEGIN_PROJECT_NAMESPACE();

class OpenGLRenderer : public Renderer {
 public:
  /// \brief Standard constructor.
  OpenGLRenderer();

  /// \brief Default destructor.
  ~OpenGLRenderer();

  /// \brief Method to get a new mesh renderer object.
  virtual boost::shared_ptr<MeshRenderer> GetNewMeshRenderer() const;

  /// \brrief Method to get a new texture object.
  virtual boost::shared_ptr<Texture> GetNewTexture() const;

  // TODO: este metodo va a necesitar tener cierta informacion de la textura 
  // como por ejemplo su dimension, de esta manera va a poder crear un 
  // rectangulo exacto del tamaño necesario para que no pierda calidad la imagen.
  void DrawSprite(const std::string& texture); //, // Esto podria ser un identificador para que sea mas rapido el acceso.
                                               // faltarian aca la posicion, el centro de la imagen, etc. revisar el proyecto de xbox 360 para tener una idea.

 private:
  DISALLOW_COPY_AND_ASSIGN(OpenGLRenderer);
};

END_PROJECT_NAMESPACE();

#endif  // OPENGL_RENDERER_H__
