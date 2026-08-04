#include "util.hpp"
#include <string>
#include <unordered_map>
#include <vector>

using Index =
    std::unordered_map<std::string, std::unordered_map<std::string, int>>;

int calc_total(const std::vector<std::string> &permutation, const Index &index);

int solve(const std::vector<std::string> &input) {
  Index index;
  for (const std::string &line : input) {
    const std::vector<std::string> tokens = util::split(line, " ");
    const std::string from = tokens[0];

    std::string to = tokens[10];
    to.pop_back();

    int points = std::stoi(tokens[3]);
    if (tokens[2] == "lose") {
      points *= -1;
    }

    if (index.find(from) != index.end()) {
      index[from][to] = points;
    } else {
      index[from] = {{to, points}};
    }
  }

  const std::vector<std::vector<std::string>> permutations =
      make_permutations(index.key_set());
  int result = 0;
  for (const std::vector<std::string> &permutation : permutations) {
    result = std::max(result, calc_total(permutation, index));
  }
  return result;
}

int calc_total(const std::vector<std::string> &permutation,
               const Index &index) {
  int result = 0;
  const size_t size = permutation.size();
  const size_t last = size - 1;
  for (int i = 0; i < size; i++) {
    size_t left_ix;
    size_t right_ix;
    switch (i) {
    case 0:
      left_ix = last;
      right_ix = 1;
      break;
    case last:
      left_ix = last - 1;
      right_ix = 0;
      break;
    default:
      left_ix = i - 1;
      right_ix = i + 1;
    }

    const std::string &current = permutation[i];
    const std::string &left = permutation[left];
    const std::string &right = permutation[right];
    result += index[current][left];
    result += index[current][right];
  }

  return result;
}
