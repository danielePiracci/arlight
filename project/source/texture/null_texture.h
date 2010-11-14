/// \file texture/null_texture.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/07
/// \version 1.0
/// 
/// \brief This file declares the DissertationProject::NullTexture class, 
/// which implement a null texture object, its implementation basically does 
/// nothing, but allows code that receives the object to safely continue on as 
/// if it had receives a "real" one.
#ifndef NULL_TEXTURE_H__
#define NULL_TEXTURE_H__

#include "global.h"
#include "texture/texture.h"

BEGIN_PROJECT_NAMESPACE();

class NullTexture : public Texture {
 public:
  /// \brief Standard constructor.
  NullTexture() { }

  /// \brief Default destructor.
  virtual ~NullTexture() { }

  ///
  virtual void CreateTextureFromFile(const std::string& file_path) { }
  
  virtual void CreateCubeTextureFromFile(const std::string& file_path) { }

  ///
  virtual void CreateTextureFromMemory(int width, int height, void* pixels, bool depth_texture = false) { }

  virtual void Enable() { }

  virtual void Disable() { }

 private:
  DISALLOW_COPY_AND_ASSIGN(NullTexture);
};

END_PROJECT_NAMESPACE();

#endif  // NULL_TEXTURE_H__
