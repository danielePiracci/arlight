/// \file global.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
///
/// \brief This file contain some macros of general purpose for the application.
#ifndef GLOBAL_H__
#define GLOBAL_H__

#ifdef _WIN32
  // Disable deprecated funtions warnings.
  #pragma warning(disable : 4996)
#endif 

// Macros to begin and end the global namespace declaration of the application.
#define BEGIN_PROJECT_NAMESPACE() namespace DissertationProject {
#define END_PROJECT_NAMESPACE() };

// Macros to begin and end a sub namespace.
#define BEGIN_NAMESPACE(namespace_name) namespace namespace_name {
#define END_NAMESPACE(namespace_name) };

// Macro to disallow the copy constructor and operator= functions.
// This should be used in the private: declarations for a class.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator =(const TypeName&)

#endif  // GLOBAL_H__
