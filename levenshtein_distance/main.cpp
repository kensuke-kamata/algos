#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

enum Operation {
  NONE, INSERT, DELETE, SUBSTITUTE,
};

void debug(
    const std::string_view &seq_a,
    const std::string_view &seq_b,
    const std::vector<std::vector<int>> &matrix) {
  if (matrix.empty()) { return; }

  std::cout << "\\" << " - ";
  for (auto c : seq_b) { std::cout << c << " "; }
  std::cout << std::endl;

  auto rowNum = matrix.size();
  auto colNum = matrix[0].size();

  for (auto i = 0; i < rowNum; i++) {
    // Print the first column
    if (i == 0) {
      std::cout << "- ";
    } else {
      std::cout << seq_a[i - 1] << " ";
    }

    // Print the matrix
    for (auto j = 0; j < colNum; j++) {
      std::cout << matrix[i][j] << " ";
    }

    std::cout << std::endl;
  }
}

int levenshtein_distance(const std::string &seq_a, const std::string &seq_b) {
  auto len_a = seq_a.size();
  auto len_b = seq_b.size();
  std::vector<std::vector<int>> mat(len_a + 1, std::vector<int>(len_b + 1));
  std::vector<std::vector<Operation>> ops(len_a + 1, std::vector<Operation>(len_b + 1, NONE));

  // Initialize the matrix
  for (auto i = 0; i <= len_a; i++) { mat[i][0] = i; }
  for (auto j = 0; j <= len_b; j++) { mat[0][j] = j; }

  // Calculate distances
  for (auto i = 1; i <= len_a; i++) {
    for (auto j = 1; j <= len_b; j++) {
      auto cost = (seq_a[i - 1] == seq_b[j - 1]) ? 0 : 1;

      // Pair each cost with the corresponding operation
      std::pair<int, Operation> pairs[] = {
        {mat[i - 1][j] + 1,        DELETE},
        {mat[i][j - 1] + 1,        INSERT},
        {mat[i - 1][j - 1] + cost, SUBSTITUTE}
      };

      // Find the minimum cost and operation
      auto min = pairs[0];
      for (const auto &iter : pairs) {
        if (iter.first < min.first) {
          min = iter;
        }
      }

      mat[i][j] = min.first;
      ops[i][j] = min.second;
    }
  }
  debug(seq_a, seq_b, mat);

  // Backtrack to find the edit operations
  std::vector<std::string_view> edit_ops;
  int i = len_a, j = len_b;
  while (i > 0 || j > 0) {
    auto op = ops[i][j];
    if (op == DELETE || j == 0) {
      std::cout << "DELETE:     " + std::to_string(i) + "-th base " + seq_a[i - 1] + " of " + seq_a << std::endl;
      i--;
      continue;
    }
    if (op == INSERT || i == 0) {
      std::cout << "INSERT:     " + std::to_string(j) + "-th base " + seq_b[j - 1] + " of " + seq_b << std::endl;
      j--;
      continue;
    }
    if (mat[i][j] > mat[i - 1][j - 1]) {
      std::cout << "SUBSTITUTE: " + std::to_string(i) + "-th base " + seq_a[i - 1] + " of " + seq_a + " with " + seq_b[j - 1] << std::endl;
    }
    i--; j--;
  }

  return mat[len_a][len_b];
}

int main(int, char**){
  std::string seq_a = "AGGCT";
  std::string seq_b = "AGCA";

  std::cout << "Sequence 1: " << seq_a << std::endl;
  std::cout << "Sequence 2: " << seq_b << std::endl;

  auto result = levenshtein_distance(seq_a, seq_b);
  std::cout << "Levenshtein Distance: " << result << std::endl;
  return 0;
}
