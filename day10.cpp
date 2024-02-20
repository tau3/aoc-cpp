#include <functional>
#include <tuple>
#include <stdexcept>
#include <iostream>

#include "day10.hpp"

using namespace std;

typedef tuple<size_t, size_t> Point;

Point find_start(const vector<string> &grid) {
  for (size_t r = 0; r < grid.size(); ++r) {
    for (size_t c = 0; c < grid[0].size(); ++c) {
      if (grid[r][c] == 'S') {
        return make_tuple(r, c);
      }
    }
  }
  throw invalid_argument("grid");
}

bool contains(const string &str, char c) { return str.find(c) != string::npos; }

char direction_for_start(const vector<string> &grid, const Point &start) {
  size_t r;
  size_t c;
  tie(r, c) = start;
  size_t height = grid.size();
  size_t width = grid[0].size();

  if ((c > 0) && contains("FL-", grid[r][c - 1])) {
    return 'l';
  }
  if ((r > 0) && contains("F7|", grid[r - 1][c])) {
    return 'u';
  }
  if ((r < height - 1) && contains("|JL", grid[r + 1][c])) {
    return 'd';
  }
  if ((c < width - 1) && contains("-J7", grid[r][c + 1])) {
    return 'r';
  }
  throw invalid_argument("start");
}

int solve_pt1(const vector<string> &grid) {
  const Point start = find_start(grid);
  Point current = start;
  int steps = 0;
  char direction = direction_for_start(grid, start);

  while ((current != start) || (steps == 0)) {
    switch (direction) {
    case 'u':
      current = make_tuple(get<0>(current) - 1, get<1>(current));
      break;
    case 'd':
      current = make_tuple(get<0>(current) + 1, get<1>(current));
      break;
    case 'l':
      current = make_tuple(get<0>(current), get<1>(current) - 1);
      break;
    case 'r':
      current = make_tuple(get<0>(current), get<1>(current) + 1);
      break;
    default:
      throw invalid_argument("direction");
    }

    ++steps;

    char current_value = grid[get<0>(current)][get<1>(current)];
    switch (current_value) {
    case 'L':
      if (direction == 'l') {
        direction = 'u';
      } else if (direction == 'd') {
        direction = 'r';
      } else {
        throw invalid_argument("L direction");
      }
      break;
    case 'J':
      if (direction == 'r') {
        direction = 'u';
      } else if (direction == 'd') {
        direction = 'l';
      } else {
        throw invalid_argument("J direction");
      }
      break;
    case '7':
      if (direction == 'r') {
        direction = 'd';
      } else if (direction == 'u') {
        direction = 'l';
      } else {
        throw invalid_argument("7 direction");
      }
      break;
    case 'F':
      if (direction == 'u') {
        direction = 'r';
      } else if (direction == 'l') {
        direction = 'd';
      } else {
        throw invalid_argument("F direction");
      }
      break;
    }
  }
  return steps /2 ;
}
