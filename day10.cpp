#include <cstddef>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "day10.hpp"

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

inline ostream &operator<<(ostream &os, const Direction &direction) {
  switch (direction) {
  case Direction::UP:
    os << "Direction::UP";
    break;
  case Direction::DOWN:
    os << "Direction::DOWN";
    break;
  case Direction::LEFT:
    os << "Direction::LEFT";
    break;
  case Direction::RIGHT:
    os << "Direction::RIGHT";
    break;
  default:
    throw invalid_argument("direction");
  }
  return os;
}

struct Point {
  size_t row;
  size_t col;

  explicit Point(size_t row, size_t col) : row(row), col(col) {}

  void move(const Direction direction) {
    switch (direction) {
    case Direction::UP:
      row--;
      break;
    case Direction::DOWN:
      row++;
      break;
    case Direction::LEFT:
      col--;
      break;
    case Direction::RIGHT:
      col++;
      break;
    default:
      throw invalid_argument("direction");
    }
  }
};

inline bool operator!=(const Point &lhs, const Point &rhs) {
  return (lhs.col != rhs.col) || (lhs.row != rhs.row);
}

inline ostream &operator<<(ostream &os, const Point &point) {
  os << "Point{row=" << point.row << ";col=" << point.col << "}";
  return os;
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

Direction pick_direction(const vector<string> &grid, const Point &current,
                         const Direction direction) {
  const char current_value = grid[current.row][current.col];
  switch (current_value) {
  case 'L':
    if (direction == Direction::LEFT) {
      return Direction::UP;
    } else if (direction == Direction::DOWN) {
      return Direction::RIGHT;
    }
    throw invalid_argument("L direction");
  case 'J':
    if (direction == Direction::RIGHT) {
      return Direction::UP;
    } else if (direction == Direction::DOWN) {
      return Direction::LEFT;
    }
    throw invalid_argument("J direction");
  case '7':
    if (direction == Direction::RIGHT) {
      return Direction::DOWN;
    } else if (direction == Direction::UP) {
      return Direction::LEFT;
    }
    throw invalid_argument("7 direction");
  case 'F':
    if (direction == Direction::UP) {
      return Direction::RIGHT;
    } else if (direction == Direction::LEFT) {
      return Direction::DOWN;
    }
    throw invalid_argument("F direction");
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
    direction = pick_direction(grid, current, direction);
  }

  return steps / 2;
}

void replace_all(string &orig, string substring, string replacement) {
  size_t pos = orig.find(substring);
  while (pos != string::npos) {
    orig.replace(pos, substring.size(), replacement);
    pos = orig.find(substring, pos + replacement.size());
  }
}

size_t count(const string &str, char symbol) {
  size_t result = 0;
  for (char c : str) {
    if (c == symbol) {
      ++result;
    }
  }
  return result;
}

bool contains(const set<Point> &points, const Point &point) {
  return points.find(point) != points.end();
}

bool inside(const vector<string> &grid, const set<Point> &loop,
            const Point &point, const Point &start) {
  // TODO may be wrong
  string line;
  const size_t from = (point.col < start.col) ? 0 : point.col + 1;
  const size_t to = (point.col < start.col) ? point.col : grid[0].size();
  for (size_t i = from; i < to; ++i) {
    const Point current = Point(point.row, i);
    const char value = grid[current.row][current.col];
    if ((contains(loop, current)) && (value != '.') && (value != '-')) {
      line += value;
    }
  }

  replace_all(line, "F7", "");
  replace_all(line, "LJ", "");
  replace_all(line, "FJ", "|");
  replace_all(line, "L7", "|");

  return count(line, '|') % 2 == 1;
}

int foo(const vector<string> &grid) {
  queue<Point> dots;
  for (size_t row = 0; row < grid.size(); ++row) {
    for (size_t col = 0; col < grid[0].size(); ++col) {
      if (grid[row][col] == '.') {
        dots.push(Point(row, col));
      }
    }
  }

  int result = 0;
  while (!dots.empty()) {
    Point point = dots.front();
    dots.pop();

    set<Point> visited;
    queue<Point> neighbours;
    neighbours.push(point);

    while (!neighbours.empty()) {
      point = neighbours.front();
      neighbours.pop();
      if (contains(visited, point)) {
        continue;
      }
      const vector<Point> adjacent = point.adjacent();
      neighbours.add_all(adjacent);
    }

    if (inside(grid, loop, point, start)) {
      result += neighbours.size();
    }

    dots.remove_all(neighbours);
  }
  return result;
}

void solve_pt2(const vector<string> &grid) {
  for (const string &line : grid) {
    bool inside = false;
    for (const char c : line) {
    }
  }
}
