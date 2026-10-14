#include "day2.hpp"
#include <array>
#include <format>
#include <functional>
#include <stdexcept>

namespace Day2 {

int move(const int current, const char direction) {
  switch (direction) {
  case 'U':
    if (current == 1 || current == 2 || current == 3) {
      return current;
    } else {
      return current - 3;
    }
    break;
  case 'L':
    if (current == 1 || current == 4 || current == 7) {
      return current;
    } else {
      return current - 1;
    }
    break;
  case 'R':
    if (current == 3 || current == 6 || current == 9) {
      return current;
    } else {
      return current + 1;
    }
    break;
  case 'D':
    if (current == 7 || current == 8 || current == 9) {
      return current;
    } else {
      return current + 3;
    }
    break;
  }
  throw std::runtime_error(std::format("invalid direction: {}", direction));
}

char move2(const char current, const char direction) {
  // up, down, left, right
  // clang-format off
  const static std::array<std::array<char, 5>, 13> moves = {
      std::array<char,5>{'1', '1', '3', '1', '1'},
      {'2', '2', '6', '2', '3'},
      {'3', '1', '7', '2', '4'},
      {'4', '4', '8', '3', '4'},
      {'5', '5', '5', '5', '6'},
      {'6', '2', 'A', '5', '7'},
      {'7', '3', 'B', '6', '8'},
      {'8', '4', 'C', '7', '9'},
      {'9', '9', '9', '8', '9'},
      {'A', '6', 'A', 'A', 'B'},
      {'B', '7', 'D', 'A', 'C'},
      {'C', '8', 'C', 'B', 'C'},
      {'D', 'B', 'D', 'D', 'D'},
  };
  size_t index = 0;
  switch(direction){
  case 'U':
    index = 1;
    break;
  case 'D':
    index = 2;
    break;
  case 'L':
    index = 3;
    break;
  case 'R':
    index = 4;
    break;
  default:
  throw runtime_error(std::format("invalid direction {}", direction));
}
  // clang-format on
  for (const std::array<char, 5> line : moves) {
    if (line[0] != current) {
      continue;
    }
    return line[index];
  }
  throw runtime_error(std::format("invalid button {}", current));
}

std::string solve(const std::vector<std::string> &input,
                  std::function<int(int, char)> keypad) {
  std::string result = "";
  char current = '5';
  for (const std::string &line : input) {
    for (const char letter : line) {
      current = keypad(current, letter);
    }
    result += current;
  }
  return result;
}

std::string solve_day2_pt1(const std::vector<std::string> &input) {
  return solve(input, move);
}

std::string solve_day2_pt2(const std::vector<std::string> &input) {
  return solve(input, move2);
}

} // namespace Day2
