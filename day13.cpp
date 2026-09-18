#include "day13.hpp"
#include "util.hpp"
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Day13 {

using namespace std;

int count_bits(size_t n) {
  size_t count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

bool is_open(const size_t x, const size_t y, const size_t favorite_number) {
  size_t z = x * x + 3 * x + 2 * x * y + y + y * y;
  z += favorite_number;

  const int bits = count_bits(z);
  return bits % 2 == 0;
}

using Pos = util::Point<size_t>;
using Cell = pair<Pos, bool>;

vector<Cell> calc_adjacent(const size_t x, const size_t y,
                           const size_t favorite_number) {
  vector<Cell> result;

  result.push_back({Pos{x + 1, y}, is_open(x + 1, y, favorite_number)});
  result.push_back({Pos{x, y + 1}, is_open(x, y + 1, favorite_number)});
  if (x > 0) {
    result.push_back({Pos{x - 1, y}, is_open(x - 1, y, favorite_number)});
  }
  if (y > 0) {
    result.push_back({Pos{x, y - 1}, is_open(x, y - 1, favorite_number)});
  }
  return result;
}

size_t solve_pt1(const size_t favorite_number) {
  queue<pair<Pos, size_t>> q;
  q.push({Pos{1, 1}, 0});

  const Pos target{7, 4};
  unordered_set<Pos, util::PointHash> visited;
  while (!q.empty()) {
    const auto [pos, dist] = q.front();
    const auto &[x, y] = pos;
    q.pop();

    visited.insert(pos);
    const vector<Cell> adjacent = calc_adjacent(x, y, favorite_number);
    for (const Cell &cell : adjacent) {
      if (cell.first == target) {
        return dist + 1;
      }

      if (cell.second && !util::contains(visited, pos)) {
        q.push({cell.first, dist + 1});
      }
    }
  }
  throw runtime_error("no solution");
}

} // namespace Day13
