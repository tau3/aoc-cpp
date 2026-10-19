#ifndef INCLUDE_DAY_3_H
#define INCLUDE_DAY_3_H

#include <cstddef>

namespace Day3 {

using namespace std;

class Generator {
private:
  char direction = 'e';
  size_t c = 1;
  bool twice = false;
  size_t i = 0;

  char next_direction() const;

public:
  char next();
};

int solve(const size_t n);

} // namespace Day3

#endif
