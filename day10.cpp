#include "day10.hpp"
#include <unordered_map>
#include <unordered_set>

namespace Day10 {
using Point = pair<int, int>;

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

using Points = unordered_set<Point, PointHash>;
using ScoreMemo = unordered_map<Point, Points, PointHash>;
using RatingMemo = unordered_map<Point, int, PointHash>;

char get_height(const Grid &grid, const Point &point) {
  const auto [row, column] = point;
  return grid[row][column];
}

bool is_in_bounds(const Point &point, const Grid &grid) {
  const size_t height = grid.size();
  const size_t width = grid[0].size();

  const auto [row, column] = point;

  return (row >= 0) && (column >= 0) && (row < height) && (row < width);
}

Points score(const Point &point, const Grid &grid, ScoreMemo &memo) {
  if (get_height(grid, point) == '9') {
    return {point};
  }

  const auto [r, c] = point;
  Point adjacent[] = {{r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}};
  Points result;
  for (const Point &current_point : adjacent) {
    if (!is_in_bounds(current_point, grid) ||
        ((get_height(grid, current_point) - 1) != get_height(grid, point))) {
      continue;
    }

    if (const auto &entry = memo.find(current_point); entry != memo.end()) {
      const Points& score = entry->second;
      result.insert(score.begin(), score.end());
    } else {
      const Points& current_score = score(current_point, grid, memo);
      result.insert(current_score.begin(), current_score.end());
      memo[current_point] = current_score;
    }
  }
  return result;
}

int rating(const Point &point, const Grid &grid, RatingMemo &memo) {
  if (get_height(grid, point) == '9') {
    return 1;
  }

  const auto [r, c] = point;
  Point adjacent[] = {{r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}};
  int result = 0;
  for (const Point &current_point : adjacent) {
    if (!is_in_bounds(current_point, grid) ||
        ((get_height(grid, current_point) - 1) != get_height(grid, point))) {
      continue;
    }

    if (const auto &entry = memo.find(current_point); entry != memo.end()) {
      const int score = entry->second;
      result += score;
    } else {
      int current_score = rating(current_point, grid, memo);
      result += current_score;
      memo[current_point] = current_score;
    }
  }
  return result;
}

int solve_day10_pt1(const Grid &grid) {
  const size_t height = grid.size();
  const size_t width = grid[0].size();
  ScoreMemo memo;
  int result = 0;
  for (size_t r = 0; r < height; ++r) {
    for (size_t c = 0; c < width; ++c) {
      const Point point = {r, c};
      if (get_height(grid, point) == '0') {
        const Points current = score(point, grid, memo);
        result += current.size();
      }
    }
  }

  return result;
}

int solve_day10_pt2(const Grid &grid) {
  const size_t height = grid.size();
  const size_t width = grid[0].size();
  RatingMemo memo;
  int result = 0;
  for (size_t r = 0; r < height; ++r) {
    for (size_t c = 0; c < width; ++c) {
      const Point point = {r, c};
      if (get_height(grid, point) == '0') {
        const int current = rating(point, grid, memo);
        result += current;
      }
    }
  }

  return result;
}

} // namespace Day10
