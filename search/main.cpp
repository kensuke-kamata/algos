#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "hash.h"

int main(int, char**){
  // Test with integers
  int int_arr[] = {1, 5, 8, 10, 3, 2};
  size_t int_size = sizeof(int_arr) / sizeof(int_arr[0]);

  HashSearch<int> int_search;
  std::cout << "search<int>: " << 10 << ": "
            << (int_search.search(int_arr, int_size, 10) ? "Found" : "Not Found") << std::endl;
  std::cout << "search<int>: " << 7  << ": "
            << (int_search.search(int_arr, int_size, 7) ? "Found" : "Not Found") << std::endl;

  // Test with strings
  std::string str_arr[] = {"apple", "banana", "orange", "melon", "peach"};
  size_t str_size = sizeof(str_arr) / sizeof(str_arr[0]);

  HashSearch<std::string> str_search;
  std::cout << "search<std::string>: " << "banana" << ": "
            << (str_search.search(str_arr, str_size, "banana") ? "Found" : "Not Found") << std::endl;
  std::cout << "search<std::string>: " << "kiwi" << ": "
            << (str_search.search(str_arr, str_size, "kiwi") ? "Found" : "Not Found") << std::endl;

  return 0;
}
