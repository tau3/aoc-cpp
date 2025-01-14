#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day21 {

using namespace std;

const int A = -1;
const int UP = -2;
const int DOWN = -3;
const int LEFT = -4;
const int RIGHT = -5;

using Graph = unordered_map<int, unordered_map<int, int>>;

// clang-format off
const Graph NUMERIC_KEYPAD = {
    {7, {{4, DOWN}, {8, RIGHT}}},
    {8, {{7, LEFT}, {9, RIGHT}, {5, DOWN}}},
    {9, {{8, LEFT}, {6, DOWN}}},
    {4, {{7, UP}, {5, RIGHT}, {1, DOWN}}},
    {5, {{4, LEFT}, {8, UP}, {6, RIGHT}, {2, DOWN}}},
    {6, {{9, UP}, {5, LEFT}, {3, DOWN}}},
    {1, {{2, RIGHT}, {4, UP}}},
    {2, {{1, LEFT}, {5, UP}, {3, RIGHT}, {0, DOWN}}},
    {3, {{6, UP}, {2, LEFT}, {A, DOWN}}},
    {0, {{2, UP}, {A, RIGHT}}},
    {A, {{3, UP}, {0, LEFT}}}};
// clang-format on

const Graph DIRECTIONAL_KEYPAD = {
    {UP, {{DOWN, DOWN}, {A, RIGHT}}},
    {A, {{UP, LEFT}, {RIGHT, DOWN}}},
    {LEFT, {{DOWN, RIGHT}}},
    {DOWN, {{LEFT, LEFT}, {RIGHT, RIGHT}, {UP, UP}}},
    {RIGHT, {{DOWN, LEFT}, {A, UP}}}};

int to_int(const char c) {
  switch (c) {
  case 'A':
    return A;
  case '^':
    return UP;
  case '<':
    return LEFT;
  case 'v':
    return DOWN;
  case '>':
    return RIGHT;
  default:
    return c - '0';
  }
}

char to_char(const int i) {
  switch (i) {
  case A:
    return 'A';
  case UP:
    return '^';
  case LEFT:
    return '<';
  case DOWN:
    return 'v';
  case RIGHT:
    return '>';
  default:
    return '0' + i;
  }
}

int extract_min(vector<int> &queue, const unordered_map<int, int> &distances) {
  assert(!queue.empty());

  int result = queue[0];
  int min_distance = distances.at(result);
  size_t index = 0;
  for (size_t i = 1; i < queue.size(); ++i) {
    const int current = queue[i];
    const int distance = distances.at(current);
    if (distance < min_distance) {
      result = current;
      min_distance = distance;
      index = i;
    }
  }

  queue.erase(queue.begin() + index);
  return result;
}

optional<int> get_next(int current, char direction, const Graph &graph) {
  const auto &button_to_direction = graph.at(current);
  for (const auto &[button, current_direction] : button_to_direction) {
    if (current_direction == to_int(direction)) {
      return button;
    }
  }
  return nullopt;
}

bool is_valid_path(const int start, const string &path, const Graph &graph) {
  int current = start;
  for (const auto direction : path) {
    optional<int> maybe_next = get_next(current, direction, graph);
    if (maybe_next.has_value()) {
      current = maybe_next.value();
    } else {
      return false;
    }
  }
  return true;
}

string optimize(const int start, const int end, const Graph &graph,
                const string &path) {
  string v1 = path;
  sort(v1.begin(), v1.end());
  if (is_valid_path(start, v1, graph)) {
    return v1;
  }
  string v2 = v1;
  reverse(v2.begin(), v2.end());
  if (is_valid_path(start, v2, graph)) {
    return v2;
  }
  return path;
}

string shortest_path(const int start, const int end, const Graph &graph) {
  unordered_map<int, int> dist;
  unordered_map<int, int> prev;
  vector<int> q;
  for (const auto &[v, _] : graph) {
    dist[v] = numeric_limits<int>::max();
    q.push_back(v);
  }
  dist[start] = 0;

  while (!q.empty()) {
    int u = extract_min(q, dist);

    for (const auto &[v, _] : graph.at(u)) {
      int alt = dist[u] + 1;
      if (alt < dist[v]) {
        dist[v] = alt;
        prev[v] = u;
      }
    }
  }

  int u = end;
  vector<int> s;
  while (u != start) {
    s.push_back(u);
    u = prev[u];
  }
  s.push_back(start);

  string result;
  for (size_t i = 1; i < s.size(); ++i) {
    char from = s[i - 1];
    char to = s[i];
    result += to_char(graph.at(to).at(from));
  }

  return optimize(start, end, graph, result);
}

string process_sequence(const string &code, const Graph &graph) {
  int start = A;
  string result;
  for (size_t i = 0; i < code.size(); ++i) {
    int end = to_int(code[i]);
    result += shortest_path(start, end, graph);
    result += 'A';
    start = end;
  }
  return result;
}

int complexity(const string &code) {
  string result = process_sequence(code, NUMERIC_KEYPAD);
  result = process_sequence(result, DIRECTIONAL_KEYPAD);
  result = process_sequence(result, DIRECTIONAL_KEYPAD);
  int numeric_part = stoi(code.substr(0, code.size() - 1));

  return result.size() * numeric_part;
}

int solve_day21_pt1(const vector<string> &input) {
  int result = 0;
  for (const string &code : input) {
    result += complexity(code);
  }
  return result;
}

} // namespace Day21
