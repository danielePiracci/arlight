// Author: Juan Carlos De Abreu (jcabreur@gmail.com)

#include "frustum_culling.h"

BEGIN_PROJECT_NAMESPACE();

FrustumCulling::FrustumCulling() {}

FrustumCulling::~FrustumCulling() {}
/*
void FrustumCulling::CalculateFrustum(const Mat4f& model_view,
                                      const Mat4f& projection) {
  // Create the clip.
  const Mat4f clip = model_view * projection;

  // Calculate the right side of the frustum.
  frustum_[0] = math::Plane(clip[3]  - clip[0],
                            clip[7]  - clip[4],
                            clip[11] - clip[8],
                            clip[15] - clip[12]);

  // Calculate the left side of the frustum.
  frustum_[1] = math::Plane(clip[3]  + clip[0],
                            clip[7]  + clip[4],
                            clip[11] + clip[8],
                            clip[15] + clip[12]);

  // Calculate the bottom side of the frustum.
  frustum_[2] = math::Plane(clip[3]  + clip[1],
                            clip[7]  + clip[5],
                            clip[11] + clip[9],
                            clip[15] + clip[13]);

  // Calculate the top side of the frustum.
  frustum_[3] = math::Plane(clip[3]  - clip[1],
                            clip[7]  - clip[5],
                            clip[11] - clip[9],
                            clip[15] - clip[13]);

  // Calculate the far side of the frustum.
  frustum_[4] = math::Plane(clip[3]  - clip[2],
                            clip[7]  - clip[6],
                            clip[11] - clip[10],
                            clip[15] - clip[14]);
	
  // Calculate the near side of the frustum.
  frustum_[5] = math::Plane(clip[3]  + clip[2],
                            clip[7]  + clip[6],
                            clip[11] + clip[10],
                            clip[15] + clip[14]);

  // Normalize the sides of the frustum.
  Normalize();
}

void FrustumCulling::Normalize() {
  // Loop through each side of the frustum and normalize it.
  for(int i = 0; i < kNumberOfFrustumSides; i++)
    frustum_[i].normalize();
}

bool FrustumCulling::IsPointVisiable(const vec3f& position) {
  // Loop through each side of the frustum and test if the point lies outside
  // any of them.
  for (int i = 0; i < kNumberOfFrustumSides; i++)
    if (getDistance(frustum_[i], position) < 0) return false;
  return true;
}

bool FrustumCulling::IsSphereVisiable(const vec3f& position, float radius) {
  // Loop through each side of the frustum and test if the sphere lies outside
  // any of them.
  for(int i = 0; i < kNumberOfFrustumSides; i++)
    if (getDistance(frustum_[i], position) < -radius) return false;
  return true;
}

bool FrustumCulling::IsBoxVisiable(const vec3f& position, float size) {
  // Calculate the bounding box.
  const Vec3f min = position - size;
  const Vec3f max = position + size;	

  // Loop through each side of the frustum and test if the box lies outside any
  // of them.
  for (int i = 0; i < kNumberOfFrustumSides; i++) {
    if (getDistance(frustum_[i], Vec3f(min.x, min.y, min.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(max.x, min.y, min.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(min.x, max.y, min.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(max.x, max.y, min.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(min.x, min.y, max.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(max.x, min.y, max.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(min.x, max.y, max.z)) > 0) continue;
    if (getDistance(frustum_[i], Vec3f(max.x, max.y, max.z)) > 0) continue;
    return false;
  }
  return true;
}
*/
END_PROJECT_NAMESPACE();
