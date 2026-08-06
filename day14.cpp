#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace Day14 {

struct Deer {
  int speed;
  int fly;
  int rest;
};

int distance(const Deer &deer, int time) {
  const int cycle = deer.fly + deer.rest;
  int result = (time / cycle) * deer.speed * deer.fly;

  int reminder = time % cycle;
  result += deer.speed * std::min(reminder, deer.fly);

  return result;
}

Deer parse(const std::string &line) {
  // "Comet can fly 14 km/s for 10 seconds, but then must rest for 127
  // seconds.",
  const auto tokens = util::split(line, " ");
  const int speed = stoi(tokens[3]);
  const int fly = stoi(tokens[6]);
  const int rest = stoi(tokens[13]);

  return Deer{speed, fly, rest};
}

int solve_day14_pt1(const std::vector<std::string> &input) {
  int result = 0;
  for (const auto &line : input) {
    Deer deer = parse(line);
    result = std::max(result, distance(deer, 2503));
  }
  return result;
}

int solve_day14_pt2(const std::vector<Deer> &deers) {
  const size_t count = deers.size();
  std::vector<int> pos(count);
  std::vector<int> all_points(count);

  for (int i = 0; i < 1000; i++) {
    for (size_t j = 0; j < count; j++) {
      const Deer &deer = deers[j];
      pos[j] = distance(deer, i);
    }

    size_t max_pos_ix = 0;
    int max_pos = 0;
    for (size_t j = 0; j < count; j++) {
      if (max_pos < pos[j]) {
        max_pos = pos[j];
        max_pos_ix = j;
      }
    }
    all_points[max_pos_ix]++;
  }

  int result = 0;
  for (const int p : all_points) {
    if (result < p) {
      result = p;
    }
  }
  return result;
}

int solve_day14_pt2(const std::vector<std::string> &input) {
  std::vector<Deer> deers;
  for (const auto &line : input) {
    Deer deer = parse(line);
    deers.push_back(deer);
  }
  return solve_day14_pt2(deers);
}

} // namespace Day14
