/// \file shader/post_process_effect.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/11/29
/// \version 1.0
///
/// \brief This file declares the DissertationProject::PostProcessEffect class, 
/// which implement the basic functionalities of a post process effect.
/// The user should pass the parameters to the shader between the calls to 
/// enable and disable.
#ifndef POST_PROCESS_EFFECT_H__
#define POST_PROCESS_EFFECT_H__

#include "global.h"
#include "shader/effect.h"
#include "renderer/frame_buffer.h"

BEGIN_PROJECT_NAMESPACE();

// TODO: By defaul the post process effect could send to the shader common 
// values such as textures size.

class PostProcessEffect : public Effect {
 public:
  /// \brief Standard constructor.
  PostProcessEffect(const boost::shared_ptr<Shader>& shader,
                    const boost::shared_ptr<FrameBuffer>& frame_buffer);

  /// \brief Default destructor.
  virtual ~PostProcessEffect();

  /// \brief Method to start the use of the material.
  void Enable();

  /// \brief Method to stop the use of the material.
  void Disable();

  ///
  boost::shared_ptr<FrameBuffer> frame_buffer() const { return frame_buffer_; }

 private:
  boost::shared_ptr<FrameBuffer> frame_buffer_;

  DISALLOW_COPY_AND_ASSIGN(PostProcessEffect);
};

END_PROJECT_NAMESPACE();

#endif  // POST_PROCESS_EFFECT_H__
