/// \file util/rand.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
#include "util/rand.h"

BEGIN_PROJECT_NAMESPACE();

float Rand(float min_range, float max_range) {
  return min_range + rand() * (max_range - min_range) / RAND_MAX;
}

END_PROJECT_NAMESPACE();
