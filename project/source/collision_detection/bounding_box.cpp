/// \file collision_detection/bounding_box.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/09/24
/// \version 1.0
///
/// \brief This file implements the DissertationProject::BoundingBox class, 
/// declared at collision_detection/bounding_box.h.
#include "collision_detection/bounding_box.h"
#include "algorithm"

BEGIN_PROJECT_NAMESPACE();

BoundingBox::BoundingBox() { }

BoundingBox::~BoundingBox() { }

void BoundingBox::Update(const vec3f& point) {
  min_point_.x = std::min(min_point_.x, point.x);
  min_point_.y = std::min(min_point_.y, point.y);
  min_point_.z = std::min(min_point_.z, point.z);

  max_point_.x = std::max(max_point_.x, point.x);
  max_point_.y = std::max(max_point_.y, point.y);
  max_point_.z = std::max(max_point_.z, point.z);
}

END_PROJECT_NAMESPACE();
