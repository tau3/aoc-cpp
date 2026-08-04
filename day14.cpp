#include "util.hpp"
#include <algorithm>
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
  // "Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.",
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

} // namespace Day14
