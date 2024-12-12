#include "day4.hpp"
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

enum class Direction { N, NE, E, SE, S, SW, W, NW };

static const Direction ALL[] = {Direction::N,  Direction::NE, Direction::E,
                                Direction::SE, Direction::S,  Direction::SW,
                                Direction::W,  Direction::NW};

using Pos = tuple<int, int>;

Pos step(const Direction &direction, const Pos &pos) {
  const auto [r, c] = pos;
  switch (direction) {
  case Direction::N:
    return {r - 1, c};
  case Direction::NE:
    return {r - 1, c + 1};
  case Direction::E:
    return {r, c + 1};
  case Direction::SE:
    return {r + 1, c + 1};
  case Direction::S:
    return {r + 1, c};
  case Direction::SW:
    return {r + 1, c - 1};
  case Direction::W:
    return {r, c - 1};
  case Direction::NW:
    return {r - 1, c - 1};
  default:
    throw "unreachable";
  }
}

bool is_in_grid(const vector<string> &grid, const Pos &pos) {
  const auto [r, c] = pos;
  const size_t w = grid[0].size();
  const size_t h = grid.size();

  return (r >= 0) && (c >= 0) && (r < h) && (c < w);
}

auto get_unsafe(const vector<string> &grid, const Pos &pos) {
  const auto [r, c] = pos;
  return grid[r][c];
}

bool check_direction(const vector<string> &grid, const Pos &pos,
                     const Direction &direction) {
  const string word = "XMAS";
  Pos current = pos;
  for (size_t i = 1; i < word.size(); ++i) {
    current = step(direction, current);
    const auto letter = word[i];
    if (!is_in_grid(grid, current)) {
      return false;
    }
    if (get_unsafe(grid, current) != letter) {
      return false;
    }
  }
  return true;
}

int count(const vector<string> &grid, const Pos &pos) {
  int result = 0;
  for (const Direction direction : ALL) {
    if (check_direction(grid, pos, direction)) {
      ++result;
    }
  }
  return result;
}

int solve_day4_pt1(const vector<string> &grid) {
  const size_t w = grid[0].size();
  const size_t h = grid.size();
  int result = 0;
  for (size_t r = 0; r < w; ++r) {
    for (size_t c = 0; c < h; ++c) {
      if (grid[r][c] == 'X') {
        result += count(grid, {r, c});
      }
    }
  }
  return result;
}

bool is_xmas(const vector<string> &grid, const Pos &pos) {
  int m = 0;
  int s = 0;
  const Direction steps[] = {Direction::NW, Direction::NE, Direction::SE,
                             Direction::SW};
  for (const Direction direction : steps) {
    const Pos target = step(direction, pos);
    if (!is_in_grid(grid, target)) {
      return false;
    }
    const auto letter = get_unsafe(grid, target);
    if (letter == 'M') {
      ++m;
    } else if (letter == 'S') {
      ++s;
    }
  }
  return (m == 2) && (s == 2);
}

int solve_day4_pt2(const vector<string> &grid) {
  const size_t w = grid[0].size();
  const size_t h = grid.size();
  int result = 0;
  for (size_t r = 0; r < w; ++r) {
    for (size_t c = 0; c < h; ++c) {
      if (grid[r][c] == 'A') {
        if (is_xmas(grid, {r, c})) {
          ++result;
        }
      }
    }
  }
  return result;
}
