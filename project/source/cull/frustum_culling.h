// Author: Juan Carlos De Abreu (jcabreur@gmail.com)
//
// This class implement the Frustum Culling using the modelview and projection 
// matrix.

#ifndef CULL_FRUSTUM_CULLING_H__
#define CULL_FRUSTUM_CULLING_H__

#include "../global.h"
#include "cull.h"
#include "../Math/Vector.h"
//#include "../Math/Matrix.h"
//#include "../Math/Plane/Plane-inl.h"

BEGIN_PROJECT_NAMESPACE();

class FrustumCulling : public ICull {
 public:
  // FrustumCulling constructor and destructor.
  FrustumCulling();
  ~FrustumCulling();

  // Method to create the planes of each side of the frustum.
//  void CalculateFrustum(const Mat4f& model_view, const Mat4f& projection);
  
  // Methods to know if a point, box and sphere are inside of a frustrum
  // otherwise the object is not visible.
//  virtual bool IsPointVisiable(const vec3f& position);
//  virtual bool IsBoxVisiable(const vec3f& position, float size);
//  virtual bool IsSphereVisiable(const vec3f& position, float radius);

 private:
  // Method to normalize each plane side of the frustum.
  void Normalize();
  
  // FrustrumCulling attibutes.
  static const int kNumberOfFrustumSides = 6;
//  math::Plane frustum_[kNumberOfFrustumSides];
  DISALLOW_COPY_AND_ASSIGN(FrustumCulling);
};

END_PROJECT_NAMESPACE();

#endif  // CULL_FRUSTUM_CULLING_H__
