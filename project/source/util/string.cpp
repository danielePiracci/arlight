/// \file util/string.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
#include "util/string.h"

//#include "sstream"
//#include "stdexcept"

BEGIN_PROJECT_NAMESPACE();

std::string IntToStr(int n) {
  // TODO: try to use this implementation instead.
  //std::ostringstream result;
  //result << n;
  //return result.str();

  char buffer[20]; sprintf(buffer, "%d", n);
  return std::string(buffer);
}

/*
int StrToInt(const std::string& s) {
  int result;
  std::istringstream ss(s);
  ss >> result;
  if (!ss) throw std::invalid_argument("StrToInt");
  return result;
}
*/
END_PROJECT_NAMESPACE();
