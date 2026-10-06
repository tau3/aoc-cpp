#include "day22.hpp"
#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>

namespace Day22 {

struct Node {
  uint16_t used;
  uint16_t avail;
  bool has_target_data;

  size_t hash_code() const {
    size_t result = 17;
    result = result * 31 + used;
    result = result * 31 + avail;
    result = result * 31 + has_target_data;
    return result;
  };

  bool can_have_data_from(const Node &node) const { return avail >= node.used; }

  pair<Node, Node> move_data_from(const Node &node) const {
    Node to = *this;
    Node from = node;

    to.used += from.used;
    to.avail -= from.used;
    to.has_target_data = from.has_target_data;

    from.avail += from.used;
    from.used = 0;
    from.has_target_data = false;

    return {to, from};
  }

  bool operator==(const Node &other) const {
    return (used == other.used) && (avail == other.avail) &&
           (has_target_data == other.has_target_data);
  }
};

pair<uint16_t, uint16_t> parse_position(const string &fs) {
  vector<string> tokens = util::split(fs, "/");
  const string node = tokens[3];

  tokens = util::split(node, "-");

  string x = tokens[1];
  string y = tokens[2];

  x.erase(0, 1);
  y.erase(0, 1);

  return {stoi(x), stoi(y)};
}

class Nodes {
private:
  using Key = util::Point<uint16_t>;

  unordered_map<Key, Node, util::PointHash> nodes;

  Nodes get_adjacent(const Key &key) const {
    const uint16_t x = key.col;
    const uint16_t y = key.row;

    Nodes result;
    if (y > 0) {
      Key key(x, y - 1);
      result.put(x, y - 1, nodes.at(key));
    }
    if (x > 0) {
      Key key(x - 1, y);
      result.put(x - 1, y, nodes.at(key));
    }

    Key right(x + 1, y);
    auto it = nodes.find(right);
    if (it != nodes.end()) {
      result.put(right.col, right.row, it->second);
    }

    Key bottom(x, y + 1);
    it = nodes.find(right);
    if (it != nodes.end()) {
      result.put(right.col, right.row, it->second);
    }

    return result;
  }

public:
  void put(const uint16_t x, const uint16_t y, const Node &node) {
    Key key(x, y);
    nodes.insert({key, node});
  }

  void set_target_data() {
    uint16_t max_x = 0;
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

  vector<Nodes> make_all_perms() const {
    vector<Nodes> result;
    for (const auto &[key, node] : nodes) {
      if (node.used == 0) {
        continue;
      }

      Nodes adjacents = get_adjacent(key);
      for (const auto &[adj_key, adj_node] : adjacents.nodes) {
        if (adj_node.can_have_data_from(node)) {
          Nodes copy = *this;
          const auto &[new_adj, new_node] = adj_node.move_data_from(node);
          copy.put(adj_key.col, adj_key.row, new_adj);
          copy.put(key.col, key.row, new_node);

          result.push_back(copy);
        }
      }
    }
    return result;
  }

  bool operator==(const Nodes &other) const { return nodes == other.nodes; }

  friend std::ostream &operator<<(std::ostream &os, const Nodes &nodes) {
    for (const auto &[k, v] : nodes.nodes) {
      os << "[" << k.col << "," << k.row << "]={" << v.has_target_data << ","
         << v.avail << "," << v.used << "}; ";
    }
    return os;
  };
};

struct NodesHash {
  size_t operator()(const Nodes &nodes) const { return nodes.hash_code(); };
};

Nodes parse_input(const vector<string> &input) {
  Nodes nodes;
  uint16_t max_x = 0;
  for (size_t i = 2; i < input.size(); i++) {
    const string &raw = input[i];
    const vector<string> tokens = util::split_by_spaces(raw);

    const string fs = tokens[0];

    string used = tokens[2];
    string avail = tokens[3];
    used.pop_back();
    avail.pop_back();

    const auto [x, y] = parse_position(fs);

    const Node node{static_cast<uint16_t>(stoi(used)),
                    static_cast<uint16_t>(stoi(avail)), false};

    max_x = max(max_x, x);

    nodes.put(x, y, node);
  }

  nodes.set_target_data();

  return nodes;
}

size_t solve_pt2(const vector<string> &input) {
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

    vector<Nodes> steps = nodes.make_all_perms();
    for (const Nodes &step : steps) {
      if (visited.insert(step).second) {
        cout << step << endl;
        q.push({step, depth + 1});
      }
    }
  }

  throw runtime_error("unreachable!");
}

} // namespace Day22
