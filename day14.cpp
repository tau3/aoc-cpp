<<<<<<< HEAD
#include "day14.hpp"
#include "util.hpp"
#include <unordered_set>
#include <vector>

namespace Day14 {

Point point_from_string(const string &raw) {
  const auto tokens = split(raw, ",");
  return {stoi(tokens[0]), stoi(tokens[1])};
}

bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

using Grid = Point;

void Robot::move(const Grid &grid) {
  const auto [width, height] = grid;

  int x = position.x + velocity.x;
  if (x >= width) {
    x -= width;
  } else if (x < 0) {
    x = width + x;
  }

  int y = position.y + velocity.y;
  if (y >= height) {
    y -= height;
  } else if (y < 0) {
    y = height + y;
  }

  position = {x, y};
}

int Robot::quadrant(const Grid &grid) const {
  const int vertical = grid.x / 2;
  if (position.x == vertical) {
    return -1;
  }

  const int horizontal = grid.y / 2;
  if (position.y == horizontal) {
    return -1;
  }

  const bool is_left = position.x < vertical;
  const bool is_top = position.y < horizontal;

  if (is_left) {
    return is_top ? 1 : 4;
  } else {
    return is_top ? 2 : 3;
  }
}

Robot robot_from_string(const string &input) {
  const vector<string> tokens = split(input, " ");

  string position = tokens[0];
  string velocity = tokens[1];

  position = position.substr(2);
  velocity = velocity.substr(2);

  return {point_from_string(position), point_from_string(velocity)};
}

int solve(vector<Robot> &robots, const Grid &grid) {
  for (int i = 0; i < 100; ++i) {
    for (Robot &robot : robots) {
      robot.move(grid);
    }
  }

  int counts[4] = {0};
  for (const Robot &robot : robots) {
    const int quadrant = robot.quadrant(grid);
    if (quadrant >= 0) {
      ++counts[quadrant - 1];
    }
  }

  return counts[0] * counts[1] * counts[2] * counts[3];
}

int solve_raw_input(const vector<string> &input, const Grid &grid) {
  vector<Robot> robots;
  for (const string &line : input) {
    robots.push_back(robot_from_string(line));
  }

  return solve(robots, grid);
}

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

int solve_pt2(const vector<string> &input, const Grid &grid) {
  vector<Robot> robots;
  for (const string &line : input) {
    robots.push_back(robot_from_string(line));
  }

  int i = 0;
  while (true) {
    unordered_set<Point, PointHash> positions;
    bool no_duplicates = true;
    for (Robot &robot : robots) {
      robot.move(grid);
      if (no_duplicates) {
        const auto [_, is_new_element] = positions.insert(robot.position);
        if (!is_new_element) {
          no_duplicates = false;
        }
      }
    }
    if (no_duplicates) {
      return i + 1;
    }
    ++i;
  }
}

} // namespace Day14
=======
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

int total_load(const vector<string> &grid) {
  int result = 0;
  for (size_t row = 0; row < grid.size(); ++row) {
    for (char cell : grid[row]) {
      if (cell == 'O') {
        result += (grid.size() - row);
      }
    }
  }
  return result;
}

void move_point(vector<string> &grid, size_t row, size_t column) {
  if (row == 0) {
    return;
  }

  if (grid[row - 1][column] == '.') {
    grid[row - 1][column] = 'O';
    grid[row][column] = '.';
    move_point(grid, row - 1, column);
  }
}

int solve_day14_pt1(vector<string> &grid) {
  for (size_t row = 0; row < grid.size(); ++row) {
    for (size_t column = 0; column < grid[0].size(); ++column) {
      if (grid[row][column] == 'O') {
        move_point(grid, row, column);
      }
    }
  }

  return total_load(grid);
}
>>>>>>> 1807ec9 (initial day14pt1)
