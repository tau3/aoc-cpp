#include <cstddef>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "day10.hpp"

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
  size_t row;
  size_t col;

  explicit Point(size_t row, size_t col) : row(row), col(col) {}

  void move(const Direction direction) {
    switch (direction) {
    case Direction::UP:
      col--;
      break;
    case Direction::DOWN:
      col++;
      break;
    case Direction::LEFT:
      row--;
      break;
    case Direction::RIGHT:
      row++;
      break;
    default:
      throw invalid_argument("direction");
    }
  }
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

Direction direction_for_start(const vector<string> &grid, const Point &start) {
  const size_t row = start.row;
  const size_t col = start.col;
  const size_t height = grid.size();
  const size_t width = grid[0].size();

  if ((col > 0) && contains("FL-", grid[row][col - 1])) {
    return Direction::LEFT;
  }
  if ((row > 0) && contains("F7|", grid[row - 1][col])) {
    return Direction::UP;
  }
  if ((row < height - 1) && contains("|JL", grid[row + 1][col])) {
    return Direction::DOWN;
  }
  if ((col < width - 1) && contains("-J7", grid[row][col + 1])) {
    return Direction::RIGHT;
  }
  throw invalid_argument("start");
}

Direction foo(const vector<string> &grid, const Point &current,
              const Direction direction) {
  char current_value = grid[current.col][current.row];
  switch (current_value) {
  case 'L':
    if (direction == Direction::LEFT) {
      return Direction::UP;
    } else if (direction == Direction::DOWN) {
      return Direction::RIGHT;
    } else {
      throw invalid_argument("L direction");
    }
    break;
  case 'J':
    if (direction == Direction::RIGHT) {
      return Direction::UP;
    } else if (direction == Direction::DOWN) {
      return Direction::LEFT;
    } else {
      throw invalid_argument("J direction");
    }
    break;
  case '7':
    if (direction == Direction::RIGHT) {
      return Direction::DOWN;
    } else if (direction == Direction::UP) {
      return Direction::LEFT;
    } else {
      throw invalid_argument("7 direction");
    }
    break;
  case 'F':
    if (direction == Direction::UP) {
      return Direction::RIGHT;
    } else if (direction == Direction::LEFT) {
      return Direction::DOWN;
    } else {
      throw invalid_argument("F direction");
    }
    break;
  }
  return direction;
}

int solve_pt1(const vector<string> &grid) {
  const Point start = find_start(grid);
  Point current = start;
  int steps = 0;
  Direction direction = direction_for_start(grid, start);

  while ((current != start) || (steps == 0)) {
    current.move(direction);
    ++steps;
    direction = foo(grid, current, direction);
  }

  return steps / 2;
}
