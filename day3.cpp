#include "day3.hpp"
#include <iostream>
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
  // cout << "dir=" << direction << "; c=" << c << "; tw=" << twice << "; i=" << i
       // << endl;

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
  return direction;
}

} // namespace Day3
