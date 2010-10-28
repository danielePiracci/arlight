/// \file string.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0

#ifndef UTIL_STRING_H__
#define UTIL_STRING_H__

#include "string"
#include "vector"

BEGIN_PROJECT_NAMESPACE();

std::vector<std::string> Split(std::string s, std::string delim) {
  std::vector<std::string> res; int pos;
  while ((pos = s.find(delim)) != -1) {
    if (pos) res.push_back(s.substr(0, pos));
    s.erase(0, pos + delim.size());
  } if (!s.empty()) res.push_back(s);
  return res;
}

// Function to get path of a file without the name of the file
// for GetPathWithOutFileName("Data/Textures/wall.jpg") return "Data/Textures/"
inline std::string GetPathWithOutFileName(std::string path) {
  // Return the substring with the path
  return path.substr(0, path.rfind("/") + 1);
}

// 
// for example; path = "Data/Texture/wall.jpg" return "Data/Texture"
inline std::string GetPathWithOutLastSlash(std::string path) {
  return path.substr(0, path.rfind("/"));
}

//
// for example; path = "../Data/texture" return "Data/Texture"
inline std::string GetPathWithOutFirstSlash(std::string path) {
  return path.substr(path.find("/") + 1);
}

// Return the extension of a file.
// For example; path = "/Data/Model/home.obj" return "obj"
inline std::string GetExt(const std::string& path) {
  return path.substr(path.rfind(".") + 1);
}

// TODO: create a method to change al the \ for / in a path ...

// Return the fileName defined as "base name" + "file extension".
// For example; path = "/Data/Model/home.obj" return "home.obj"
inline std::string GetFileName(const std::string& path) {
  if (path.find("/") != -1) return path.substr(path.rfind("/") + 1);
  else return path.substr(path.rfind("\\") + 1);
}

// Return the base file name.
// For example; path = "/Data/Model/home.obj" return "home".
inline std::string GetBaseFileName(const std::string& path) {
  const std::string fileName = GetFileName(path);
  return fileName.substr(0, fileName.rfind(_T(".")));
}

// Function to get path for the origin of one ..
// for example; src = "Data/texture/wall.jpg" and dest = "../Model/home.obj"
//				return "Data/Model/home.obj"
inline std::string GetAPathFromOne(std::string src, std::string dest) {
  // Check if the source has file or is only a path.
  // So, remove the file name.
  if (src.find(".") != -1) src = GetPathWithOutLastSlash(src);

  // 
  while (dest.find("../") != -1) {
    dest = GetPathWithOutFirstSlash(dest);
    src = GetPathWithOutLastSlash(src);
  }

  // Return the path builded
  if (src.empty()) return dest;
  return src + std::string("/") + dest;
}


// Function to check if a file exist.
//   Return True if the file exist, otherwise false.
inline bool fileExist(const std::string& path) {
  FILE *f = fopen(path.c_str(), "r");
  if (f == NULL) return false;
  fclose(f); return true;
}

END_PROJECT_NAMESPACE();

#endif  // UTIL_STRING_H__
