#include "day14.hpp"
#include "util.hpp"

namespace Day14 {

Point point_from_string(const string &raw) {
  const auto tokens = split(raw, ",");
  return {stoi(tokens[0]), stoi(tokens[1])};
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

} // namespace Day14
