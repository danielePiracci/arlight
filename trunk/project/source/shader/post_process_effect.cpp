/// \file shader/post_process_effect.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/29
/// \version 1.0
///
/// \brief This file implements the DissertationProject::PostProcessEffect class, 
/// declared at shader/PostProcessEffect.h.
#include "shader/post_process_effect.h"

BEGIN_PROJECT_NAMESPACE();

PostProcessEffect::PostProcessEffect(const boost::shared_ptr<Shader>& shader,
                                     const boost::shared_ptr<FrameBuffer>& frame_buffer)
    : frame_buffer_(frame_buffer), Effect(shader) { }

PostProcessEffect::~PostProcessEffect() {
  frame_buffer_.reset();
}

void PostProcessEffect::Enable() {
  //
  Effect::Enable();
  frame_buffer_->Enable();
}

void PostProcessEffect::Disable() {
  //
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // verificar si no tengo que colocar esto de otra manera.
  const int kWidth = frame_buffer_->width();
  const int kHeight = frame_buffer_->height();
  glOrtho(0, kWidth, kHeight, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //
  glColor4f(1, 1, 1, 1.0f);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(0, 0);
    glTexCoord2f(1, 1);
    glVertex2f(kWidth, 0);
    glTexCoord2f(1, 0);
    glVertex2f(kWidth, kHeight);
    glTexCoord2f(0, 0);
    glVertex2f(0, kHeight);
  glEnd();

  //
  frame_buffer_->Disable();
  Effect::Disable();
}

END_PROJECT_NAMESPACE();
