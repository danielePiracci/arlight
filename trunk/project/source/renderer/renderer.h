/// \file renderer/renderer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
/// 
/// \brief This file declares the DissertationProject::Renderer class, 
/// which implement the basic functionalities of a renderer.
#ifndef RENDERER_H__
#define RENDERER_H__

#include "global.h"
#include "math/vector.h"
#include "texture/texture_manager.h"
#include "renderer/mesh_renderer.h"

#include "vector"

BEGIN_PROJECT_NAMESPACE();

// Forward-declare the Camera, Light Material and Mesh classes.
class Camera;
class Light;
class Material;

class Renderer {
 public:  
  /// \brief Standard constructor.
  Renderer();

  /// \brief Default destructor.
  virtual ~Renderer();

  /// \brrief Method to get a new texture object.
  virtual boost::shared_ptr<Texture> GetNewTexture() const = 0;

  /// \brief Method to get a new mesh renderer object.
  virtual boost::shared_ptr<MeshRenderer> GetNewMeshRenderer() const = 0;

/*
  /// \brief Method to start the render.
  virtual void BeginRender() = 0;

  /// \brief Method to finish the render.
  virtual void EndRender() = 0;

  /// \brief Method to clear the renderer buffers.
  /// \param[in] color Default color for the color buffer.
  virtual void ClearBuffer(const vec4i& color) = 0;

  /// \brief Method to load a mesh.
  /// \param[in] file_path Mesh file path.
  virtual void LoadMesh(const std::string& file_path) = 0;

  /// \brief Method to set up a camera.
  /// \param[in] camera Camera to be used in the renderer.
  virtual void SetCamera(const Camera& camera) = 0;

  /// \brief Method to display a mesh.
  /// \param[in] mesh file path of the mesh that will be rendered.
  /// \param[in] apply_material Flag to know if the mesh will apply the 
  /// material.
  virtual void RenderMesh(const std::string& file_path,
                          bool apply_material = true) = 0;

  ///// \brief Method to display a mesh.
  ///// \param[in] mesh Mesh that will be rendered.
  ///// \param[in] apply_material Flag to know if the mesh will apply the 
  ///// material.
  //virtual void RenderMesh(Mesh<MeshHandler>& mesh,
  //                        bool apply_material = true) = 0;

  /// \brief Method to render a box.
  virtual void RenderBox() = 0;

  /// \brief Method to start the use of a light.
  /// \param[in] light Light that will be enable.
  virtual void EnableLight(const Light& light) = 0;

  /// \brief Method to stop the use of a light.
  /// \param[in] light Light that will be disable.
  virtual void DisableLight(const Light& light) = 0;

  /// \brief Method to start the use of a material.
  /// \param[in] material Material that will be enable.
  virtual void EnableMaterial(const Material& material) = 0;

  /// \brief Method to stop the use of a material.
  /// \param[in] material Material that will be disable.
  virtual void DisableMaterial(const Material& material) = 0;

  /// \brief Method to enable the use of the depth buffer.
  virtual void EnableDepthBuffer() = 0;

  /// \brief Method to disable the use of the depth buffer.
  virtual void DisableDepthBuffer() = 0;

  /// \brief Method to enable the use of alpha blending.
  virtual void EnableAlphaBlending() = 0;

  /// \brief Method to disable the use of alpha blending.
  virtual void DisableAlphaBlending() = 0;

  /// \brief Method to enable the use of the stencil buffer.
  virtual void EnableStencilBuffer() = 0;

  /// \brief Method to disable the use of the stencil buffer.
  virtual void DisableStencilBuffer() = 0;

  /// \brief Method to start the use of stencil shadows.
  virtual void EnableStencilShadow() = 0;

  /// \brief Method to stop the use of stencil shadows.
  virtual void DisableStencilShadow() = 0;

  /// \brief Method to start the use of stencil for reflexion.
  virtual void EnableStencilReflexion() = 0;

  /// \brief Method to stop the use of stencil for reflexion.
  virtual void DisableStencilReflexion() = 0;

  /// \brief Method to set the current matrix as identity.
  virtual void LoadIdentity() = 0;

  /// \brief Method to apply the current matrix.
  virtual void ApplyTransformations() = 0;

  /// \brief Method to apply a scale to the current matrix.
  /// \param[in] x Scale factor in x axis.
  /// \param[in] y Scale factor in y axis.
  /// \param[in] z Scale factor in z axis.
  virtual void Scale(float x, float y, float z) = 0;

  /// \brief Method to apply a tranlation to the current matrix.
  /// \param[in] x Translate factor in x axis.
  /// \param[in] y Translate factor in y axis.
  /// \param[in] z Translate factor in z axis.
  virtual void Translate(float x, float y, float z) = 0;

  /// \brief Method to apply a rotation over the x axis.
  /// \param[in] angle Angle of rotation over the x axis.
  virtual void RotateX(float angle) = 0;

  /// \brief Method to apply a rotation over the y axis.
  /// \param[in] angle Angle of rotation over the y axis.
  virtual void RotateY(float angle) = 0;

  /// \brief Method to apply a rotation over the z axis.
  /// \param[in] angle Angle of rotation over the z axis.
  virtual void RotateZ(float angle) = 0;

  /// \brief Method to multiply the matrix by the current matrix.
  /// \param[in] matrix Matrix to multiply by the current matrix.
  virtual void Multiply(const float* matrix) = 0;

  /// \brief Method to create a shadow matrix and then multiply it by the 
  /// current matrix.
  /// \param[in] light Light used to calculate the shadow matrix.
  /// \param[in] plane Plane used to calculate the shadow matrix.
  virtual void ShadowMatrix(const vec4f& light, const vec4f& plane) = 0;

  /// \brief Method to push the current matrix in the matrixes list.
  virtual void PushMatrix() = 0;

  /// \brief Method to pop the last matrix in the matrixes list.
  virtual void PopMatrix() = 0;

  /// \brief Method to render a text message.
  virtual void DrawText(int left, int top, int height, int width, const std::string& message) = 0;

  /// \brief Method to set the render fill mode.
  virtual void SetFillMode(int fill_mode) = 0;
*/
  enum FillMode {
    FILL_POINT = 1,
    FILL_WIREFRAME = 2,
    FILL_SOLID = 3,
  };

 private:
  DISALLOW_COPY_AND_ASSIGN(Renderer);
};

END_PROJECT_NAMESPACE();

#endif  // RENDERER_H__
