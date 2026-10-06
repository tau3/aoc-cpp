#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
  uint8_t used;
  uint8_t avail;
  bool has_target_data;
  uint8_t x;
  uint8_t y;
};

pair<uint8_t, uint8_t> parse_position(const string &fs) {
  vector<string> tokens = util::split(fs, "/");
  const string node = tokens[2];

  tokens = util::split(node, "-");

  string x = tokens[1];
  string y = tokens[2];

  x.erase(0, 1);
  y.erase(0, 1);

  return {stoi(x), stoi(y)};
}

vector<Node> parse_input(const vector<string> &input) {
  vector<Node> nodes;
  uint8_t max_x = 0;
  for (size_t i = 2; i < input.size(); i++) {
    const string &raw = input[i];
    const vector<string> tokens = util::split_by_spaces(raw);

    const string fs = tokens[0];

    string used = tokens[2];
    string avail = tokens[3];
    used.pop_back();
    avail.pop_back();

    const auto [x, y] = parse_position(fs);

    const Node node{static_cast<uint8_t>(stoi(used)),
                    static_cast<uint8_t>(stoi(avail)), false, x, y};

    max_x = max(max_x, x);

    nodes.push_back(node);
  }

  for (Node &node : nodes) {
    if (node.x == max_x && node.y == 0) {
      node.has_target_data = true;
    }
  }

  return nodes;
}

vector<vector<Node>> make_all_perms(const vector<Node> &nodes) {
  throw runtime_error("not implemented yet!");
}

size_t solve(const vector<string> &input) {
  const vector<Node> nodes = parse_input(input);

  queue<pair<vector<Node>, size_t>> q;
  q.push({nodes, 0});

  unordered_set<vector<Node>> visited;
  while (!q.empty()) {
    const auto [nodes, depth] = q.front();
    q.pop();

    if (nodes.is_goal_data()) {
      return depth + 1;
    }

    vector<vector<Node>> steps = make_all_perms(nodes);
    for (const vector<Node> &step : steps) {
      if (!visited.add(step)) {
        q.push({step, depth + 1});
      }
    }
  }

  throw runtime_error("unreachable!");
}
