#include "day8.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Day8 {

using Box = array<long, 3>;

struct BoxHash {
  size_t operator()(const Box &point) const noexcept {
    return 7 * point[0] + 31 * point[1] + 13 * point[2];
  }
};

using Distances = map<long, pair<Box, Box>>;
using Circuit = unordered_set<Box, BoxHash>;

long euclid(const Box &left, const Box &right) {
  return sqrt((left[0] - right[0]) * (left[0] - right[0]) +
              (left[1] - right[1]) * (left[1] - right[1]) +
              (left[2] - right[2]) * (left[2] - right[2]));
}

Box to_point(const string &line) {
  const auto tokens = util::split(line, ",");
  return {stol(tokens[0]), stol(tokens[1]), stol(tokens[2])};
}

struct CircuitSizeComparator {
  bool operator()(const Circuit &left, const Circuit &right) const noexcept {
    return left.size() > right.size();
  }
};

long solve_day8_pt1(const vector<string> &input) {
  Distances distances;
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = i; j < input.size(); j++) {
      const Box left = to_point(input[i]);
      const Box right = to_point(input[j]);
      const long distance = euclid(left, right);
      distances[distance] = {left, right};
    }
  }

  vector<Circuit> circuits;
  for (int i = 0; i < 10; i++) {
    const auto &[left, right] = distances.erase(distances.begin())->second;
    bool is_new_circuit = true;
    for (Circuit circuit : circuits) {
      if ((circuit.find(left) != circuit.end()) ||
          (circuit.find(right) != circuit.end())) {
        circuit.emplace(left);
        circuit.emplace(right);
        is_new_circuit = false;
        break;
      }
    }
    if (is_new_circuit) {
      Circuit circuit;
      circuit.emplace(left);
      circuit.emplace(right);
      circuits.push_back(circuit);
    }
  }

  sort(circuits.begin(), circuits.end(), CircuitSizeComparator());
  return circuits[0].size() * circuits[1].size() * circuits[2].size();
}

} // namespace Day8
