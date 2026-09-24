#include "day17.hpp"
#include "day5.hpp"
#include "util.hpp"
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <format>
#include <queue>
#include <stdexcept>

namespace Day17 {

const size_t WIDTH = 4;
const size_t HEIGHT = 4;

using Doors = bitset<4>;
using Position = util::Point<size_t>;

bool is_open(const char c) {
  return (c == 'b') || (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f');
}

char direction(const size_t direction) {
  switch (direction) {
  case 0:
    return 'U';
  case 1:
    return 'D';
  case 2:
    return 'L';
  case 3:
    return 'R';
  default:
    throw runtime_error(std::format("unexpected direction {}", direction));
  }
}

// up, down, left, right
Doors calc_doors(const string &path) {
  const string md5 = Day5::md5(path);

  Doors result;
  for (size_t i = 0; i < 4; i++) {
    result[i] = is_open(md5[i]);
  }

  return result;
}

Position new_pos(const Position &position, const size_t direction) {
  switch (direction) {
  case 0:
    return position.up();
  case 1:
    return position.down();
  case 2:
    return position.left();
  case 3:
    return position.right();
  default:
    throw runtime_error(std::format("unexpected direction {}", direction));
  }
}

bool exists(const Position &position, const size_t direction) {
  switch (direction) {
  case 0:
    return position.row > 0;
  case 1:
    return position.row < HEIGHT - 1;
  case 2:
    return position.col > 0;
  case 3:
    return position.col < WIDTH - 1;
  default:
    throw runtime_error(std::format("unexpected direction {}", direction));
  }
}

string solve_pt1(const string &input) {
  const Position end{WIDTH - 1, HEIGHT - 1};

  queue<pair<Position, string>> q;
  q.push({Position{0, 0}, input});

  while (!q.empty()) {
    const auto [position, path] = q.front();
    q.pop();

    if (position == end) {
      return path.substr(input.size());
    }

    Doors doors = calc_doors(path);
    for (size_t i = 0; i < 4; i++) {
      if (doors[i] && exists(position, i)) {
        const string new_path = path + direction(i);
        const Position new_position = new_pos(position, i);
        q.push({new_position, new_path});
      }
    }
  }

  throw runtime_error("unreachable");
}

size_t solve_pt2(const string &input) {
  const Position end{WIDTH - 1, HEIGHT - 1};

  queue<pair<Position, string>> q;
  q.push({Position{0, 0}, input});

  size_t result = 0;
  while (!q.empty()) {
    const auto [position, path] = q.front();
    q.pop();

    if (position == end) {
      result = max(result, path.size() - input.size());
    }

    Doors doors = calc_doors(path);
    for (size_t i = 0; i < 4; i++) {
      if (doors[i] && exists(position, i)) {
        const string new_path = path + direction(i);
        const Position new_position = new_pos(position, i);
        q.push({new_position, new_path});
      }
    }
  }

  return result;
}

} // namespace Day17
