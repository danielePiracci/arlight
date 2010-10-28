/// \file mesh/face.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/20
/// \version 1.0
///
/// \brief This file declares the DissertationProject::face
/// class, which implement the basic functionalities of a triangle face.
#ifndef MESH_FACE_H__
#define MESH_FACE_H__

#include "global.h"
#include "math/vector.h"

BEGIN_PROJECT_NAMESPACE();

class Face {
 public:
  // Face constructor and destructor.
  Face(vec3i vertex_ = vec3i(), vec3i normal_ = vec3i(), vec3i texture_ = vec3i());
  ~Face();

  // Attributes
  vec3i vertex;		// Vextex indexes of the face
  vec3i normal;		// Normals indexes of the face
  vec3i texture;	// Texture indexes of the face
};

END_PROJECT_NAMESPACE();

#endif  // MESH_FACE_H__
