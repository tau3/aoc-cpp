#include "day3.hpp"
#include "util.hpp"
#include <array>
#include <cstddef>
#include <stdexcept>
#include <unordered_map>

namespace Day3 {

using namespace std;

char Generator::next_direction() const {
  switch (direction) {
  case 'e':
    return 'n';
  case 'n':
    return 'w';
  case 'w':
    return 's';
  case 's':
    return 'e';
  default:
    throw runtime_error("invalid direction");
  }
}

char Generator::next() {
  char result = direction;
  i++;
  if (i == c) {
    if (twice) {
      direction = next_direction();
      c++;
      twice = false;
      i = 0;
    } else {
      direction = next_direction();
      twice = true;
      i = 0;
    }
  }
  return result;
}

int solve_pt1(const size_t n) {
  Generator generator;

  int x = 0;
  int y = 0;

  for (size_t i = 1; i < n; i++) {
    const char direction = generator.next();
    switch (direction) {
    case 'e':
      x++;
      break;
    case 'n':
      y++;
      break;
    case 'w':
      x--;
      break;
    case 's':
      y--;
      break;
    default:
      throw runtime_error("unknown direction");
    }
  }

  return abs(x) + abs(y);
}

using Point = util::Point<int>;

int solve_pt2(const int n) {
  Generator generator;

  Point current{0, 0};

  unordered_map<Point, int, util::PointHash> point_to_value;
  point_to_value.insert({current, 1});

  while (point_to_value.at(current) <= n) {
    const char direction = generator.next();
    switch (direction) {
    case 'e':
      current = current.right();
      break;
    case 'n':
      current = current.down();
      break;
    case 'w':
      current = current.left();
      break;
    case 's':
      current = current.up();
      break;
    default:
      throw runtime_error("unknown direction");
    }

    int sum = 0;
    const array<Point, 8> adjacent = util::get_adjacent(current);
    for (const Point &point : adjacent) {
      const auto &entry = point_to_value.find(point);
      if (entry != point_to_value.end()) {
        sum += entry->second;
      }
    }
    point_to_value.insert({current, sum});
  }

  return point_to_value.at(current);
}

} // namespace Day3
