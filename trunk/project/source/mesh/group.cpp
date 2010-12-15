/// \file mesh/face.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file implements the DissertationProject::Face class, 
/// declared at mesh/face.h.
#include "mesh/group.h"
//#include "../Includes/OpenGL.h"
//#include "../Util/TextureManagement.h"

BEGIN_PROJECT_NAMESPACE();

Group::Group() {}

Group::~Group() { 
	//mat.clear();
}

// To create the DL of surface
void Group::createDL() {
  // Add one more matIndex for the limit
  matIndex.push_back(faceList.size());

  // Obtain the number of material indexes ...
  const int nMatIndex = static_cast<int> (matIndex.size());
	
  // 
  dl.resize(nMatIndex - 1, 0);

  // Generate a display list for each group
  for (int i = 0; i < nMatIndex -1; ++i) {
    //	
    dl[i] = glGenLists(1);
		
    // Check if the display list was created
    //if (!glIsList(dl[i]))
    //  PRINT_LOG(TYPE_WARNING, "The display list #%d don't was create", i);

    // Add the information of the display list
    glNewList(dl[i], GL_COMPILE);
    glBegin(GL_TRIANGLES);
      // Check ig almost the textureList has define one texture coord
      //if (textureList.size() == 0) textureList.push_back(Vec2f());
      if (textureList.size() == 0) textureList.push_back(vec3f());

      // For each face
      for (int j = matIndex[i]; j < matIndex[i + 1]; ++j) {
        // Obtain the indexes of the vertex
        const vec3i v = faceList[j].vertex;
        const vec3i n = faceList[j].normal;	
        vec3i t = faceList[j].texture;

        // Chequear si hay alguna coord con indice -1
        if (t.x < 0) t.x = 0;
        if (t.y < 0) t.y = 0;
        if (t.z < 0) t.z = 0;

        // Draw the vertex
        glTexCoord2f(textureList[t.x].x, textureList[t.x].y);
        glNormal3f(normalList[n.x].x, normalList[n.x].y, normalList[n.x].z);
        glVertex3f(vertexList[v.x].x, vertexList[v.x].y, vertexList[v.x].z);

        glTexCoord2f(textureList[t.y].x, textureList[t.y].y);
        glNormal3f(normalList[n.y].x, normalList[n.y].y, normalList[n.y].z);
        glVertex3f(vertexList[v.y].x, vertexList[v.y].y, vertexList[v.y].z);
					
        glTexCoord2f(textureList[t.z].x, textureList[t.z].y);
        glNormal3f(normalList[n.z].x, normalList[n.z].y, normalList[n.z].z);
        glVertex3f(vertexList[v.z].x, vertexList[v.z].y, vertexList[v.z].z);
      }
    glEnd();
    glEndList(); 
  }
}

void Group::drawDL(int renderMode) {
  const int nDisplayLists = static_cast<int> (dl.size());
  for (int i = 0; i < nDisplayLists; ++i) {
    // 
//    if (!(renderMode & TRANSLUCENT) && mat[i]->alpha < 1.0) continue;
//    if (!(renderMode & OPAQUE_) && mat[i]->alpha == 1.0) continue;
		
    // Render the geometry.
//    BEGIN_MATERIAL(mat[i], renderMode);
      glCallList(dl[i]);	
//    END_MATERIAL(mat[i], renderMode);
  }
}

END_PROJECT_NAMESPACE();
