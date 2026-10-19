#include "day3.hpp"
#include <stdexcept>

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

int solve(const size_t n) {
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

} // namespace Day3
