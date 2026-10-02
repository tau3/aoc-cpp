#include "day19.hpp"
#include <cstddef>
#include <deque>

namespace Day19 {

using namespace std;

size_t solve_pt1(const size_t count) {
  deque<size_t> q;
  for (size_t i = 1; i <= count; i++) {
    q.push_back(i);
  }

  while (q.size() != 1) {
    const size_t left = q.front();
    q.pop_front();

    q.pop_front();

    q.push_back(left);
  }

  return q.front();
}

size_t solve_pt2(const size_t count) {
  deque<size_t> q;
  for (size_t i = 1; i <= count; i++) {
    q.push_back(i);
  }

  while (q.size() != 1) {
    const size_t current = q.front();
    const size_t size = q.size();

    q.pop_front();

    q.erase(q.begin() + (size / 2 - 1));

    q.push_back(current);
  }

  return q.front();
}

} // namespace Day19
