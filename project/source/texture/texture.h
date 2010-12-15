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

#include "string"

BEGIN_PROJECT_NAMESPACE();

// TODO: implement a better way to manage multitextures.

class Texture {
 public:
  /// \brief Standard constructor.
  Texture();

  /// \brief Default destructor.
  virtual ~Texture();

  /// \brief Accessor method for the texture width.
  /// \return The width of the texture.
  inline int width() const { return width_; }

  /// \brief Accessor method for the texture height.
  /// \return The height of the texture.
  inline int height() const { return height_; }

  ///
  virtual void CreateTextureFromFile(const std::string& file_path) = 0;
  
  virtual void CreateCubeTextureFromFile(const std::string& file_path) = 0;

  ///
  virtual void CreateTextureFromMemory(int width, int height, void* pixels, bool depth_texture = false) = 0;

  virtual void Enable() = 0;

  virtual void Disable() = 0;

 protected:
  /// \brief texture width.
  int width_;

  /// \brief texture height.
  int height_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Texture);
};

END_PROJECT_NAMESPACE();

#endif  // TEXTURE_H__
