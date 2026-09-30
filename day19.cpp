#include "day19.hpp"
#include <deque>

namespace Day19 {

using namespace std;

size_t solve(const size_t count) {
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

} // namespace Day19
