// Author: Juan Carlos De Abreu (jcabreur@gmail.com)
//
// This class define an interface for techniques that implement culling.

#ifndef CULL_CULL_H__
#define CULL_CULL_H__

#include "../global.h"
#include "../Math/Vector.h"

BEGIN_PROJECT_NAMESPACE();

class ICull {
 public:
  // ICull constructor and destructor.
  ICull();
  virtual ~ICull();

  // Methods to know if a point, box and sphere are not visible.
  virtual bool IsPointVisiable(const vec3f& pos) = 0;
  virtual bool IsBoxVisiable(const vec3f& pos, float size) = 0;
  virtual bool IsSphereVisiable(const vec3f& pos, float radius) = 0;

 private:
   DISALLOW_COPY_AND_ASSIGN(ICull);
};

END_PROJECT_NAMESPACE();

#endif  // CULL_CULL_H__
