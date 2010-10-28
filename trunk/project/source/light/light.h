/// \file light/light.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
/// 
/// \brief This file declares the DissertationProject::Light class, which 
/// implement the basic functionalities of a light.
#ifndef LIGHT_H__
#define LIGHT_H__

#include "global.h"
#include "math/vector.h"

BEGIN_PROJECT_NAMESPACE();

class Light {
 public:
  /// \brief Standard constructor.
  Light();

  /// \brief Initialization constructor.
  Light(int type, const vec3f& position, const vec3f& direction, 
        const vec4f& ambient, const vec4f& diffuse, const vec4f& specular);

  /// \brief Default destructor.
  ~Light();

  /// \brief Mutator method for the type of light.
  /// \param[in] type New type of light.
  inline void set_type(int type);

  /// \brief Mutator method for the index of the light.
  /// \param[in] index New index of the light.
  inline void set_index(int index);

  /// \brief Mutator method for the cutoff range of the light.
  /// \param[in] range New cutoff range of the light.
  inline void set_range(float range);

  /// \brief Mutator method for the constant attenuation of the light.
  /// \param[in] constant_attenuation New constant attenuation of the light.
  inline void set_constant_attenuation(float constant_attenuation);

  /// \brief Mutator method for the linear attenuation of the light.
  /// \param[in] linear_attenuation New linear attenuation of the light.
  inline void set_linear_attenuation(float linear_attenuation);

  /// \brief Mutator method for the quadratic attenuation of the light.
  /// \param[in] quadratic_attenuation New quadratic attenuation of the light.
  inline void set_quadratic_attenuation(float quadratic_attenuation);

  /// \brief Mutator method for the position of the light.
  /// \param[in] position New position for the light.
  inline void set_position(const vec3f& position);

  /// \brief Mutator method for the direction of the light.
  /// \param[in] specular New direction for the light.
  inline void set_direction(const vec3f& direction);

  /// \brief Mutator method for the ambient component of the light.
  /// \param[in] ambient New ambient component for the light.
  inline void set_ambient(const vec4f& ambient);

  /// \brief Mutator method for the diffuse component of the light.
  /// \param[in] diffuse New diffuse component for the light.
  inline void set_diffuse(const vec4f& diffuse);

  /// \brief Mutator method for the specular component of the light.
  /// \param[in] specular New specular component for the light.
  inline void set_specular(const vec4f& specular);

  /// \brief Accessor method to the type of light.
  /// \return A int that contain the type of light.
  inline int type() const;

  /// \brief Accessor method to the index of the light.
  /// \return A int that contain the index of the light.
  inline int index() const;

  /// \brief Accesor method to the cutoff range of the light.
  /// \return A float that contain the cutoff range of the light.
  inline float range() const;

  /// \brief Accesor method to the constant attenuation of the light.
  /// \return A float that contain the constant attenuation of the light.
  inline float constant_attenuation() const;

  /// \brief Accesor method to the linear attenuation of the light.
  /// \return A float that contain the linear attenuation of the light.
  inline float linear_attenuation() const;

  /// \brief Accesor method to the quadratic attenuation of the light.
  /// \return A float that contain the quadratic attenuation of the light.
  inline float quadratic_attenuation() const;

  /// \brief Accessor method to the position of the light.
  /// \return A vec3f that contain the position of the light.
  inline vec3f position() const;

  /// \brief Accessor method to the direction of the light.
  /// \return A vec3f that contain the direction of the light.
  inline vec3f direction() const;

  /// \brief Accessor method to the ambient component of the light.
  /// \return A vec4f that contain the ambient component of the light.
  inline vec4f ambient() const;

  /// \brief Accessor method to the diffuse component of the light.
  /// \return A vec4f that contain the diffuse component of the light.
  inline vec4f diffuse() const;

  /// \brief Accessor method to the specular component of the light.
  /// \return A vec4f that contain the specular component of the light.
  inline vec4f specular() const;

  /// \brief Method to start the use of the light.
  void Enable();

  /// \brief Method to stop the use of the light.
  void Disable();

  enum LighType {
	POINT = 1,
    SPOT = 2,
    DIRECTIONAL = 3,
  };

 private:
  /// \brief type of light.
  int type_;

  /// \brief index of the light.
  int index_;

  /// \brief cutoff range of the light.
  float range_;

  /// \brief constant attenuation of the light.
  float constant_attenuation_;

  /// \brief linear attenuation of the light.
  float linear_attenuation_;

  /// \brief quadratic attenuation of the light.
  float quadratic_attenuation_;

  /// \brief Light position.
  vec3f position_;

  /// \brief Light direction;
  vec3f direction_;

  /// \brief ambient component of the light.
  vec4f ambient_;

  /// \brief diffuse component of the light.
  vec4f diffuse_;

  /// \brief specular component of the light.
  vec4f specular_;

  DISALLOW_COPY_AND_ASSIGN(Light);
};

END_PROJECT_NAMESPACE();

#endif  // LIGHT_H__
