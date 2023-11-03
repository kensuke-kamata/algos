# Levenshtein Distance

## Overview

The Levenshtein distance is a string metric for measuring the difference between two sequences. It is calculated as the minimum number of single-character edits (insertions, deletions, or substitutions) required to change one word into the other. This measure has various applications in computer science and information theory, such as spell checking, DNA and protein sequence analysis, and natural language processing.

## Implementation

The provided C++ program calculates the Levenshtein distance between two strings using dynamic programming. The algorithm fills a matrix where the entry at `mat[i][j]` contains the Levenshtein distance between the first `i` characters of string `seq_a` and the first `j` characters of string `seq_b`. Additionally, the program keeps track of the operations (insertions, deletions, substitutions) that lead to the minimal distance to be able to reconstruct the sequence of edits.

### Algorithm

The algorithm operates as follows:

1. Initialize a matrix `mat` with dimensions `(len_a+1) x (len_b+1)`, where `len_a` is the length of `seq_a` and `len_b` is the length of `seq_b`.
2. Fill the first row and column of `mat` with indices `0` to `len_a` and `0` to `len_b`, respectively. These represent the distances from the empty string.
3. Iteratively fill in the matrix using the recurrence relation that considers the cost of deletions, insertions, and substitutions to find the minimum cost at each step.
4. Maintain an operations matrix `ops` that stores the operation leading to the minimum cost at each cell.
5. After the matrix is filled, backtrack from `mat[len_a][len_b]` to `mat[0][0]` to determine the sequence of operations that leads to the Levenshtein distance.
6. Output the sequence of operations alongside their descriptions.

### Debug Function

A debug function `debug` is provided to print the matrix `mat` for visualization of the dynamic programming process.

### Backtracking for Operations

The backtracking logic reconstructs the sequence of operations (insert, delete, substitute) needed to transform `seq_a` into `seq_b`. During backtracking, operations are printed to the console with their descriptions, indicating the type of operation, the character involved, and its position in the original string.

## Compilation

Compile the program with a C++ compiler supporting C++17 or later, as `std::string_view` is used.

```sh
> clang++ -std=c++17 -o levenshtein main.cpp
```

### Output

```sh
> ./levenshtein
Sequence 1: AGGCT
Sequence 2: AGCA
\ - A G C A
- 0 1 2 3 4
A 1 0 1 2 3
G 2 1 0 1 2
G 3 2 1 1 2
C 4 3 2 1 2
T 5 4 3 2 2
SUBSTITUTE: 5-th base T of AGGCT with A
DELETE:     3-th base G of AGGCT
Levenshtein Distance: 2
```
