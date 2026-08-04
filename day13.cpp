#include "day13.hpp"
#include "util.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace Day13 {

using Index =
    std::unordered_map<std::string, std::unordered_map<std::string, int>>;

int calc_total(const std::vector<std::string> &permutation, const Index &index);

Index make_index(const std::vector<std::string> &input, const bool pt2) {
  Index index;
  if (pt2) {
    index["me"] = {};
  }

  for (const std::string &line : input) {
    const std::vector<std::string> tokens = util::split(line, " ");
    const std::string from = tokens[0];

    std::string to = tokens[10];
    to.pop_back(); // remove last dot

    int points = std::stoi(tokens[3]);
    if (tokens[2] == "lose") {
      points *= -1;
    }

    if (index.find(from) != index.end()) {
      index[from][to] = points;
    } else {
      index[from] = {{to, points}};
      if (pt2) {
        index[from]["me"] = 0;
        index["me"][from] = 0;
      }
    }
  }

  return index;
}

int solve(const std::vector<std::string> &input, const bool pt2) {
  Index index = make_index(input, pt2);

  std::vector<std::string> names;
  for (const auto &entry : index) {
    names.push_back(entry.first);
  }
  std::sort(names.begin(), names.end());

  int result = 0;
  do {
    result = std::max(result, calc_total(names, index));
  } while (std::next_permutation(names.begin(), names.end()));
  return result;
}

int solve_day13_pt1(const std::vector<std::string> &input) {
  return solve(input, false);
}

int solve_day13_pt2(const std::vector<std::string> &input) {
  return solve(input, true);
}

int calc_total(const std::vector<std::string> &permutation,
               const Index &index) {
  int result = 0;
  const size_t size = permutation.size();
  const size_t last = size - 1;
  for (int i = 0; i < size; i++) {
    size_t left_ix;
    size_t right_ix;

    if (i == 0) {
      left_ix = last;
      right_ix = 1;
    } else if (i == last) {
      left_ix = last - 1;
      right_ix = 0;
    } else {
      left_ix = i - 1;
      right_ix = i + 1;
    }

    const std::string &current = permutation[i];
    const std::string &left = permutation[left_ix];
    const std::string &right = permutation[right_ix];
    result += index.at(current).at(left);
    result += index.at(current).at(right);
  }

  return result;
}

} // namespace Day13
