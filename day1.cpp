#include "day1.hpp"
#include "util.hpp"
#include <array>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <stdexcept>
#include <unordered_set>
#include <vector>

namespace Day1 {

char turn(const char direction, const char turn) {
  // clang-format off
  static const vector<array<char, 3>> turns = {
      {'n', 'R', 'e'},
      {'n', 'L', 'w'},
      {'e', 'R', 's'},
      {'e', 'L', 'n'},
      {'s', 'R', 'w'},
      {'s', 'L', 'e'},
      {'w', 'R', 'n'},
      {'w', 'L', 's'},
  };
  // clang-format on
  for (const array<char, 3> entry : turns) {
    if (entry[0] == direction && entry[1] == turn) {
      return entry[2];
    }
  }

  throw runtime_error(std::format("invalid turn: {} {}", direction, turn));
}

int solve_day1_pt1(const string &input) {
  char direction = 'n';
  int x = 0;
  int y = 0;

  vector<string> tokens = util::split(input, " ");
  for (size_t i = 0; i < tokens.size(); i++) {
    string &token = tokens[i];
    if (i != tokens.size() - 1) {
      token.pop_back();
    }
    const char current_turn = token[0];
    token.erase(0, 1);
    const int distance = stoi(token);

    direction = turn(direction, current_turn);
    switch (direction) {
    case 'n':
      y -= distance;
      break;
    case 'w':
      x -= distance;
      break;
    case 's':
      y += distance;
      break;
    case 'e':
      x += distance;
      break;
    default:
      throw runtime_error(std::format("unexpected direction: {}", direction));
    }
  }
  return abs(x) + abs(y);
}

int solve_day1_pt2(const string &input) {
  char direction = 'n';
  int x = 0;
  int y = 0;

  vector<string> tokens = util::split(input, " ");
  unordered_set<util::Point<int>, util::PointHash> visited;
  for (size_t i = 0; i < tokens.size(); i++) {
    string &token = tokens[i];
    if (i != tokens.size() - 1) {
      token.pop_back();
    }
    const char current_turn = token[0];
    token.erase(0, 1);
    const int distance = stoi(token);

    direction = turn(direction, current_turn);
    switch (direction) {
    case 'n':
      y -= distance;
      for (int i = 0; i < distance; i++) {
        const int y_1 = y + distance - i;
        cout << "emplace " << x << " " << y_1 << endl;
        if (!visited.emplace(util::Point<int>{x, y_1}).second) {
          return abs(x) + abs(y_1);
        }
      }
      break;
    case 'w':
      x -= distance;
      for (int i = 0; i < distance; i++) {
        const int x_1 = x + distance - i;
        cout << "emplace " << x_1 << " " << y << endl;
        if (!visited.emplace(util::Point<int>{x_1, y}).second) {
          return abs(x_1) + abs(y);
        }
      }
      break;
    case 's':
      y += distance;
      for (int i = 0; i < distance; i++) {
        const int y_1 = y - distance + i;
        cout << "emplace " << x << " " << y_1 << endl;
        if (!visited.emplace(util::Point<int>{x, y_1}).second) {
          return abs(x) + abs(y_1);
        }
      }
      break;
    case 'e':
      x += distance;
      for (int i = 0; i < distance; i++) {
        const int x_1 = x - distance + i;
        cout << "emplace " << x_1 << " " << y << endl;
        if (!visited.emplace(util::Point<int>{x_1, y}).second) {
          return abs(x_1) + abs(y);
        }
      }
      break;
    default:
      throw runtime_error(std::format("unexpected direction: {}", direction));
    }
  }

  throw runtime_error("unreachable!");
}

} // namespace Day1
