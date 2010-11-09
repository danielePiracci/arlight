/// \file base/locator.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/22
/// \version 1.0
///
/// \brief This file declares the DissertationProject::Locator class, 
/// which implement the basic functionalities of a locator. Locator provides a 
/// global point of access to a service without coupling users to the concrete 
/// class that implements it.
#ifndef LOCATOR_H__
#define LOCATOR_H__

#include "global.h"
#include "renderer/renderer.h"
#include "mesh/mesh_manager.h"
#include "texture/texture_manager.h"

#include "boost/shared_ptr.hpp"

BEGIN_PROJECT_NAMESPACE();

class Locator {
 public:
  /// \brief Standard constructor.
  Locator();

  /// \brief Default destructor.
  ~Locator();

  /// \brief Method to initialize the services.
  inline static void Initilize();
   
  /// \brief Method to release all the services.
  inline static void Release();

  /// \brief Method to register the renderer of the application.
  /// \param[in] renderer Renderer for the application.
  inline static void Register(const boost::shared_ptr<Renderer>& renderer);

  /// \brief Method to register the Mesh Manager of the application.
  /// \param[in] mesh_manager Mesh Manager for the application.
  inline static void Register(const boost::shared_ptr<MeshManager>& mesh_manager);

  /// \brief Method to register the Texture Manager of the application.
  /// \param[in] texture_manager Texture Manager for the application.
  inline static void Register(const boost::shared_ptr<TextureManager>& texture_manager);
  
  /// \brief Method to have access to the renderer of the application.
  /// \return A Renderer that define the current renderer of the application.
  inline static boost::shared_ptr<Renderer>& GetRenderer();

  /// \brief Method to have access to the mesh manager of the application.
  /// \return A MeshManager that define the current mesh manager of the application.
  inline static boost::shared_ptr<MeshManager>& GetMeshManager();

  /// \brief Method to have access to the texture manager of the application.
  /// \return A TextureManager that define the current texture manager of the application.
  inline static boost::shared_ptr<TextureManager>& GetTextureManager();

 private:
  /// \brief Renderer service.
  static boost::shared_ptr<Renderer> renderer_;

  /// \brief Mesh Manager service.
  static boost::shared_ptr<MeshManager> mesh_manager_;

  /// \brief Texture Manager service.
  static boost::shared_ptr<TextureManager> texture_manager_;

  DISALLOW_COPY_AND_ASSIGN(Locator);
};

END_PROJECT_NAMESPACE();

#endif  // LOCATOR_H__
