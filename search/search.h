#pragma once

template <typename T>
class ISearch {
 public:
  virtual bool search(T* arr, size_t size, T target) = 0;
  virtual ~ISearch() {}
};
