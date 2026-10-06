#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
  uint8_t used;
  uint8_t avail;
  bool has_target_data;
  uint8_t x;
  uint8_t y;

  size_t hash_code() const {};
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

class Nodes {
private:
  using Key = util::Point<uint8_t>;

  unordered_map<Key, Node, util::PointHash> nodes;

public:
  void put(const uint8_t x, const uint8_t y, const Node &node) {
    Key key(x, y);
    nodes.insert({key, node});
  }

  void set_target_data() {
    uint8_t max_x = 0;
    for (const auto &[k, v] : nodes) {
      max_x = max(max_x, k.col);
    }

    Key key(max_x, 0);
    Node &node = nodes.at(key);
    node.has_target_data = true;
  }

  size_t hash_code() const {
    size_t result = 0;
    util::PointHash point_hash;
    for (const auto &[k, v] : nodes) {
      result ^= point_hash(k);
      result ^= v.hash_code();
    }
    return result;
  }

  bool is_goal_data() const {
    Key key(0, 0);
    const Node &node = nodes.at(key);
    return node.has_target_data;
  }
};

struct NodesHash {
  size_t operator()(const Nodes &nodes) const { return nodes.hash_code(); };
};

Nodes parse_input(const vector<string> &input) {
  Nodes nodes;
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

    nodes.put(x, y, node);
  }

  nodes.set_target_data();

  return nodes;
}

vector<Nodes> make_all_perms(const Nodes &nodes) {
  throw runtime_error("not implemented yet!");
}

size_t solve(const vector<string> &input) {
  const Nodes nodes = parse_input(input);

  queue<pair<Nodes, size_t>> q;
  q.push({nodes, 0});

  unordered_set<Nodes, NodesHash> visited;
  while (!q.empty()) {
    const auto [nodes, depth] = q.front();
    q.pop();

    if (nodes.is_goal_data()) {
      return depth + 1;
    }

    vector<Nodes> steps = make_all_perms(nodes);
    for (const Nodes &step : steps) {
      if (!visited.insert(step).second) {
        q.push({step, depth + 1});
      }
    }
  }

  throw runtime_error("unreachable!");
}
