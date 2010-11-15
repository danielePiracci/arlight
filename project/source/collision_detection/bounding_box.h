/// \file collision_detection/bounding_box.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/09/24
/// \version 1.0
///
/// \brief This file declares the DissertationProject::BoundingBox class, 
/// which implement the basic functionalities of a bounding box.
#ifndef BOUNDING_BOX_H__
#define BOUNDING_BOX_H__

#include "global.h"
#include "math/vector.h"

BEGIN_PROJECT_NAMESPACE();

class BoundingBox {
 public:
  /// \brief Standard constructor.
  BoundingBox();

  /// \brief Default destructor.
  ~BoundingBox();

  void Update(const vec3f& point);

  inline void Init(const vec3f& point) { min_point_ = point; max_point_ = point; }
  inline void set_min_point(const vec3f& min_point) { min_point_ = min_point; }
  inline void set_max_point(const vec3f& max_point) { max_point_ = max_point; }

  inline const vec3f& min_point() { return min_point_; }
  inline const vec3f& max_point() { return max_point_; }

 private:
  //
  vec3f min_point_;
  vec3f max_point_;

  DISALLOW_COPY_AND_ASSIGN(BoundingBox);
};

END_PROJECT_NAMESPACE();

#endif  // BOUNDING_BOX_H__
