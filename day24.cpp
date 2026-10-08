#include "day24.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <unordered_set>

namespace Day24 {

using Point = util::Point<uint16_t>;
using PointSet = unordered_set<Point, util::PointHash>;

vector<Point> get_adjacent(const vector<string> &maze, const Point &point) {
  vector<Point> result;
  for (const Point &current :
       {point.down(), point.left(), point.right(), point.up()}) {
    if (maze[current.row][current.col] != '#') {
      result.push_back(current);
    }
  }
  return result;
}

struct State {
  Point point;
  PointSet targets;
  uint16_t depth;
};

bool operator==(const State &lhs, const State &rhs) {
  return lhs.depth == rhs.depth && lhs.point == rhs.point &&
         lhs.targets == rhs.targets;
}

struct StateHash {
  size_t operator()(const State &state) const {
    size_t result = 17;

    static util::PointHash point_hash;
    std::function<size_t(const Point &)> f = [](const Point &point) {
      return point_hash(point);
    };

    result = 31 * result + util::hash_code(state.targets, f);
    result = 31 * result + state.depth;
    result = 31 * result + point_hash(state.point);
    return result;
  }
};

pair<PointSet, Point> find_targets(const vector<string> &maze) {
  PointSet targets;
  Point start(1, 1);
  for (size_t row = 0; row < maze.size(); row++) {
    for (size_t col = 0; col < maze[0].size(); col++) {
      const char c = maze[row][col];
      if (c != '#' && c != '.') {
        const Point point(row, col);
        targets.insert(point);
        if (c == '0') {
          start = point;
        }
      }
    }
  }
  return {targets, start};
}

size_t solve(const vector<string> &maze) {
  const auto [all_targets, start] = find_targets(maze);

  State initial{start, {start}, 0};

  queue<State> q;
  q.push(initial);
  unordered_set<State, StateHash> states;
  states.insert(initial);

  while (!q.empty()) {
    const State state = q.front();
    q.pop();

    if (state.targets == all_targets) {
      return state.depth;
    }

    const vector<Point> adjacents = get_adjacent(maze, state.point);
    for (const Point &adjacent : adjacents) {
      auto visited_targets = state.targets;
      if (maze[adjacent.row][adjacent.col] != '.') {
        visited_targets.insert(adjacent);
      }

      State new_state{adjacent, visited_targets, state.depth + 1};
      if (states.insert(new_state).second) {
        q.push(new_state);
      }
    }
  }

  throw runtime_error("unreachable!");
}

} // namespace Day24
