/// \file base/locator.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/10/22
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Locator class, 
/// declared at base/locator.h.
#include "base/locator.h"

BEGIN_PROJECT_NAMESPACE();

boost::shared_ptr<Renderer> Locator::renderer_;
boost::shared_ptr<MeshManager> Locator::mesh_manager_;
boost::shared_ptr<TextureManager<int> > Locator::texture_manager_;

Locator::Locator() { }

Locator::~Locator() { }

END_PROJECT_NAMESPACE();
