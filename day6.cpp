#include "string"
#include "vector"
#include <cstddef>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

namespace Day6 {
using Position = tuple<int, int>;

struct Guard {
  Position position;
  char direction;

  void turn_right() {
    switch (direction) {
    case 'N':
      direction = 'E';
      break;
    case 'E':
      direction = 'S';
      break;
    case 'S':
      direction = 'W';
      break;
    case 'W':
      direction = 'N';
      break;
    default:
      throw "unknown direction";
    }
  }
};

bool is_oob(const Position &posititon, const vector<string> &grid) {
  const auto [r, c] = posititon;
  const size_t w = grid[0].size();
  const size_t h = grid.size();
  return (r < 0) || (c < 0) || (r >= h) || (c >= w);
}

Position get_current_position(const vector<string> &grid) {
  const size_t h = grid.size();
  const size_t w = grid[0].size();
  for (size_t r = 0; r < h; ++r) {
    for (size_t c = 0; c < w; ++c) {
      if (grid[r][c] == '^') {
        return {r, c};
      }
    }
  }
  throw "no start found";
}

bool step(const vector<string> &grid, Guard &guard) {
  const auto [current_row, current_column] = guard.position;
  Position next;
  switch (guard.direction) {
  case 'N':
    next = {current_row - 1, current_column};
    break;
  case 'E':
    next = {current_row, current_column + 1};
    break;
  case 'S':
    next = {current_row + 1, current_column};
    break;
  case 'W':
    next = {current_row, current_column - 1};
    break;
  default:
    throw "unknown direction";
  }

  if (is_oob(next, grid)) {
    return true;
  }

  const auto [next_row, next_column] = next;
  if (grid[next_row][next_column] == '#') {
    guard.turn_right();
    return false;
  }

  guard.position = next;
  return false;
}

int solve_day6_pt1(const vector<string> &grid) {
  Position current = get_current_position(grid);
  Guard guard = {current, 'N'};
  unordered_set<Position> result;
  result.insert(current);
  while (!step(grid, guard)) {
    result.insert(guard.position);
  }

  return result.size();
}

} // namespace Day6
