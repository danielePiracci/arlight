/// \file singleton.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2009/11/07
/// \version 1.0
//
// This file define a class to create the design pattern singleton.
#ifndef BASE_SINGLETON_H__
#define BASE_SINGLETON_H__

#include "global.h"

BEGIN_PROJECT_NAMESPACE();

// Definition of the structure of Singleton
template<typename T>
class Singleton {
 public:
  // Singleton destructor.
  ~Singleton();

  // Methods to get the unique instance of T as pointer and as reference.
  static T& GetInstance();
  static T* GetInstancePtr();

 protected:
  // Singleton attribute, unique instance for of T.
  static T m_Instance;

  // Singleton constructor
  Singleton();
};

// Unique instance of T
template<typename T> T Singleton<T>::m_Instance;

// Standard constructor of Singleton
template<typename T> Singleton<T>::Singleton() {
  // Do anything ...
}

// Destructor of Singleton
template<typename T> Singleton<T>::~Singleton() {
  // Do anything ...
}

// Method to get the unique instance of T
template<typename T> T& Singleton<T>::GetInstance() {
  return m_Instance;
}

// Method to get the pointer of the unique instance of T
template<typename T> T* Singleton<T>::GetInstancePtr() {
  return &m_Instance;
}

END_PROJECT_NAMESPACE();

#endif  // BASE_SINGLETON_H__
