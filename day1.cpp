#include "day1.hpp"
#include "util.hpp"
#include <array>
#include <cstdlib>
#include <format>
#include <stdexcept>
#include <vector>

namespace Day1 {

char turn(const char direction, const char turn) {
  // clang-format off
  static const vector<array<char, 3>> turns = {
      {'n', 'R', 'e'},
      {'n', 'L', 'w'},
      {'e', 'R', 's'},
      {'e', 'L', 'n'},
      {'s', 'R', 'w'},
      {'s', 'L', 'e'},
      {'w', 'R', 'n'},
      {'w', 'L', 's'},
  };
  // clang-format on
  for (const array<char, 3> entry : turns) {
    if (entry[0] == direction && entry[1] == turn) {
      return entry[2];
    }
  }

  throw runtime_error(std::format("invalid turn: {} {}", direction, turn));
}

int solve_day1_pt1(const string &input) {
  char direction = 'n';
  int x = 0;
  int y = 0;

  vector<string> tokens = util::split(input, " ");
  for (string &token : tokens) {
    token.pop_back();
    const char current_turn = token[0];
    token.erase(0, 1);
    const int distance = stoi(token);

    direction = turn(direction, current_turn);
    switch (direction) {
    case 'n':
      y -= distance;
      break;
    case 'w':
      x -= distance;
      break;
    case 's':
      y += distance;
      break;
    case 'e':
      x += distance;
      break;
    default:
      throw runtime_error(std::format("unexpected direction: {}", direction));
    }
  }
  return abs(x) + abs(y);
}

} // namespace Day1
