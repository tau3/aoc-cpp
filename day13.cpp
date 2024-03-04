#include "day13.hpp"
#include "util.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

struct Solution {
  size_t rows;
  size_t columns;
};

bool equal_cols(const vector<string> &input, size_t left, size_t right) {
  for (const string &line : input) {
    if (line[left] != line[right]) {
      return false;
    }
  }
  return true;
}

bool is_horizontal_border(const vector<string> &input, size_t lower) {
  int down = lower + 1;
  int up = lower - 2;
  while ((up >= 0) && (down < input.size())) {
    if (input[up] != input[down]) {
      return false;
    }
    up--;
    down++;
  }
  return true;
}

bool is_vertical_border(const vector<string> &input, size_t right) {
  int east = right + 1;
  int west = right - 2;
  while ((west >= 0) && (east < input[0].size())) {
    if (!equal_cols(input, west, east)) {
      return false;
    }
    west--;
    east++;
  }
  return true;
}

Solution solve_pattern(const vector<string> &input) {
  for (size_t i = 1; i < input.size(); ++i) {
    if (input[i] == input[i - 1]) {
      if (is_horizontal_border(input, i)) {
        return Solution{i, 0};
      }
    }
  }

  for (size_t i = 0; i < input[0].size(); ++i) {
    if (equal_cols(input, i, i - 1)) {
      if (is_vertical_border(input, i)) {
        return Solution{0, i};
      }
    }
  }

  throw invalid_argument("no solution");
}

size_t count_diffs(const vector<string> &pattern, bool is_row, size_t i,
                   size_t j) {
  if (is_row) {
    const string &left = pattern[i];
    const string &right = pattern[j];
    size_t result = 0;
    for (size_t k = 0; k < left.size(); ++k) {
      if (left[k] != right[k]) {
        result++;
      }
    }
    return result;
  }

  size_t result = 0;
  for (size_t k = 0; k < pattern.size(); ++k) {
    if (pattern[k][i] != pattern[k][j]) {
      result++;
    }
  }
  return result;
}

void set_column(vector<string> &input, size_t i, size_t j) {
  for (string &line : input) {
    line[i] = line[j];
  }
}

bool other_is_symmetrical(const vector<string> &pattern, bool is_row, int i,
                          int j) {
  if (is_row) {
    for (int k = -pattern.size(); k < pattern.size(); ++k) {
      int di = i + k;
      int dj = j - k;
      if ((di < 0) || (dj < 0) || (dj > (pattern.size() - 1)) ||
          (di > (pattern.size() - 1))) {
        continue;
      }
      if (pattern[di] != pattern[dj]) {
        return false;
      }
    }
    return true;
  }

  for (int k = -pattern[0].size(); k < pattern[0].size(); ++k) {
    int di = i + k;
    int dj = i - k;
    if ((di < 0) || (dj < 0) || (dj > (pattern[0].size() - 1)) ||
        (di > (pattern[0].size() - 1))) {
      continue;
    }
    if (!equal_cols(pattern, di, dj)) {
      return false;
    }
  }
  return true;
}

void place_smudge(vector<string> &input) {
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = i + 1; j < input.size(); ++j) {
      if (count_diffs(input, true, i, j) == 1) {
        if (other_is_symmetrical(input, true, i, j)) {
          input[i] = input[j];
          return;
        }
      }
    }
  }

  for (size_t i = 0; i < input[0].size(); ++i) {
    for (size_t j = i + 1; j < input[0].size(); ++j) {
      if (count_diffs(input, false, i, j) == 1) {
        if (other_is_symmetrical(input, false, i, j)) {
          set_column(input, i, j);
          return;
        }
      }
    }
  }
  throw invalid_argument("no smudge found");
}

int traverse(const vector<string> &input, void (*func)(vector<string> &)) {
  size_t start = 0;
  size_t current = 0;
  size_t columns = 0;
  size_t rows = 0;
  while (current < input.size()) {
    current++;
    if (!input[current].empty()) {
      continue;
    }
    vector<string> slice =
        vector<string>(input.begin() + start, input.begin() + current);
    func(slice);
    const Solution solution = solve_pattern(slice);
    columns += solution.columns;
    rows += solution.rows;
    start = current + 1;
  }
  if (start < current) {
    vector<string> slice =
        vector<string>(input.begin() + start, input.begin() + current);
    func(slice);
    const Solution solution = solve_pattern(slice);
    columns += solution.columns;
    rows += solution.rows;
  }
  return columns + 100 * rows;
}

int solve_day13_pt1(const vector<string> &input) {
  return traverse(input, [](auto) -> void {});
}

int solve_day13_pt2(const vector<string> &input) {
  return traverse(input, place_smudge);
}
