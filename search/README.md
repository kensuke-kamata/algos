# Search

## HashSearch

The `HashSearch` implementation provides a generic template-based hash table for efficient data search operations. It supports integer and string data types by default, using specialized hash functions to map the values to a finite space managed by a hash table.

### HashSearch: Overview

The implementation consists of several template classes that work together to provide a complete hash table search functionality:

- `HashFunction<T>`: A template class with explicit specializations for `int` and `std::string` types. It defines the hash function used to map keys to table indices.
- `HashNode<T>`: A node structure that holds the value and a pointer to the next node, enabling collision resolution via chaining.
- `HashTable<T, HashFunc>`: A template class that represents the hash table itself, using separate chaining for collision handling.
- `ISearch<T>`: An interface with a pure virtual `search` function, which is implemented by the `HashSearch` class to search for values within an array.
- `HashSearch<T, HashFunc>`: A class that implements the `ISearch` interface, using the `HashTable` for storing and searching values.

### HashSearch: Details

#### Hash Functions

The hash functions are main components that affect the performance and collision rate of the hash table. Two specializations are provided:

##### Hash Functions: Integer Hash Function

The integer hash function is a simple modulus operator that returns the remainder of the value divided by the table size. It is a fast and effective way to handle integer keys.

```cpp
template <>
class HashFunction<int> {
 public:
  size_t operator()(const int &value, size_t size) const {
    return value % size;
  }
};
```

##### Hash Functions: String Hash Function

The string hash function uses a polynomial rolling hash approach, which is a common and effective method for hashing strings.

Here's the formula for a simple polynomial rolling hash function:

$$
hash(s)=s[0]+s[1]\cdot p+s[2]\cdot p^2+...+s[n-1]\cdot p^{n-1} \mod m
$$

where:

- $s[i]$ is the ASCII value of the $i$-th character in the string.
- $p$ is a prime number (base), chosen to be not too small.
- $n$ is the length of the string.
- $m$ is a large prime number, chosen to fit the hash into a fixed size.

```cpp
template <>
class HashFunction<std::string> {
 public:
  size_t operator()(const std::string &value, size_t size) const {
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
```

The hash calculation is based on the idea of treating the string as a number in base `prime_base`, with the modulus `prime_mod` keeping the calculations within a fixed numeric range to prevent overflow and collisions. Each character's ASCII value (offset to start from `1` for `'a'`) contributes to the hash. It's scaled by its position in the string, using powers of `prime_base`.

The use of modular arithmetic ensures that the hash value and the power of `prime_base` (`prime_pow`) remain within the range of `unsigned long` (which is supposed to be a large enough type in this computation process). The `prime_mod` value is chosen to be a large prime to reduce collisions and provide a uniform distribution of hash codes. In this implementation, the `prime_mod` is chosen as `1e9 + 9`, a large prime number which is less than the maximum value of `unsigned long`.

#### Hash Table and Search Classes

The `HashTable` and `HashSearch` classes use these hashing strategies to store and search for data. `HashSearch` pre-populates the hash table with the given array by ($O(n)$) before performing the search operation, offering an efficient search time complexity that, on average, is close to $O(1)$ depending on the hash function's ability to distribute the keys uniformly.
