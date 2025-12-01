#include "day15.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_set>

// too borded to refactor this
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

bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.c == rhs.c) && (lhs.r == rhs.r);
}

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

void append(vector<Point> &lhs, const vector<Point> &rhs) {
  lhs.insert(lhs.end(), rhs.begin(), rhs.end());
}

vector<Point> distinct(const vector<Point> &points) {
  vector<Point> result;
  unordered_set<Point, PointHash> found;
  for (const Point &point : points) {
    const auto [_, not_seen] = found.insert(point);
    if (not_seen) {
      result.push_back(point);
    }
  }
  return result;
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

  vector<Point> build_chain(const Point &box, const char direction) const {
    assert(at(box) == '[');

    switch (direction) {
    case '<': {
      const Point next_box = box.next(direction).next(direction);
      if (at(next_box) != '[') {
        return {box};
      } else {
        vector<Point> result = {box};
        append(result, build_chain(next_box, direction));
        return result;
      }
      break;
    }
    case '>': {
      const Point next_box = box.next(direction).next(direction);
      if (at(next_box) != '[') {
        return {box};
      } else {
        vector<Point> result = {box};
        append(result, build_chain(next_box, direction));
        return result;
      }
      break;
    }
    case 'v':
    case '^': {
      const Point next = box.next(direction);
      vector<Point> result = {box};
      if (at(next) == '[') {
        append(result, build_chain(next, direction));
        return result;
      } else if (at(next) == ']') {
        const Point vertical_left = next.next('<');
        append(result, build_chain(vertical_left, direction));
        const Point vertical_right = next.next('>');
        if (at(vertical_right) == '[') {
          append(result, build_chain(vertical_right, direction));
        }
        return result;
      } else {
        return result;
      }
      break;
    }
    default:
      throw "unknown direction: " + to_string(direction);
    }
    throw "unreachable";
  }

  bool can_move_scaled_box(const Point &box, const char direction) const {
    assert(at(box) == '[');

    switch (direction) {
    case '^':
    case 'v':
      return (at(box.next(direction)) == '.') &&
             (at(box.next(direction).next('>')) == '.');
    case '<':
      return (at(box.next(direction)) == '.');
    case '>':
      return (at(box.next(direction).next(direction)) == '.');
    default:
      throw "unknown direction: " + to_string(direction);
    }
  }

  void dump(const char direction) const {
    system("clear");
    for (const string &line : grid) {
      cout << line << endl;
    }
    cout << "next move: " << char(direction) << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  void move_scaled_box(const Point &box, const char direction) {
    assert(at(box) == '[');

    switch (direction) {
    case '^':
    case 'v': {
      const Point right = box.next('>');
      const Point vertical = box.next(direction);
      assert(at(vertical) == '.');
      assert(at(right) == ']');
      assert(at(right.next(direction)) == '.');

      at(vertical) = '[';
      at(box) = '.';
      at(right) = '.';
      at(right.next(direction)) = ']';
      break;
    }
    case '<': {
      const Point horizontal = box.next(direction);
      assert(at(horizontal) == '.');
      at(horizontal) = '[';
      at(box) = ']';
      at(box.next('>')) = '.';
      break;
    }
    case '>': {
      const Point horizontal = box.next(direction).next(direction);
      assert(at(horizontal) == '.');
      at(horizontal) = ']';
      at(box.next(direction)) = '[';
      at(box) = '.';
      break;
    }
    default:
      throw "unknown direction: " + to_string(direction);
    }
  }

  Point find_closest_box_to_robot(const char direction) const {
    switch (direction) {
    case '<':
      return robot.next(direction).next(direction);
    case '>':
      return robot.next(direction);
    case 'v':
    case '^':
      return at(robot.next(direction)) == '[' ? robot.next(direction)
                                              : robot.next(direction).next('<');
    default:
      throw "unreachable";
    }
  }

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

    const Point closest_box = find_closest_box_to_robot(direction);
    vector<Point> chain = build_chain(closest_box, direction);
    reverse(chain.begin(), chain.end());
    chain = distinct(chain);

    Grid copy = Grid(grid);
    for (const Point &box : chain) {
      if (!copy.can_move_scaled_box(box, direction)) {
        return;
      }
      copy.move_scaled_box(box, direction);
    }
    grid = copy.grid;

    at(robot) = '.';
    robot = next_position;
    at(next_position) = '@';
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

  void simulate_scaled(const vector<string> &moves) {
    for (const string &line : moves) {
      for (const char direction : line) {
        move_scaled(direction);
	dump(direction);
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
          size_t left = c;
          size_t top = r;
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

int solve_day15_pt2(const vector<string> &input) {
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

  grid_data = scale(grid_data);

  Grid grid(grid_data);
  grid.simulate_scaled(moves);
  return grid.sum_scaled_gps();
}

} // namespace Day15
