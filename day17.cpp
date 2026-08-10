#include "day17.hpp"
#include <cmath>
#include <string>

namespace Day17 {

bool test_bit(const int num, const int i) {
  int mask = 1 << i;
  return num & mask;
}

int how_many_ways(const vector<int> &containers, int limit) {
  int counter = pow(2, containers.size());
  int result = 0;
  for (int i = 1; i < counter; i++) {
    int sum = 0;
    for (int j = 0; j < containers.size(); j++) {
      if (test_bit(i, j)) {
        sum += containers[j];
      }
    }
    if (sum == limit) {
      result++;
    }
  }
  return result;
}

int solve_day17_pt1(const vector<string> &input) {
  vector<int> containers;
  for (const auto &line : input) {
    containers.push_back(stoi(line));
  }
  return how_many_ways(containers, 150);
}

} // namespace Day17
