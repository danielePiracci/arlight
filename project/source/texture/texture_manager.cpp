/// \file texture/texture_manager.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the DissertationProject::TextureManager 
/// class, declared at texture/texture_manager.h.
#include "texture/texture_manager.h"
#include "base/locator_inl.h"

BEGIN_PROJECT_NAMESPACE();

TextureManager::TextureManager() { }

TextureManager::~TextureManager() {
  textures_by_name_.clear();
  textures_by_path_.clear();
}

void TextureManager::EnableTexture(const std::string& texture_name) {
  std::map<std::string, boost::shared_ptr<Texture> >::const_iterator it = textures_by_name_.find(texture_name);
  if (it != textures_by_name_.end()) it->second->Enable();
}

void TextureManager::DisableTexture(const std::string& texture_name) {
  std::map<std::string, boost::shared_ptr<Texture> >::const_iterator it = textures_by_name_.find(texture_name);
  if (it != textures_by_name_.end()) it->second->Enable();
}

void TextureManager::RegisterTexture2D(const std::string& name, const std::string& file_path) {
  std::map<std::string, boost::shared_ptr<Texture> >::const_iterator it = textures_by_path_.find(file_path);
  if (it == textures_by_path_.end()) {
    boost::shared_ptr<Texture> texture = Locator::GetRenderer()->GetNewTexture();
    texture->CreateTextureFromFile(file_path);
    textures_by_path_[file_path] = texture;

  // Check if exist a name already defined.
  } else if (textures_by_name_.find(name) != textures_by_name_.end()) {
     printf("Texture name redefined!\n");
  }
  textures_by_name_[name] = textures_by_path_[file_path];
}

void TextureManager::RegisterTexture2D(const std::string& name, int width, int height, void* pixels, bool depth_texture) {
  boost::shared_ptr<Texture> texture = Locator::GetRenderer()->GetNewTexture();
  texture->CreateTextureFromMemory(width, height, pixels, depth_texture);
  textures_by_name_[name] = texture;
}

void TextureManager::RegisterTextureCubeMap(const std::string& name, const std::string& file_path) {
  std::map<std::string, boost::shared_ptr<Texture> >::const_iterator it = textures_by_path_.find(file_path);
  if (it == textures_by_path_.end()) {
    boost::shared_ptr<Texture> texture = Locator::GetRenderer()->GetNewTexture();
    texture->CreateCubeTextureFromFile(file_path);
    textures_by_path_[file_path] = texture;
    textures_by_name_[name] = texture;
  }
}

boost::shared_ptr<Texture> TextureManager::GetTexture(const std::string& name) const {
  std::map<std::string, boost::shared_ptr<Texture> >::const_iterator it = textures_by_name_.find(name);
  return it == textures_by_name_.end() ? boost::shared_ptr<Texture>(new NullTexture()) : it->second;
}

END_PROJECT_NAMESPACE();
