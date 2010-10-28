/// \file mesh/face.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Face class, 
/// declared at mesh/face.h.
#include "mesh/Face.h"

BEGIN_PROJECT_NAMESPACE();

Face::Face(vec3i vertex_, vec3i normal_, vec3i texture_)
    : vertex(vertex_), normal(normal_), texture(texture_) {}

Face::~Face() {}

END_PROJECT_NAMESPACE();
