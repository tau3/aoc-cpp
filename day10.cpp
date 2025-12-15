#include "day10.hpp"
#include "gauss.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace Day10 {

string &unquote(string &str) {
  str.erase(0, 1);
  str.erase(str.size() - 1);
  return str;
}

using Button = vector<size_t>;
using State = vector<bool>;
using Levels = vector<size_t>;

State press_button(const State &state, const Button &button) {
  State result = state;
  for (const size_t i : button) {
    result[i] = !state[i];
  }
  return result;
}

vector<size_t> string_to_nums(const string &input) {
  vector<size_t> result;
  const vector<string> tokens = util::split(input, ",");
  for (const string &token : tokens) {
    result.push_back(stol(token));
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

tuple<State, vector<Button>, Levels> parse_line(const string &line) {
  vector<string> tokens = util::split(line, " ");

  vector<Button> buttons;
  for (size_t i = 1; i < tokens.size() - 1; i++) {
    string &button_str = tokens[i];
    unquote(button_str);
    const Button button = string_to_nums(button_str);
    const vector<string> indexes = util::split(button_str, ",");
    buttons.push_back(button);
  }

  State target = parse_target(tokens[0]);
  Levels levels = string_to_nums(unquote(tokens[tokens.size() - 1]));

  return {target, buttons, levels};
}

int solve_line(const string &line) {
  const auto &[target, buttons, _] = parse_line(line);

  queue<pair<State, int>> states;
  const auto initial = vector(target.size(), false);
  assert(initial.size() > 0);
  states.push({initial, 0});

  unordered_set<State> cache;
  while (!states.empty()) {
    const auto [state, n] = states.front();
    states.pop();

    if (cache.find(state) != cache.end()) {
      continue;
    }

    if (state == target) {
      return n;
    }

    cache.emplace(state);

    for (const Button &button : buttons) {
      const State after_press = press_button(state, button);
      states.push({after_press, n + 1});
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

vector<vector<Gauss::num_t>> to_matrix(const vector<Button> &buttons,
                                       const Levels &levels) {
  vector<vector<Gauss::num_t>> result;
  for (size_t i = 0; i < levels.size(); i++) {
    vector<Gauss::num_t> line(levels.size(), 0);
    for (size_t j = 0; j < buttons.size(); j++) {
      const Button button = buttons[j];
      if (find(button.begin(), button.end(), i) != button.end()) {
        line[j] = 1;
      }
    }
    line.push_back(levels[i]);
    result.push_back(line);
  }
  return result;
}

int solve_pt2_line(const string &line) {
  const auto &[_, buttons, levels] = parse_line(line);
  auto matrix = to_matrix(buttons, levels);
  const vector<Gauss::num_t> solution = Gauss::gauss(matrix);

  int result = 0;
  for (size_t i = 0; i < solution.size(); i++) {
    result += solution[i];
  }
  return result;
}

int solve_day10_pt2(const vector<string> &input) {
  int result = 0;
  for (const string &line : input) {
    result += solve_pt2_line(line);
  }
  return result;
}

} // namespace Day10
