/// \file mesh/mesh.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
// 
/// \brief This file declares the DissertationProject::Mesh class, which 
/// implement the basic functionalities of a mesh.
#ifndef MESH_H__
#define MESH_H__

#include "global.h"
#include "material/material.h"
#include "renderer/mesh_renderer.h"
#include "vector"

#include "boost/shared_ptr.hpp"

BEGIN_PROJECT_NAMESPACE();

class Mesh {
 public:
  /// \brief Standard constructor.
  Mesh();

  /// \brief Default destructor.
  virtual ~Mesh();

  /// \brief Method to load a mesh.
  virtual void Load(const std::string& file_path) = 0;

  /// \brief Method to render the mesh.
  void Render(bool apply_material = true);

  /// \brief Method to add a material to the mesh.
  /// \param[in] material Material to be add to the list of materials.
  void AddMaterial(const boost::shared_ptr<Material>& material);

  /// \brief Method to enable a material.
  /// \param[in] index Index of the material that will be enabled.
  void EnableMaterial(int index);

  /// \brief Method to disable a material.
  /// \param[in] index Index of the material that will be disable.
  void DisableMaterial(int index);

  /// \brief Method to get the number of materials in the mesh.
  /// \return int Number of materials stored in the mesh.
  inline int NumberOfMaterials() const;

 private:
  /// \brief Mesh renderer component.
  boost::shared_ptr<MeshRenderer> mesh_renderer_;

  /// \brief Materials contained on the mesh.
  std::vector<boost::shared_ptr<Material> > materials_;

  DISALLOW_COPY_AND_ASSIGN(Mesh);
};

END_PROJECT_NAMESPACE();

#endif  // MESH_H__
