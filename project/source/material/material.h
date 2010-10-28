/// \file material/material.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Material class, 
/// which implement the basic functionalities of a material.
#ifndef MATERIAL_H__
#define MATERIAL_H__

#include "global.h"
#include "math/vector.h"
#include "string"

BEGIN_PROJECT_NAMESPACE();

class Material {
 public:
  /// \brief Standard constructor.
  Material();

  /// \brief Initializer constructor.
  /// \param[in] name Name for the material.
  /// \param[in] file_path Texture file path for the material.
  /// \param[in] ambient Ambient component for the material.
  /// \param[in] diffuse Diffuse component for the material.
  /// \param[in] specular Specular component for the material.
  /// \param[in] emissive Emissive component for the material.
  Material(const std::string& name, const std::string& file_path,
           const vec4f& ambient, const vec4f& diffuse, const vec4f& specular,
           const vec4f& emissive);

  /// \brief Default destructor.
  ~Material();

  /// \brief Mutator method for the ambient component of the material.
  /// \param[in] ambient New ambient component for the material.
  inline void set_ambient(const vec4f& ambient);

  /// \brief Mutator method for the diffuse component of the material.
  /// \param[in] diffuse New diffuse component for the material.
  inline void set_diffuse(const vec4f& diffuse);

  /// \brief Mutator method for the specular component of the material.
  /// \param[in] specular New specular component for the material.
  inline void set_specular(const vec4f& specular);

  /// \brief Mutator method for the emissive component of the material.
  /// \param[in] emissive New emissive component for the material.
  inline void set_emissive(const vec4f& emissive);

  /// \brief Mutator method for the name of the material.
  /// \param[in] name New name for the material.
  inline void set_name(const std::string& name);

  /// \brief Mutator method for the texture file path related to the material.
  /// \param[in] texture_file_path New texture file path for the material.
  inline void set_texture_file_path(const std::string& texture_file_path);

  /// \brief Accessor method to the ambient component of the material.
  /// \return A vec4f that contain the ambient component of the material.
  inline vec4f ambient() const;

  /// \brief Accessor method to the diffuse component of the material.
  /// \return A vec4f that contain the diffuse component of the material.
  inline vec4f diffuse() const;

  /// \brief Accessor method to the specular component of the material.
  /// \return A vec4f that contain the specular component of the material.
  inline vec4f specular() const;

  /// \brief Accessor method to the emissive component of the material.
  /// \return A vec4f that contain the emissive component of the material.
  inline vec4f emissive() const;

  /// \brief Accessor method to the name of the material.
  /// \return A std::string that contain the name of the material.
  inline std::string name() const;

  /// \brief Accessor method to the texture file name related to the material.
  /// \return A std::string that contain the texture file path for the material.
  inline std::string texture_file_path() const;

  /// \brief Method to start the use of the material.
  void Enable();

  /// \brief Method to stop the use of the material.
  void Disable();

 private:
  /// \brief Ambient component of the material.
  vec4f ambient_;

  /// \brief Diffuse component of the material.
  vec4f diffuse_;

  /// \brief Specular component of the material.
  vec4f specular_;

  /// \brief Emissive component of the material.
  vec4f emissive_;

  /// \brief Material name.
  std::string name_;

  /// \brief Texture file path.
  std::string texture_file_path_;

  DISALLOW_COPY_AND_ASSIGN(Material);
};

END_PROJECT_NAMESPACE();

#endif  // MATERIAL_H__
