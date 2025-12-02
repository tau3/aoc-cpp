#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day24 {

using namespace std;

using num_t = long;

bool eval(unordered_map<string, string> &data, const string &key) {
  const string &expression = data[key];
  if (expression.find(" ") == expression.npos) {
    assert((expression == "1") || (expression == "0"));
    return (expression == "1");
  }

  const vector<string> tokens = split(expression, " ");
  const string lhs_key = tokens[0];
  const bool lhs = eval(data, lhs_key);

  const string rhs_key = tokens[2];
  const bool rhs = eval(data, rhs_key);

  const string operation = tokens[1];
  bool result;
  if (operation == "AND") {
    result = lhs & rhs;
  } else if (operation == "OR") {
    result = lhs | rhs;
  } else if (operation == "XOR") {
    result = lhs ^ rhs;
  } else {
    throw "unknown operation: " + operation;
  }

  data[key] = result ? "1" : "0";
  return result;
}

num_t solve(unordered_map<string, string> &data) {
  vector<string> z_keys;
  for (const auto &[k, _] : data) {
    if (k[0] == 'z') {
      z_keys.push_back(k);
    }
  }
  assert((sizeof(num_t) * 8) >= z_keys.size());
  sort(z_keys.begin(), z_keys.end(), greater<>());

  num_t result = 0;
  for (const string &z_key : z_keys) {
    const bool bit = eval(data, z_key);
    result = result << 1;
    result |= bit;
  }
  return result;
}

num_t solve_day24_pt1(const vector<string> &input) {
  unordered_map<string, string> data;
  for (const string &line : input) {
    if (line.empty()) {
      continue;
    }
    if (line.find(":") != line.npos) {
      const vector<string> tokens = split(line, ": ");
      string key = tokens[0];
      string value = tokens[1];
      data[key] = value;
    } else {
      const vector<string> tokens = split(line, " -> ");
      string key = tokens[1];
      string value = tokens[0];
      data[key] = value;
    }
  }

  return solve(data);
}

} // namespace Day24
