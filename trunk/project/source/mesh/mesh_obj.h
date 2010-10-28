/// \file mesh/mesh_obj.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/08/21
/// \version 1.0
// 
/// \brief This file declares the DissertationProject::MeshObj class, which 
/// implement the basic functionalities to load obj meshes.
#ifndef MESH_OBJ_H__
#define MESH_OBJ_H__

#include "global.h"
#include "string"
#include "vector"

#include "mesh/mesh.h"
#include "mesh/group.h"

#include "opengl_includes.h"

BEGIN_PROJECT_NAMESPACE();

class MeshObj : public Mesh {
 public:
  /// \brief Standard constructor.
  MeshObj();

  /// \brief Default destructor.
  ~MeshObj();

  virtual void Load(const std::string& file_path);


  /////////////////////////////////////
  /// Prueba para pintar el objeto....
  GLuint surfaceDL;  // Display List of the model surface

  void createSurfaceDL();

  void drawSurface(int renderMode);

  std::vector<Group> groupList;

  void process();
  /////////////////////////////////////

 private:
  DISALLOW_COPY_AND_ASSIGN(MeshObj);
};

END_PROJECT_NAMESPACE();

#endif  // MESH_OBJ_H__
