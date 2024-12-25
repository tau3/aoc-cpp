#include "day15.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

namespace Day15 {

struct Point {
  size_t r;
  size_t c;

  Point next(const char direction) const {
    assert(r > 0);
    assert(c > 0);
    switch (direction) {
    case '^':
      return {r - 1, c};
    case '>':
      return {r, c + 1};
    case 'v':
      return {r + 1, c};
    case '<':
      return {r, c - 1};
    default:
      throw "invalid direction " + to_string(direction);
    }
  }
};

void append(vector<Point> &lhs, const vector<Point> &rhs) {
  lhs.insert(lhs.end(), rhs.begin(), rhs.end());
}

class Grid {
  vector<string> grid;
  Point robot;

  Grid();

  char at(const Point &point) const { return grid[point.r][point.c]; }

  char &at(const Point &point) { return grid[point.r][point.c]; }

  void move(const char direction) {
    const auto next_position = robot.next(direction);
    if (at(next_position) == '#') {
      return;
    }

    if (at(next_position) == '.') {
      at(robot) = '.';
      robot = next_position;
      at(next_position) = '@';
      return;
    }

    vector<Point> shifted_boxes;
    Point current = next_position;
    while (at(current) == 'O') {
      shifted_boxes.push_back(current);
      current = current.next(direction);
    }
    if (at(current) == '.') {
      for (auto it = shifted_boxes.rbegin(); it != shifted_boxes.rend(); ++it) {
        at(it->next(direction)) = 'O';
      }

      at(robot) = '.';
      robot = next_position;
      at(next_position) = '@';
    }
  }

  vector<Point> asd(const Point &box, const char direction) {
    assert(at(box) == '[');

    switch (direction) {
    case '<': {
      const Point next_box = box.next(direction).next(direction);
      if (at(next_box) != '[') {
        return {box};
      } else {
        vector<Point> result = {box};
        append(result, asd(next_box, direction));
        return result;
      }
      break;
    }
    case '>': {
      const Point next_box = box.next(direction).next(direction);
      if (at(next_box) != ']') {
        return {box};
      } else {
        vector<Point> result = {box};
        append(result, asd(next_box, direction));
        return result;
      }
      break;
    }
    case 'v':
    case '^': {
      const Point next = box.next(direction);
      vector<Point> result = {box};
      if (at(next) == '[') {
        append(result, asd(next, direction));
        return result;
      } else if (at(next) == ']') {
        const Point vertical_left = next.next('<');
        append(result, asd(vertical_left, direction));
        const Point vertical_right = next.next('>');
        if (at(vertical_right) == '[') {
          append(result, asd(vertical_right, direction));
        }
        return result;
      }
      break;
    }
    default:
      throw "unknown direction: " + to_string(direction);
    }
    throw "unreachable";
  }

  void chain(const char direction) { Point current = robot.next(direction); }

  void move_scaled(const char direction) {
    const auto next_position = robot.next(direction);
    if (at(next_position) == '#') {
      return;
    }

    if (at(next_position) == '.') {
      at(robot) = '.';
      robot = next_position;
      at(next_position) = '@';
      return;
    }

    //   vector<Point> shifted_boxes;
    //   Point current = next_position;
    //   while (at(current) == 'O') {
    //     shifted_boxes.push_back(current);
    //     current = current.next(direction);
    //   }
    //   if (at(current) == '.') {
    //     for (auto it = shifted_boxes.rbegin(); it != shifted_boxes.rend();
    //     ++it) {
    //       at(it->next(direction)) = 'O';
    //     }

    //     at(robot) = '.';
    //     robot = next_position;
    //     at(next_position) = '@';
    //   }
  }

public:
  explicit Grid(const vector<string> grid) : grid(grid) {
    for (size_t r = 0; r < grid.size(); ++r) {
      for (size_t c = 0; c < grid[0].size(); ++c) {
        if (grid[r][c] == '@') {
          robot = {r, c};
          return;
        }
      }
    }
    throw "no robot";
  }

  void simulate(const vector<string> &moves) {
    for (const string &line : moves) {
      for (const char direction : line) {
        move(direction);
      }
    }
  }

  int sum_gps() const {
    int result = 0;
    for (size_t r = 0; r < grid.size(); ++r) {
      for (size_t c = 0; c < grid[0].size(); ++c) {
        if (grid[r][c] == 'O') {
          int gps = 100 * r + c;
          result += gps;
        }
      }
    }
    return result;
  }

  int sum_scaled_gps() const {
    int result = 0;
    const size_t height = grid.size();
    const size_t width = grid[0].size();
    for (size_t r = 0; r < height; ++r) {
      for (size_t c = 0; c < width; ++c) {
        if (grid[r][c] == '[') {
          size_t left = r;
          size_t top = c;
          size_t right = width - left - 2;
          assert(right < width);
          size_t bottom = height - top - 2;
          assert(bottom < height);
          int gps = 100 * min(top, bottom) + min(left, right);
          result += gps;
        }
      }
    }
    return result;
  }
};

int solve_day15_pt1(const vector<string> &input) {
  vector<string> grid_data;
  vector<string> moves;

  bool is_grid = true;
  for (const string &line : input) {
    if (line.empty()) {
      is_grid = false;
      continue;
    }

    if (is_grid) {
      grid_data.push_back(line);
    } else {
      moves.push_back(line);
    }
  }

  Grid grid(grid_data);
  grid.simulate(moves);
  return grid.sum_gps();
}

vector<string> scale(const vector<string> &grid) {
  vector<string> result;
  for (const string &line : grid) {
    string scaled;
    for (const char c : line) {
      switch (c) {
      case '#':
        scaled += "##";
        break;
      case 'O':
        scaled += "[]";
        break;
      case '.':
        scaled += "..";
        break;
      case '@':
        scaled += "@.";
        break;
      default:
        throw "unknown tile: " + to_string(c);
      }
    }
    result.push_back(scaled);
  }
  return result;
}

} // namespace Day15
