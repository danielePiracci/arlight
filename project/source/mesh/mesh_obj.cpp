/// \file mesh/mesh_obj.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/08/21
/// \version 1.0
///
/// \brief This file implements the DissertationProject::MeshObj class, 
/// declared at mesh/mesh_obj.h.
#include "mesh/mesh_obj.h"

#include "mesh/face.h"
#include "mesh/group.h"

#include "tchar.h"

#include "util/string.h"

#include "cmath"

BEGIN_PROJECT_NAMESPACE();

MeshObj::MeshObj() { }

MeshObj::~MeshObj() { }

void MeshObj::Load(const std::string& file_path) {
  // Try to open the file
  FILE *f = fopen(file_path.c_str(), "r");
	
  // Check if the file was open
  if (f == NULL) {
    // TODO: Report the error in the Log
    // PRINT_LOG(TYPE_ERROR, "The file \"%s\" not was found!", lpszPathName);
    return;
  }
	
  const int MAX_LONG  = 200;

  _TCHAR str[MAX_LONG];

  Group g;		// To save the data temporaly of the groups
	
  // To mantain the refences of the model local to each group
  Face refIndex;
  refIndex.normal = 1;
  refIndex.texture = 1;
  refIndex.vertex = 1;

  // Load the data in the file
  while (fgets(str, MAX_LONG, f) != NULL) {
    // Obtain the type of line
    _TCHAR lineType[MAX_LONG];
    sscanf(str, "%s", lineType);
		
    // Check if is a comment line
    if (strcmp(lineType, "#") == 0) {
      // Do anything ...
      // Process the next line
      continue;
    }
		
    // Check if is a begin group line
    if (strcmp(lineType, "g") == 0) {
      // Check if a have a previus group
      if (g.vertexList.size() > 0) {
        // Check if the material was defined to the group
        //if(strcmp(g.mat.name.c_str(), "") == 0) {
        if (g.mat.size() == 0) {
          // Add the last material defined
// TODO: Ver como agregar los materiales al modelo.
//          g.mat.push_back(MATERIAL(_T("SceneNavigator_Default__")));
//          g.matIndex.push_back(0);
        }

        // Add the group to the groupList
        groupList.push_back(g);
        // Update the index reference ...
        refIndex.normal += g.normalList.size();
        refIndex.vertex += g.vertexList.size();
        refIndex.texture += g.textureList.size();
      }

	  g = Group();

      // Process the next line
      continue;
    }

    // Check if is a pathFile of materials
    if (strcmp(lineType, "mtllib") == 0) {
      // Obtain the path of the file that have the mtllib
      sscanf(str, "%*s %s", str);

      // Load the material library
// TODO: Agregar esta funcion, y ver como voy a hacer la funcionalidad para cargar los materiales.
//      LOAD_MATERIALS(GetAPathFromOne(file_path, str));
      // Process the next line
      continue;
    }
		
    // Check if is an use of a material
    if (strcmp(lineType, "usemtl") == 0) {
      // Obtain the material name
      sscanf(str, "%*s %s", str);

// TODO: Ver como voy a hacer la carga y el enlace de los materiales en la aplicacion.
//     g.mat.push_back(MATERIAL(str));
      g.matIndex.push_back(g.faceList.size());

      // Process the next line
      continue;
    }

    // Check if is a definition of a vertex
    if (strcmp(lineType, "v") == 0) {
      // To save the information of the vertex
      vec3f v;
      // Obtain the definition of a vertex
      sscanf(str, "%*s %f %f %f", &v.x, &v.y, &v.z);
      // Add the vertex to the vertexList
      g.vertexList.push_back(v);
      // Process the next line
      continue;
    }

    // Check if is a definition of a normal of a vextex
    if (strcmp(lineType, "vn") == 0) {
      // To save the information of the normal
      vec3f v;
      // Obtain the definition of a vertex
      sscanf(str, "%*s %f %f %f", &v.x, &v.y, &v.z);
      // Add the normal to the normalList
      g.normalList.push_back(v);
      // Process the next line
      continue;
    }

    // Check if is a definition of a texture coord of a vextex
    if (strcmp(lineType, "vt") == 0) {
      // To save the information of a texture coord
      //vec2f v;
      vec3f v;
      // Obtain the definition of a texture coord
      sscanf(str, "%*s %f %f", &v.x, &v.y);
      // Add the texture coord to the textureList
      g.textureList.push_back(v);
      // Process the next line
      continue;
    }

    // Check if is a definition of a face
    if (strcmp(lineType, "f") == 0) {
      // To save the information of the face
      Face f;
			        
      // Determin how many vertex have the face
      int nSlash = 0;
      for (int i = 0; i < (int)strlen(str); ++i)
        if (str[i] == '/') nSlash++;

      // If the face has more than 3 vertex ..
      if (nSlash > 6) {
        vec3i tmp;
        // Check if have a coord of texture
        if (strstr(str, "//") == NULL) {
          // Obtain the index of the face
          sscanf(str, "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f.vertex.x, &f.texture.x, &f.normal.x,
                &f.vertex.y, &f.texture.y, &f.normal.y, &f.vertex.z, &f.texture.z, &f.normal.z, &tmp.x, &tmp.y, &tmp.z);
        } else {
          // Obtain the index of the face
          sscanf(str, "%*s %d//%d %d//%d %d//%d %d//%d", &f.vertex.x, &f.normal.x,
                 &f.vertex.y, &f.normal.y, &f.vertex.z, &f.normal.z, &tmp.x, &tmp.z);	
        }

        // Change the range of the index to [0..n-1]
        f.vertex -= refIndex.vertex;
        f.normal -= refIndex.normal;
        f.texture -= refIndex.texture;
        tmp.x -= refIndex.vertex.x;
        tmp.y -= refIndex.texture.x;
        tmp.z -= refIndex.normal.x;
				
        // Add the face to the faceList
        g.faceList.push_back(f);

        f.vertex.y = f.vertex.z; f.vertex.z = tmp.x;
        f.texture.y = f.texture.z; f.texture.z = tmp.y;
        f.normal.y = f.normal.z; f.normal.z = tmp.z;
        g.faceList.push_back(f);
      } else {
        // Check if have a coord of texture
        if (strstr(str, "//") == NULL) {
          // Obtain the index of the face
          sscanf(str, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &f.vertex.x, &f.texture.x, &f.normal.x,
                 &f.vertex.y, &f.texture.y, &f.normal.y, &f.vertex.z, &f.texture.z, &f.normal.z);
        } else {
          // Obtain the index of the face
          sscanf(str, "%*s %d//%d %d//%d %d//%d", &f.vertex.x, &f.normal.x,
                 &f.vertex.y, &f.normal.y, &f.vertex.z, &f.normal.z);	
        }

        // Change the range of the index to [0..n-1]
        f.vertex -= refIndex.vertex;
        f.normal -= refIndex.normal;
        f.texture -= refIndex.texture;			
				
        // Add the face to the faceList
        g.faceList.push_back(f);
      }
			
      // Process the next line
      continue;
    }

    // TODO: If the line is the unknown type report a warning
    // PRINT_LOG(TYPE_WARNING, "The file %s has a unknown line \"%s\"", lpszPathName, str);
  }

  // Check if the material was defined to the group
  if (g.mat.size() == 0) {
    // Add the last material defined
// TODO: Agregar esta linea a la carga de los materiales.
//    g.mat.push_back(MATERIAL(_T("SceneNavigator_Default__")));
    g.matIndex.push_back(0);
  }

  // Add the last group to groupList
  groupList.push_back(g);

  // Close th file
  fclose(f);

  // Normalize the model
  process();
}

void MeshObj::process() {
	// Check if i have a groplist
	if(groupList.size() <= 0) {
      // TODO: print a error message on the log.
		// PRINT_LOG(TYPE_ERROR, "The model don't have a data in the groupList");
		return;
	}

    vec3f vMin, vMax;

	// Initialize the bounding box
	vMin = groupList[0].vertexList[0];
	vMax = groupList[0].vertexList[0];

	// Obtain the number of groups
	const int nGroups = static_cast<int> (groupList.size());

	// Search value of the vertex of the bouding box 
	for(int i = 0; i < nGroups; ++i) {
		// Obtain the number of vertex of the group i
		const int nVertex = static_cast<int> (groupList[i].vertexList.size());

		for(int j = 0; j < nVertex; ++j) {
			// Obtain the vertex
			const vec3f v = groupList[i].vertexList[j];
			// Check if out of the bounding box, then update this values
			if(v.x < vMin.x) vMin.x = v.x;
			if(v.y < vMin.y) vMin.y = v.y;
			if(v.z < vMin.z) vMin.z = v.z;
			if(v.x > vMax.x) vMax.x = v.x;
			if(v.y > vMax.y) vMax.y = v.y;
			if(v.z > vMax.z) vMax.z = v.z;
		}
	}
	// calculate the center of the model
	const vec3f center = (vMin + vMax) / 2.f;
	
	// Calculate the axis with more diference in the object
	float maxDistance = 1.f / (std::max(vMax.x - vMin.x, std::max(vMax.y - vMin.y, vMax.z - vMin.z)));

	// Translate the object to (0,0,0) and scale
	for(int i = 0; i < nGroups; ++i) {
		// Obtain the number of vertex of the group i
		const int nVertex = static_cast<int> (groupList[i].vertexList.size());
		// Translate and scale the vertex of the group i
		for(int j = 0; j < nVertex; ++j) {
			groupList[i].vertexList[j] -= center;
			groupList[i].vertexList[j] *= maxDistance;
		}
	}

	// Translate the bounding box to the center
	vMin -= center;
	vMax -= center;

	// Scale the model
	vMin *= maxDistance;
	vMax *= maxDistance;

	// Create all display list of the model
	//createGridDL();
	//createPointDL();	
	createSurfaceDL();
	//createBoundingBoxDL();
}

void MeshObj::createSurfaceDL() {
  const int kNumberOfGroups = static_cast<int> (groupList.size());
  for (int i = 0; i < kNumberOfGroups; ++i)
    groupList[i].createDL();
}

void MeshObj::drawSurface(int renderMode)  { 
  for (int i = 0; i < (int)groupList.size(); ++i)
    groupList[i].drawDL(renderMode);
}

END_PROJECT_NAMESPACE();
