/// \file renderer/frame_buffer.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/11
/// \version 1.0
///
/// \brief This file implements the DissertationProject::FrameBuffer class, 
/// declared at material/material.h.
#include "renderer/frame_buffer.h"
#include "base/locator_inl.h"
#include "texture/opengl_texture.h"
#include "util/string.h"

// TODO: Implement object type pattern design for textures.

BEGIN_PROJECT_NAMESPACE();

FrameBuffer::FrameBuffer(int width, int height, GLuint format, bool has_depth_buffer) 
    : width_(width), height_(height), format_(format), has_depth_buffer_(has_depth_buffer) {
  
  // TODO: agregar un assert cuando las texturas no es potencia de 2.

  // Allocate a framebuffer object.
  glGenFramebuffersEXT(1, &frame_buffer_name_);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame_buffer_name_);

  // Define the name for the framebuffer texture.
  texture_name_ = "Framebuffer" + IntToStr(frame_buffer_name_) + " texture";

  // Allocate the texture that we will rendert into.
  Locator::GetTextureManager()->RegisterTexture2D(texture_name_, width_, height_, NULL, format_ == GL_DEPTH_COMPONENT);
  texture_ = Locator::GetTextureManager()->GetTexture(texture_name_);

  // 
  OpenGLTexture *color_texture_ptr = dynamic_cast<OpenGLTexture*> (texture_.get());
  if (color_texture_ptr == NULL) { printf("Error accessing framebuffer's texture\n"); return; }  

  // Attach the framebuffer to the texture, which may be a depth texture.
  if (format_ == GL_DEPTH_COMPONENT) {
    //
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, color_texture_ptr->TextureName(), 0);
    
    // Disable drawing to any buffers, we only want the depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
  } else {
    // 
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_texture_ptr->TextureName(), 0);
  }

  if (has_depth_buffer) {
    // Allocate a render buffer for a depth buffer of the same size as the texture.
    glGenRenderbuffersEXT(1, &depth_render_buffer_);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_render_buffer_);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width_, height_);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    // Attach attach the render buffer to the frame buffer.
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_render_buffer_);
  }

  //Check if the process of create the frame buffer was successful.
  GLenum status;
  status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
  switch (status) {
    case GL_FRAMEBUFFER_COMPLETE_EXT: break;
    default: printf("Error: frame buffer\n");
  }

  // Set default frame buffer.
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

FrameBuffer::~FrameBuffer() {
  // TODO: verficar en que orden deben ser eliminados los recuros.

  // Delete resources.
  texture_.reset();
  
  // Bind to back buffer.
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  glDeleteFramebuffersEXT(1, &frame_buffer_name_);

  // 
  if (has_depth_buffer_) glDeleteRenderbuffersEXT(1, &depth_render_buffer_);
}

void FrameBuffer::Enable(bool init) {
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame_buffer_name_);
  glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);

  //glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
  glViewport(0, 0, width_, height_);

  if (init) {
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //glOrtho(0, width_, 0, height_, -1.0, 1.0);
    gluPerspective(45, 1.0, 0.01, 100);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

 //   glClearColor(0.0, 0.0, 0.0, 0.0);
 //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // TODO: podria pintar aca un plano con una textura ya cableada en el caso 
    // de que las cosas que haga no funcionen, poara poder ver que falla.
  }
}

void FrameBuffer::Disable() {

  glMatrixMode(GL_PROJECTION);  
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);  
  glPopMatrix();

  glPopAttrib();
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

  if (format_ == GL_DEPTH_COMPONENT) {
    glDrawBuffer(GL_BACK);
    glReadBuffer(GL_BACK);
  }
}

void FrameBuffer::Bind() {
  Locator::GetTextureManager()->EnableTexture(texture_name_);
}

END_PROJECT_NAMESPACE();
