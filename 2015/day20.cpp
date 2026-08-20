#include "day20.hpp"
#include <cmath>
#include <future>
#include <vector>

namespace Day20 {

using namespace std;

const int THREADS = 10;

int calc_presents(const int house_number) {
  int result = 1 + house_number;
  for (int i = 2; i <= sqrt(house_number); i++) {
    if (house_number % i == 0) {
      result += i;
    }
  }
  return result * 10;
}

int calc_block(const int from_inclusive, const int block_size,
               const int presents) {
  for (int i = from_inclusive; i < from_inclusive + block_size; i++) {
    const int current = calc_presents(i);
    if (current >= presents) {
      return i;
    }
  }
  return -1;
}

int solve_day20_pt1(const int presents) {
  const int block_size = presents / THREADS;

  vector<future<int>> futures;
  for (int i = 0; i < THREADS; i++) {
    future<int> future =
        async(calc_block, i * block_size, block_size, presents);
    futures.push_back(std::move(future));
  }

  int result = presents;
  for (future<int> &future : futures) {
    const int current = future.get();
    if (current != -1 && current < result) {
      result = current;
    }
  }
  return result;
}

} // namespace Day20
