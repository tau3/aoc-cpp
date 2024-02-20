#include <cstddef>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <tuple>

#include "day10.hpp"

using namespace std;

struct Point {
  size_t row;
  size_t col;

  explicit Point(size_t row, size_t col) : row(row), col(col) {}
};

inline bool operator!=(const Point &lhs, const Point &rhs) {
  return (lhs.col != rhs.col) || (lhs.row == rhs.row);
}

Point find_start(const vector<string> &grid) {
  const size_t width = grid[0].size();
  for (size_t row = 0; row < grid.size(); ++row) {
    for (size_t col = 0; col < width; ++col) {
      if (grid[row][col] == 'S') {
        return Point(row, col);
      }
    }
  }
  throw invalid_argument("grid");
}

bool contains(const string &str, const char c) {
  return str.find(c) != string::npos;
}

char direction_for_start(const vector<string> &grid, const Point &start) {
  const size_t row = start.row;
  const size_t col = start.col;
  const size_t height = grid.size();
  const size_t width = grid[0].size();

  if ((col > 0) && contains("FL-", grid[row][col - 1])) {
    return 'l';
  }
  if ((row > 0) && contains("F7|", grid[row - 1][col])) {
    return 'u';
  }
  if ((row < height - 1) && contains("|JL", grid[row + 1][col])) {
    return 'd';
  }
  if ((col < width - 1) && contains("-J7", grid[row][col + 1])) {
    return 'r';
  }
  throw invalid_argument("start");
}

int solve_pt1(const vector<string> &grid) {
  const Point start = find_start(grid);
  Point current = start;
  int steps = 0;
  char direction = direction_for_start(grid, start);

  while ((current != start) || (steps == 0)) {
    switch (direction) {
    case 'u':
      current.col--;
      break;
    case 'd':
      current.col++;
      break;
    case 'l':
      current.row--;
      break;
    case 'r':
      current.row++;
      break;
    default:
      throw invalid_argument("direction");
    }

    ++steps;

    char current_value = grid[current.col][current.row];
    switch (current_value) {
    case 'L':
      if (direction == 'l') {
        direction = 'u';
      } else if (direction == 'd') {
        direction = 'r';
      } else {
        throw invalid_argument("L direction");
      }
      break;
    case 'J':
      if (direction == 'r') {
        direction = 'u';
      } else if (direction == 'd') {
        direction = 'l';
      } else {
        throw invalid_argument("J direction");
      }
      break;
    case '7':
      if (direction == 'r') {
        direction = 'd';
      } else if (direction == 'u') {
        direction = 'l';
      } else {
        throw invalid_argument("7 direction");
      }
      break;
    case 'F':
      if (direction == 'u') {
        direction = 'r';
      } else if (direction == 'l') {
        direction = 'd';
      } else {
        throw invalid_argument("F direction");
      }
      break;
    }
  }
  return steps / 2;
}
