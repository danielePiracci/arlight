/// \file mesh/group.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/20
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Group 
/// class, which implement the basic functionalities of a geometry group.
#ifndef MESH_GROUP_H__
#define MESH_GROUP_H__

#include "mesh/face.h"
#include "material/material.h"
//#include "../Base/Memory/SmartPointer.h"
#include "vector"

#include "boost/shared_ptr.hpp"

#include "opengl_includes.h"

BEGIN_PROJECT_NAMESPACE();

class Group {
 public:
  // Render Modes.
  enum { OPAQUE_ = 1, TRANSLUCENT = 2, MATERIAL = 4, TEXTURE = 8 };

  // Group constructor and destructor.
  Group();
  ~Group();

  // Attributes
// NOTE: verificar como voy a implementar esta parte..
//  std::vector< SmartPointer<Material> > mat;
  std::vector< boost::shared_ptr<Material> > mat;
  std::vector< int > matIndex;			// indices para los que aplica el material

  std::vector<vec3f> vertexList;		// List of vextexs of the model
  std::vector<vec3f> normalList;		// List of normals of the model
  //std::vector<vec2f> textureList;		// List of the texture coord of the model
  std::vector<vec3f> textureList;		// List of the texture coord of the model // TODO: Cambiar esto a vec2f cuando 
  std::vector<Face> faceList;		// List of the faces of the model

  //////////
  std::vector<GLuint> dl;			// Display lists of each material
  void createDL();
  void drawDL(int renderMode);
  /////////

};

END_PROJECT_NAMESPACE();

#endif  // MESH_GROUP_H__
