/// \file renderer/null_renderer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/27
/// \version 1.0
/// 
/// \brief This file declares the DissertationProject::NullRenderer class, 
/// which implement a null renderer object, its implementation basically does 
/// nothing, but allows code that receives the object to safely continue on as 
/// if it had receives a "real" one.
#ifndef NULL_RENDERER_H__
#define NULL_RENDERER_H__

#include "global.h"
#include "renderer/renderer.h"
#include "texture/null_texture.h"

BEGIN_PROJECT_NAMESPACE();

class NullRenderer : public Renderer {
 public:  
  /// \brief Standard constructor.
  NullRenderer() { }

  /// \brief Default destructor.
  ~NullRenderer() { }

  /// \brrief Method to get a new texture object.
  virtual inline boost::shared_ptr<Texture> GetNewTexture() const {
    return boost::shared_ptr<NullTexture> (new NullTexture());
  }

  /// \brief Method to get a new mesh renderer object.
  virtual inline boost::shared_ptr<MeshRenderer> GetNewMeshRenderer() const {
    return boost::shared_ptr<MeshRenderer> ();
  }

  /// \brief Method to load a texture.
  /// \param[in] file_path Texture file path.
  virtual void LoadTexture(const std::string& file_path) { }

 private:
  DISALLOW_COPY_AND_ASSIGN(NullRenderer);
};

END_PROJECT_NAMESPACE();

#endif  // NULL_RENDERER_H__
