#include "day10.hpp"
#include "util.hpp"
#include <cassert>
#include <queue>
#include <unordered_set>
#include <vector>

namespace Day10 {

void unquote(string &str) {
  str.erase(0, 1);
  str.erase(str.size() - 1);
}

using Button = vector<size_t>;
using State = vector<bool>;

State press_button(const State &state, const Button &button) {
  State result = state;
  for (const size_t i : button) {
    result[i] = !state[i];
  }
  return result;
}

State parse_target(string &target) {
  unquote(target);
  State result;
  for (const char c : target) {
    bool bit = (c == '.') ? false : true;
    result.push_back(bit);
  }
  return result;
}

pair<State, vector<Button>> parse_line(const string &line) {
  vector<string> tokens = util::split(line, " ");
  vector<Button> buttons;
  for (size_t i = 1; i < tokens.size() - 1; i++) {
    string &button_str = tokens[i];
    unquote(button_str);
    const vector<string> indexes = util::split(button_str, ",");
    Button button;
    for (const string &index : indexes) {
      button.push_back(stol(index));
    }
    buttons.push_back(button);
  }

  State target = parse_target(tokens[0]);

  return {target, buttons};
}

int solve_line(const string &line) {
  const auto &[target, buttons] = parse_line(line);

  queue<pair<State, int>> q;
  const auto initial = vector(target.size(), false);
  assert(initial.size() > 0);
  q.push({initial, 0});

  unordered_set<State> seen;
  while (!q.empty()) {
    const auto [state, n] = q.front();
    q.pop();

    if (seen.find(state) != seen.end()) {
      continue;
    }

    if (state == target) {
      return n;
    }

    seen.emplace(state);

    for (const Button &button : buttons) {
      const State after_press = press_button(state, button);
      q.push({after_press, n + 1});
    }
  }

  throw "unreachable";
}

int solve_day10_pt1(const vector<string> &input) {
  int result = 0;
  for (const string &line : input) {
    result += solve_line(line);
  }
  return result;
}

} // namespace Day10
