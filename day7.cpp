#include "day7.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day7 {

int solve_day7_pt1(vector<string> &input) {
  int result = 0;
  for (size_t row = 1; row < input.size(); row++) {
    for (size_t column = 1; column < input[0].size(); column++) {
      if ((row == 1) && (input[0][column] == 'S')) {
        input[row][column] = '|';
        continue;
      }

      if (input[row][column] == '^') {
        if (input[row - 1][column] == '|') {
          input[row][column - 1] = '|';
          input[row][column + 1] = '|';
          column++;
          result++;
        }
      } else if ((input[row][column] == '.') &&
                 (input[row - 1][column] == '|')) {
        input[row][column] = '|';
      }
    }
  }
  return result;
}

struct Point {
  size_t row;
  size_t col;
};

inline bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.col == rhs.col) && (lhs.row == rhs.row);
}

inline ostream &operator<<(ostream &os, const Point &point) {
  os << "Point{row=" << point.row << ";col=" << point.col << "}";
  return os;
}

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

vector<Point> find_possible_parents(const vector<string> &input,
                                    const size_t row, const size_t column) {
  vector<Point> result;
  for (int r = row - 2; r >= 0; r -= 2) {
    if ((input[r][column + 1] == '^') && (input[r - 1][column + 1] == '|')) {
      result.push_back({(size_t)r, column + 1});
    }
    if ((input[r][column - 1] == '^') && (input[r - 1][column - 1] == '|')) {
      result.push_back({(size_t)r, column - 1});
    }
    if (!result.empty()) {
      break;
    }
  }
  return result;
}

uint64_t solve_day7_pt2(vector<string> &input) {
  unordered_map<Point, uint64_t, PointHash> memo;
  for (size_t row = 1; row < input.size(); row++) {
    for (size_t column = 1; column < input[0].size(); column++) {
      if (input[row - 1][column] == 'S') {
        input[row][column] = '|';
        memo[{row + 1, column}] = 1;
        input[row + 1][column + 1] = '|';
        input[row + 1][column - 1] = '|';
        continue;
      }

      if ((input[row][column] == '^') && (input[row - 1][column] == '|')) {
        cout << "^ at " << row << " " << column << endl;
        if (memo.find({row, column}) != memo.end()) {
          continue;
        }

        const vector<Point> parents = find_possible_parents(input, row, column);
        cout << "parents for [" << row << ";" << column << "]" << endl;
        util::print(parents);
        uint64_t sum = 0;
        for (const Point &parent : parents) {
          sum += memo[parent];
        }
        memo[{row, column}] = sum;
        cout << "[" << row << ";" << column << "]=" << sum << endl;
        input[row][column - 1] = '|';
        input[row][column + 1] = '|';
      } else if ((input[row][column] == '.') &&
                 (input[row - 1][column] == '|')) {
        input[row][column] = '|';
      }
    }
  }
  util::print(input);

  uint64_t result = 0;
  for (size_t column = 0; column < input[0].size(); column++) {
    if (input[input.size() - 1][column] == '|') {
      const auto parents =
          find_possible_parents(input, input.size() - 1, column);
      for (const auto &parent : parents) {
        result += memo[parent];
      }
    }
  }

  return result;
}

} // namespace Day7
