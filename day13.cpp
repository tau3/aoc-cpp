#include "day13.hpp"
#include "util.hpp"
#include <string>
#include <vector>

namespace Day13 {

using namespace std;

using Arcade = tuple<Movement, Movement, Movement>;

Movement parse_button(const string &input) {
  const vector<string> &tokens = split(input, " ");
  string x_str = tokens[2];
  string y_str = tokens[3];

  x_str = x_str.substr(2, x_str.size() - 1);
  y_str = y_str.substr(2);

  return {stoul(x_str), stoul(y_str)};
}

Movement parse_prize(const string &input) {
  const vector<string> &tokens = split(input, " ");
  string x_str = tokens[1];
  string y_str = tokens[2];

  x_str = x_str.substr(2, x_str.size() - 1);
  y_str = y_str.substr(2);

  return {stoul(x_str), stoul(y_str)};
}

vector<Arcade> parse_input(const vector<string> &input) {
  vector<Arcade> result;
  for (size_t i = 0; i < input.size(); i += 4) {
    const string a_str = input[i];
    const string b_str = input[i + 1];
    const string prize_str = input[i + 2];

    result.push_back(
        {parse_button(a_str), parse_button(b_str), parse_prize(prize_str)});
  }
  return result;
}

/*
  https://en.wikipedia.org/wiki/Cramer's_rule
  a1 * x + b1 * y = c1
  a2 * x + b2 * y = c2
  =>
  y = (a1 * c2 - c1 * a2) / (a1 * b2 - b1 * a2)
  x = (c1 - b1 * y ) / a1

  for the task:
  ax * x + bx * y = px
  ay * x + by * y = py
  =>
  b_count = (ax * py - px * ay) / (ax * by - bx * ay)
  if (ax * by - bx * ay) == 0 => no solution
  a_count = (px - bx * b_count) / ax
*/
unit_t solve_equation(const vector<Arcade> &arcades) {
  unit_t result = 0;
  for (const auto &arcade : arcades) {
    const auto &[a, b, prize] = arcade;
    if (a.x == 0) {
      continue;
    }

    const unit_t divider = a.x * b.y - b.x * a.y;
    if (divider == 0) {
      continue;
    }
    unit_t divisor = a.x * prize.y - prize.x * a.y;
    const unit_t b_count = divisor / divider;
    if (b_count * divider != divisor) {
      continue;
    }

    divisor = prize.x - b.x * b_count;
    const unit_t a_count = divisor / a.x;
    if (a_count * a.x != divisor) {
      continue;
    }
    const unit_t spent = a_count * 3 + b_count;
    result += spent;
  }
  return result;
}

unit_t solve(const vector<string> &input, const bool pt2) {
  auto arcades = parse_input(input);
  if (pt2) {
    for (auto &arcade : arcades) {
      auto &[_, _, p] = arcade;
      p.y += 10000000000000;
    }
  }
  return solve_equation(arcades);
}

unit_t solve_day13_pt1(const vector<string> &input) {
  return solve(input, false);
}

unit_t solve_day13_pt2(const vector<string> &input) {
  return solve(input, true);
}

} // namespace Day13
