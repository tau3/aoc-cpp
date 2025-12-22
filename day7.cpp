#include "day7.hpp"
#include "util.hpp"
#include <cassert>
#include <string>
#include <unordered_map>
#include <variant>

namespace Day7 {

using Value = variant<string, int>;
using Instructions = unordered_map<string, Value>;

int eval(const string key, Instructions &instructions) {
  const Value expr = instructions[key];
  if (holds_alternative<int>(expr)) {
    return get<int>(expr);
  }

  const string raw = get<string>(expr);
  const vector<string> tokens = util::split(raw, " ");
  if (tokens.size() == 1) {
    const int result = stoi(tokens[0]);
    instructions[key] = result;
    return result;
  }
  if (tokens.size() == 2) {
    assert(tokens[0] == "NOT");
    const int result = !eval(tokens[1], instructions);
    instructions[key] = result;
    return result;
  }
  if (tokens.size() == 3) {
    const string operation = tokens[1];
    const int left = eval(tokens[0], instructions);
    const int right = eval(tokens[2], instructions);
    if (operation == "AND") {
      const int result = left & right;
      instructions[key] = result;
      return result;
    } else if (operation == "OR") {
      const int result = left | right;
      instructions[key] = result;
      return result;
    } else if (operation == "LSHIFT") {
      const int result = left << right;
      instructions[key] = result;
      return result;
    } else if (operation == "RSHIFT") {
      const int result = left >> right;
      instructions[key] = result;
      return result;
    } else {
      throw "unknown operation " + raw;
    }
  }

  throw "unreachable";
}

int solve_day7_pt1(const vector<string> &input) {
  Instructions instructions;
  for (const string &line : input) {
    const vector<string> tokens = util::split(line, " -> ");
    const string value = tokens[0];
    const string key = tokens[1];
    instructions[key] = value;
  }

  return eval("a", instructions);
}

} // namespace Day7
