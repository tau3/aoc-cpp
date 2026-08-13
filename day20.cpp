#include "day20.hpp"
#include <climits>
#include <future>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <vector>

namespace Day20 {

using namespace std;

const int THREADS = 10;

std::mutex m;

int calc_presents(const int house_number) {
  int result = 1 + house_number;
  for (int i = 2; i <= house_number / 2; i++) {
    if (house_number % i == 0) {
      result += i;
    }
  }
  return result * 10;
}

int calc_block(int from_inclusive, int size, int presents) {
  for (int i = from_inclusive; i < from_inclusive + size; i++) {
    const int current = calc_presents(i);
    if (current == presents) {
      return i;
    }
  }
  return -1;
}

int solve_day20_pt1(const int presents) {
  const int block_size = INT_MAX / THREADS;

  vector<future<int>> futures;
  for (int i = 0; i < THREADS; i++) {
    std::future<int> future =
        std::async(calc_block, i * block_size, block_size, presents);
    futures.push_back(std::move(future));
  }

  for (future<int> &future : futures) {
    const int result = future.get();
    if (result != -1) {
      return result;
    }
  }
  throw runtime_error("failure");
}

} // namespace Day20
