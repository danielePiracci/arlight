/// \file renderer/frame_buffer.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/11
/// \version 1.0
///
/// \brief This file declares the DissertationProject::FrameBuffer class, 
/// which implement the basic functionalities of a frame buffer.
#ifndef FRAME_BUFFER_H__
#define FRAME_BUFFER_H__

#include "global.h"
#include "opengl_includes.h"
#include "texture/texture.h"

#include "string"

#include "boost/shared_ptr.hpp"

// TODO: Add support to be able of render depth textures.

BEGIN_PROJECT_NAMESPACE();

class FrameBuffer {
 public:
  /// \brief Standard constructor.
  FrameBuffer(int width, int height, GLuint format, bool has_depth_buffer = false);

  /// \brief Default destructor.
  ~FrameBuffer();

  /// \brief Method to enable the render into the framebuffer.
  void Enable(bool init = true);

  /// \brief Method to disable the render into the framebuffer.
  void Disable();

  /// \brief Method to enable the use of the texture related to this framebuffer.
  void Bind();

  /// \brief Accessor method for the framebuffer width.
  inline int width() const { return width_; }

  /// \brief Accessor method for the framebuffer height.
  inline int height() const { return height_; }

  inline float GetAspect() const { return width_ * 1.0 / height_; }
  
  inline boost::shared_ptr<Texture> texture() const { return texture_; }
 
 private:
  /// \brief frame buffer width.
  int width_;

  /// \brief frame buffer height.
  int height_;

  /// \brief flag that define if the frame buffer has a depth buffer.
  bool has_depth_buffer_;

  /// \brief frame buffer id.
  GLuint frame_buffer_name_;

  /// \brief depth render buffer;
  GLuint depth_render_buffer_;

  /// \brief internal texture format.
  GLuint format_;

  /// \brief texture name.
  std::string texture_name_;

  /// \brief color texture.
  boost::shared_ptr<Texture> texture_;

  DISALLOW_COPY_AND_ASSIGN(FrameBuffer);
};

END_PROJECT_NAMESPACE();

#endif  // FRAME_BUFFER_H__
