#include "day24.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <unordered_set>

namespace Day24 {

using Point = util::Point<uint16_t>;
using Maze = vector<string>;

vector<Point> get_adjacent(const Maze &maze, const Point &point) {
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
  vector<Point> visited;
  vector<Point> targets;
  size_t depth;
};

bool operator==(const State &lhs, const State &rhs) {
  return lhs.depth == rhs.depth && lhs.point == rhs.point &&
         lhs.targets == rhs.targets && lhs.visited == rhs.visited;
}

struct StateHash {
  size_t operator()(const State &state) const {
    size_t result = 17;

    util::PointHash point_hash;
    std::function<size_t(const Point &)> f = [&point_hash](const Point &point) {
      return point_hash(point);
    };

    result = 31 * util::hash_code(state.visited, f);
    result = 31 * result + util::hash_code(state.targets, f);
    result = 31 * result + state.depth;
    result = 31 * result + point_hash(state.point);
    return result;
  }
};

size_t solve(const vector<string> &maze) {
  vector<Point> targets;
  for (size_t row = 0; row < maze.size(); row++) {
    for (size_t col = 0; col < maze[0].size(); col++) {
      const char c = maze[row][col];
      if (c != '#' && c != '.') {
        targets.push_back(Point(row, col));
      }
    }
  }

  // TODO check actual input
  Point start(1, 1);
  State initial{start, {start}, {start}, 0};

  queue<State> q;
  q.push(initial);
  unordered_set<State, StateHash> states;
  states.insert(initial);

  while (!q.empty()) {
    const State state = q.front();
    q.pop();

    if (state.visited == targets) {
      return state.depth;
    }

    const vector<Point> adjacents = get_adjacent(maze, state.point);
    for (const Point &adjacent : adjacents) {
      vector<Point> visited = state.visited;
      visited.push_back(adjacent);

      vector<Point> targets = state.targets;
      if (maze[adjacent.row][adjacent.col] != '.') {
        targets.push_back(adjacent);
      }

      State new_state{adjacent, visited, targets, state.depth + 1};
      if (states.insert(new_state).second) {
        q.push(new_state);
        // cout << q.size() << endl;
      } else {
        cout << "HIT" << endl;
      }
    }
  }

  throw runtime_error("unreachable!");
}

} // namespace Day24
