#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class HashFunction;

// Specialization of HashFunction for int type
template <>
class HashFunction<int> {
 public:
  size_t operator()(const int &value, size_t size) const {
    // Simple modulus hash function for integers
    return value % size;
  }
};

template <>
class HashFunction<std::string> {
 public:
  size_t operator()(const std::string &value, size_t size) const {
    // Polynomial rolling hash function for strings
    const unsigned long prime_base = 31;
    const unsigned long prime_mod = 1e9 + 9;
    unsigned long hash_value = 0;
    unsigned long prime_pow = 1;
    for (char c : value) {
      hash_value = (hash_value + (c - 'a' + 1) * prime_pow) % prime_mod;
      prime_pow = (prime_pow * prime_base) % prime_mod;
    }
    return hash_value % size;
  }
};

template <typename T>
class HashNode {
 public:
  T value;
  HashNode *next;

  HashNode(T value) : value(value), next(nullptr) {}
};

template <typename T, typename HashFunc = HashFunction<T>>
class HashTable {
  std::vector<HashNode<T> *> table;
  size_t size;
  HashFunc hash_function;

 public:
  HashTable(size_t size) : size(size), table(size, nullptr) {}
  ~HashTable() {
    for (auto head : table) {
      while (head) {
        auto next = head->next;
        delete head;
        head = next;
      }
    }
  }

  void insert(T value) {
    auto index = hash_function(value, size);
    auto node = new HashNode<T>(value);
    node->next = table[index];
    table[index] = node;
  }

  bool search(T value) {
    auto index = hash_function(value, size);
    auto head = table[index];
    while (head) {
      if (head->value == value) {
        return true;
      }
      head = head->next;
    }
    return false;
  }
};

template <typename T>
class ISearch {
 public:
  virtual bool search(T* arr, size_t size, T target) = 0;
  virtual ~ISearch() {}
};

template <typename T, typename HashFunc = HashFunction<T>>
class HashSearch : public ISearch<T> {
  HashTable<T, HashFunc> table;

 public:
  HashSearch(size_t size = 100) : table(size) {}

  bool search(T *arr, size_t size, T target) override {
    for (size_t i = 0; i < size; i++) {
      table.insert(arr[i]);
    }
    return table.search(target);
  }
};

int main(int, char**){
  // Test with integers
  int int_arr[] = {1, 5, 8, 10, 3, 2};
  size_t int_size = sizeof(int_arr) / sizeof(int_arr[0]);

  HashSearch<int> int_search;
  int int_target = 10;

  std::cout << "search<int>: " << int_target << ":"
            << (int_search.search(int_arr, int_size, int_target) ? "Found" : "Not Found") << std::endl;

  // Test with strings
  std::string str_arr[] = {"apple", "banana", "orange", "melon", "peach"};
  size_t str_size = sizeof(str_arr) / sizeof(str_arr[0]);

  HashSearch<std::string> str_search;
  std::string str_target = "banana";

  std::cout << "search<std::string>: " << str_target << ": "
            << (str_search.search(str_arr, str_size, str_target) ? "Found" : "Not Found") << std::endl;

  return 0;
}
