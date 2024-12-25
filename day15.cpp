#include <cstddef>
#include <string>
#include <vector>

using namespace std;

struct Point {
  int r;
  int c;

  Point next(const char direction) {
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

class Grid {
  vector<string> grid;
  Point robot;

  Grid();

public:
  explicit Grid(const vector<string> grid) : grid(grid) {
    for (size_t r = 0; r < grid.size(); ++r) {
      for (size_t c = 0; c < grid[0].size(); ++c) {
        if (grid[r][c] == '@') {
	  robot = {(int)r, (int)c};
          return;
        }
      }
    }
    throw "no robot";
  }

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
    if (at(current.next(direction)) == '.') {
      for (auto it = shifted_boxes.rbegin(); it != shifted_boxes.rend(); ++it) {
        at(it->next(direction)) = 'O';
      }

      at(robot) = '.';
      robot = next_position;
      at(next_position) = '@';
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
};

void simulate(Grid &grid, const vector<string> &moves) {
  for (const string &line : moves) {
    for (const char direction : line) {
      grid.move(direction);
    }
  }
}

int solve(const vector<string> &input) {
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
  simulate(grid, moves);
  return grid.sum_gps();
}
