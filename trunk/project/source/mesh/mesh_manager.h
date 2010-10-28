/// \file mesh/mesh_manager.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/20
/// \version 1.0
///
/// \brief This file declares the DissertationProject::MeshManager 
/// class, which implement the basic functionalities of a manager of mesh.
#ifndef MESH_MANAGER_H__
#define MESH_MANAGER_H__

#include "global.h"
#include "mesh/mesh.h"

#include "map"

#include "boost/shared_ptr.hpp"

BEGIN_PROJECT_NAMESPACE();

//template<typename T>
class MeshManager {
 public:
  /// \brief Standard constructor.
  MeshManager() { }

  /// \brief Default destructor.
  ~MeshManager() { }

  /// \brief Add a mesh with handler to the specified file path.
  /// \param[in] file_path Path where is located the mesh in the hard drive.
  /// \param[in] handler Pointer to the mesh handler.
  //void AddMesh(const std::string& file_path, T* handler);

  /// \brief Remove the specified mesh from the mesh manager.
  /// \param[in] file_path Path where is located the mesh in the hard drive.
  void RemoveMesh(const std::string& file_path);

  /// \brief Look up a mesh in the mesh manager.
  /// \param[in] file_path Path where is located the mesh in the hard drive.
  //boost::shared_ptr<Mesh<T> > GetMesh(const std::string& file_path) const;

  /// \brief Accessor method for the number of meshes stored in the manager.
  /// \return The number of meshes stored in the manager.
  int size() const;

 private:
  /// \brief Map with all contained textures.
  //std::map<std::string, boost::shared_ptr<Mesh<T> > > meshes_;
  std::map<std::string, boost::shared_ptr<Mesh> > meshes_;

  DISALLOW_COPY_AND_ASSIGN(MeshManager);
};
/*
template<typename T>
MeshManager<T>::MeshManager() { }

template<typename T>
MeshManager<T>::~MeshManager() {
  meshes_.clear();
}

template<typename T>
void MeshManager<T>::AddMesh(const std::string& file_path, T* handler) {
  meshes_[file_path] = boost::shared_ptr<Mesh<T> >(new Mesh<T>(handler));
}

template<typename T>
void MeshManager<T>::RemoveMesh(const std::string& file_path) {
  std::map<std::string, boost::shared_ptr<Mesh<T> > >::const_iterator it = meshes_.find(file_path);
  meshes_.erase(it);
}

template<typename T>
boost::shared_ptr<Mesh<T> > MeshManager<T>::GetMesh(const std::string& file_path) const {
  std::map<std::string, boost::shared_ptr<Mesh<T> > >::const_iterator it = meshes_.find(file_path);
  return it == meshes_.end() ? boost::shared_ptr<Mesh<T> >() : it->second;
}
*/

END_PROJECT_NAMESPACE();

#endif  // MESH_MANAGER_H__
