/// \file texture/texture_manager.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file declares the DissertationProject::TextureManager 
/// class, which implement the basic functionalities of a manager of textures.
#ifndef TEXTURE_MANAGER_H__
#define TEXTURE_MANAGER_H__

#include "global.h"
#include "texture/texture.h"
#include "map"
#include "boost/shared_ptr.hpp"

BEGIN_PROJECT_NAMESPACE();

class TextureManager {
 public:
  /// \brief Standard constructor.
  TextureManager();

  /// \brief Default destructor.
  ~TextureManager();

  /// \brief Accessor method for the number of textures stored in the manager.
  /// \return The number of textures stored in the manager.
  int size() const;


  // TODO: Todo change the name of this method to bind.
  void EnableTexture(const std::string& texture_name);

  void DisableTexture(const std::string& texture_name);


  void RegisterTexture2D(const std::string& name, const std::string& file_path);

  void RegisterTexture2D(const std::string& name, int width, int height, void* pixels, bool depth_texture = false);

  void RegisterTextureCubeMap(const std::string& name, const std::string& file_path);
  
  // void UnRegister(const std::string& file_path);

  /// \brief Look up a texture in the texture manager.
  /// \param[in] name Name used to register the texture.
  boost::shared_ptr<Texture> GetTexture(const std::string& name) const;

 private:
  /// \brief Map with all contained textures.
  std::map<std::string, boost::shared_ptr<Texture> > textures_by_path_; // only one path is related to a texture.
  std::map<std::string, boost::shared_ptr<Texture> > textures_by_name_; // many names can point to same texture.

  DISALLOW_COPY_AND_ASSIGN(TextureManager);
};

END_PROJECT_NAMESPACE();

#endif  // TEXTURE_MANAGER_H__
