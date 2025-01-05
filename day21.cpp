#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>
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

const unordered_map<int, vector<int>> NUMERIC_KEYPAD = {
    {7, {4, 8}},       {8, {7, 9, 5}}, {9, {8, 6}}, {4, {7, 5, 1}},
    {5, {4, 8, 6, 2}}, {6, {9, 5, 3}}, {1, {2, 4}}, {2, {1, 5, 3, 0}},
    {3, {6, 2, A}},    {0, {2, A}},    {A, {3, 0}}};

const unordered_map<int, vector<int>> DIRECTIONAL_KEYPAD = {
    {UP, {DOWN, A}},
    {A, {UP, RIGHT}},
    {LEFT, {DOWN}},
    {DOWN, {LEFT, RIGHT, UP}},
    {RIGHT, {DOWN, A}}};

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
    return LEFT;
  case DOWN:
    return DOWN;
  case RIGHT:
    return RIGHT;
  default:
    return '0' + i;
  }
}

int extract_min(vector<int> &queue, const unordered_map<int, int> distances) {
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

string shortest_path(const int start, const int end,
                     const unordered_map<int, vector<int>> graph) {
  unordered_map<int, int> dist;
  unordered_map<int, int> prev;
  vector<int> q;
  for (const auto &[v, _] : graph) {
    dist[v] = numeric_limits<int>::max();
    q.push_back(v);
  }

  while (!q.empty()) {
    int u = extract_min(q, dist);

    for (int v : graph.at(u)) {
      int alt = dist[u] + 1;
      if (alt < dist[v]) {
        dist[v] = alt;
        prev[v] = u;
      }
    }
  }

  int u = end;
  string s;
  while (u != start) {
    s += to_char(u);
    u = prev[u];
  }
  reverse(s.begin(), s.end());
  return s;
}

string process_sequence(const string &code,
                        const unordered_map<int, vector<int>> &graph) {
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
  result = process_sequence(result, DIRECTIONAL_KEYPAD);

  int numeric_part = stoi(code.substr(0, code.size() - 2));
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
