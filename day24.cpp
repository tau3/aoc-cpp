#include "day24.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <vector>

namespace Day24 {

using Point = util::Point<uint16_t>;

bool comp(const Point &lhs, const Point &rhs) {
  if (lhs.row != rhs.row)
    return lhs.row > rhs.row;
  return lhs.col < rhs.col;
}

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

class State {
private:
  Point point;
  vector<Point> _targets;
  uint16_t depth;

public:
  explicit State(const Point &point, const vector<Point> &targets,
                 const uint16_t depth) noexcept
      : point(point), _targets(targets), depth(depth) {
    sort(_targets.begin(), _targets.end(), comp);
    _targets.erase(std::unique(_targets.begin(), _targets.end()),
                   _targets.end());
  }

  bool operator==(const State &state) const {
    return depth == state.depth && point == state.point &&
           _targets == state._targets;
  }

  const Point &get_point() const { return point; }

  const vector<Point> &get_targets() const { return _targets; }

  uint16_t get_depth() const { return depth; }

  size_t hash_code() const {
    size_t result = 17;

    static util::PointHash point_hash;
    static std::function<size_t(const Point &)> f = [](const Point &point) {
      return point_hash(point);
    };

    result = 31 * result + util::hash_code(_targets, f);
    result = 31 * result + depth;
    result = 31 * result + point_hash(point);
    return result;
  }
};

struct StateHash {
  size_t operator()(const State &state) const { return state.hash_code(); }
};

pair<vector<Point>, Point> find_targets(const vector<string> &maze) {
  vector<Point> targets;
  Point start(1, 1);
  for (size_t row = 0; row < maze.size(); row++) {
    for (size_t col = 0; col < maze[0].size(); col++) {
      const char c = maze[row][col];
      if (c != '#' && c != '.') {
        const Point point(row, col);
        targets.push_back(point);
        if (c == '0') {
          start = point;
        }
      }
    }
  }
  return {targets, start};
}

size_t solve_pt1(const vector<string> &maze) {
  auto [all_targets, start] = find_targets(maze);
  sort(all_targets.begin(), all_targets.end(), comp);

  State initial{start, {start}, 0};

  queue<State> q;
  q.push(initial);
  unordered_set<State, StateHash> states;
  states.insert(initial);

  while (!q.empty()) {
    const State state = q.front();
    q.pop();

    if (state.get_targets() == all_targets) {
      return state.get_depth();
    }

    const vector<Point> adjacents = get_adjacent(maze, state.get_point());
    for (const Point &adjacent : adjacents) {
      auto visited_targets = state.get_targets();
      if (maze[adjacent.row][adjacent.col] != '.') {
        visited_targets.push_back(adjacent);
      }

      State new_state(adjacent, visited_targets, state.get_depth() + 1);
      if (states.insert(new_state).second) {
        q.push(new_state);
      }
    }
  }

  throw runtime_error("unreachable!");
}

size_t solve_pt2(const vector<string> &maze) {
  auto [all_targets, start] = find_targets(maze);
  sort(all_targets.begin(), all_targets.end(), comp);

  State initial{start, {start}, 0};

  queue<State> q;
  q.push(initial);
  unordered_set<State, StateHash> states;
  states.insert(initial);

  while (!q.empty()) {
    const State state = q.front();
    q.pop();

    if (state.get_point() == start && state.get_targets() == all_targets) {
      return state.get_depth();
    }

    const vector<Point> adjacents = get_adjacent(maze, state.get_point());
    for (const Point &adjacent : adjacents) {
      auto visited_targets = state.get_targets();
      if (maze[adjacent.row][adjacent.col] != '.') {
        visited_targets.push_back(adjacent);
      }

      State new_state(adjacent, visited_targets, state.get_depth() + 1);
      if (states.insert(new_state).second) {
        q.push(new_state);
      }
    }
  }

  throw runtime_error("unreachable!");
}

} // namespace Day24
