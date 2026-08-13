#include "day20.hpp"
#include <iostream>

namespace Day20 {

int calc_presents(const int house_number) {
  int result = 1 + house_number;
  for (int i = 2; i <= house_number / 2; i++) {
    if (house_number % i == 0) {
      result += i;
    }
  }
  return result * 10;
}

int solve_day20_pt1(const int presents) {
  int i = 1000000;
  while (true) {
    const int current = calc_presents(i);
    if (current < presents) {
      i *= 2;
    } else if (current > presents) {
      i /= 2;
    }
    std::cout << i << " " << current << " " << presents << std::endl;
    i++;
  }
}

} // namespace Day20
