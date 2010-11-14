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

//template<typename T>
class TextureManager {
 public:
  /// \brief Standard constructor.
  TextureManager();

  /// \brief Default destructor.
  ~TextureManager();

  /// \brief Add a texture with handler to the specified file path.
  /// \param[in] file_path Path where is located the texture in the hard drive.
  /// \param[in] handler Pointer to the texture handler.
//  void AddTexture(const std::string& file_path, T* handler);

  /// \brief Remove the specified texture from the texture manager.
  /// \param[in] file_path Path where is located the texture in the hard drive.
//  void RemoveTexture(const std::string& file_path);

  /// \brief Look up a texture in the texture manager.
  /// \param[in] file_path Path where is located the texture in the hard drive.
//  boost::shared_ptr<Texture<T> > GetTexture(const std::string& file_path) const;

  /// \brief Look up for the first texture in the texture manager.
  //std::string GetNextTextureName() const;

  /// \brief Accessor method for the number of textures stored in the manager.
  /// \return The number of textures stored in the manager.
  int size() const;


  // TODO: cambiar el nombre de este metodo por bidnd.
  void EnableTexture(const std::string& texture_name);

  void DisableTexture(const std::string& texture_name);


  void RegisterTexture2D(const std::string& name, const std::string& file_path);

  void RegisterTexture2D(const std::string& name, int width, int height, void* pixels, bool depth_texture = false);

  void RegisterTextureCubeMap(const std::string& name, const std::string& file_path);
  
//  void UnRegister(const std::string& file_path);

  /// \brief Look up a texture in the texture manager.
  /// \param[in] name Name used to register the texture.
  boost::shared_ptr<Texture> GetTexture(const std::string& name) const;



 private:
  /// \brief Map with all contained textures.

  std::map<std::string, boost::shared_ptr<Texture> > textures_by_path_; // only one path is related to a texture.
  std::map<std::string, boost::shared_ptr<Texture> > textures_by_name_; // many names can point to same texture.


  DISALLOW_COPY_AND_ASSIGN(TextureManager);
};
/*
template<typename T>
TextureManager<T>::TextureManager() { }

template<typename T>
TextureManager<T>::~TextureManager() {
  textures_.clear();
}

template<typename T>
void TextureManager<T>::AddTexture(const std::string& file_path, T* handler) {
  textures_[file_path] = boost::shared_ptr<Texture<T> >(new Texture<T>(handler));
}

template<typename T>
void TextureManager<T>::RemoveTexture(const std::string& file_path) {
  std::map<std::string, boost::shared_ptr< Texture<T> > >::const_iterator it = textures_.find(file_path);
  textures_.erase(it);
}

template<typename T>
boost::shared_ptr<Texture<T> > TextureManager<T>::GetTexture(const std::string& file_path) const {
  std::map<std::string, boost::shared_ptr< Texture<T> > >::const_iterator it = textures_.find(file_path);
  return it == textures_.end() ? boost::shared_ptr<Texture<T> >() : it->second;
}

template<typename T>
std::string TextureManager<T>::GetNextTextureName() const {
  return textures_.empty() ? "" : textures_.begin()->first;
}

template<typename T>
int TextureManager<T>::size() const {
  return static_cast<int> (textures_.size());
}
*/

END_PROJECT_NAMESPACE();

#endif  // TEXTURE_MANAGER_H__
