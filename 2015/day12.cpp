#include "day12.hpp"


namespace Day12 {

enum class State { NONE, MINUS, NUMBER };

int to_num(const char c) { return c - '0'; }

int solve_day12_pt1(const std::string &json) {
  State state = State::NONE;
  int result = 0;
  int num = 0;
  for (const char c : json) {
    switch (state) {
    case State::NONE:
      if (c == '-') {
        state = State::MINUS;
      } else if (std::isdigit(c)) {
        state = State::NUMBER;
        result *= 10;
        result += to_num(c);
      };
      break;
    case State::MINUS:
      if (std::isdigit(c)) {
        result = -to_num(c);
        state = State::NUMBER;
      } else {
        state = State::NONE;
      }
      break;
    case State::NUMBER:
      if (std::isdigit(c)) {
        result *= 10;
        result += to_num(c);
      } else {
        num += result;
        result = 0;
        state = State::NONE;
      }
      break;
    }
  }
  return num;
}
} // namespace Day12
