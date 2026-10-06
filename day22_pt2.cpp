#include "day22.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Day22 {

class Node {
private:
  uint16_t used;
  uint16_t avail;
  bool target;

  Node() = delete;

public:
  explicit Node(const uint16_t used, const uint16_t avail)
      : used(used), avail(avail), target(false) {}

  bool is_empty() const { return used == 0; }

  bool has_target_data() const { return target; }

  void set_target_data() { target = true; }

  size_t hash_code() const {
    size_t result = 17;
    result = result * 31 + used;
    result = result * 31 + avail;
    result = result * 31 + target;
    return result;
  };

  bool can_have_data_from(const Node &node) const { return avail >= node.used; }

  pair<Node, Node> move_data_from(const Node &node) const {
    Node to = *this;
    Node from = node;

    to.used += from.used;
    to.avail -= from.used;
    to.target = from.target;

    from.avail += from.used;
    from.used = 0;
    from.target = false;

    return {to, from};
  }

  bool operator==(const Node &other) const {
    return (used == other.used) && (avail == other.avail) &&
           (target == other.target);
  }
};

pair<size_t, size_t> parse_position(const string &fs) {
  vector<string> tokens = util::split(fs, "/");
  const string node = tokens[3];

  tokens = util::split(node, "-");

  string x = tokens[1];
  string y = tokens[2];

  x.erase(0, 1);
  y.erase(0, 1);

  return {stol(x), stol(y)};
}

class Nodes {
private:
  size_t width;
  size_t height;
  vector<Node> data;

  Nodes() = delete;

  const Node &at(const size_t x, const size_t y) const {
    assert(x < width && y < height);
    return data[y * width + x];
  }

  Node &at(const size_t x, const size_t y) {
    assert(x < width && y < height);
    return data[y * width + x];
  }

  vector<pair<pair<size_t, size_t>, Node &>>
  get_adjacent(const size_t x, const size_t y) const {
    vector<pair<pair<size_t, size_t>, Node &>> result;
    if (x > 0) {
      const pair<size_t, size_t> pos = {x - 1, y};
      const Node& n = at(x - 1, y);
      pair<pair<size_t, size_t>, Node&> z = {pos, n};
      // result.push_back(e);
      // result.push_back({pos, at(x - 1, y)});
    }
    // if (y > 0) {
    //   result.push_back({x, y - 1}, at(x, y - 1));
    // }
    // if (x < width) {
    //   result.push_back({x + 1, y}, at(x + 1, y));
    // }
    // if (y < height) {
    //   result.push_back({x, y + 1}, at(x, y + 1));
    // }
    return result;
  }

public:
  explicit Nodes(const size_t width, const size_t height,
                 const vector<Node> data)
      : width(width), height(height), data(data) {
    assert(data.size() == width * height);
  }

  size_t hash_code() const {
    size_t result = 0;
    for (const Node &node : data) {
      result = result * 31 + node.hash_code();
    }
    result = result * 31 + width;
    result = result * 31 + height;
    return result;
  }

  bool is_goal_data() const { return data[0].has_target_data(); }

  vector<Nodes> make_all_perms() const {
    vector<Nodes> result;
    for (size_t r = 0; r < height; r++) {
      for (size_t c = 0; c < width; c++) {
        const Node &node = at(c, r);
        if (node.is_empty()) {
          continue;
        }

        const auto adjacents = get_adjacent(c, r);
        for (const auto &[adj_pos, adj_node] : adjacents) {
          if (adj_node.can_have_data_from(node)) {
            Nodes copy = *this;
            const auto &[new_adj, new_node] = adj_node.move_data_from(node);
            copy.at(adj_pos.first, adj_pos.second) = new_adj;
            copy.at(c, r) = new_node;

            result.push_back(copy);
          }
        }
      }
    }
    return result;
  }

  bool operator==(const Nodes &other) const {
    if (other.width != width || other.height != height ||
        other.data.size() != data.size()) {
      return false;
    }

    for (size_t i = 0; i < data.size(); i++) {
      if (data[i] != other.data[i]) {
        return false;
      }
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const Nodes &nodes) {
    for (size_t r = 0; r < nodes.height; r++) {
      for (size_t c = 0; c < nodes.width; c++) {
        const Node &node = nodes.at(c, r);
        if (r == 0 && c == 0) {
          os << '(';
        } else {
          os << ' ';
        }
        if (node.is_empty()) {
          os << '_';
        } else {
          if (node.has_target_data()) {
            os << 'G';
          } else {
            os << '.';
          }
        }
        if (r == 0 && c == 0) {
          os << ')';
        } else {
          os << ' ';
        }
      }
      os << endl;
    }
    return os;
  };
};

struct NodesHash {
  size_t operator()(const Nodes &nodes) const { return nodes.hash_code(); };
};

Nodes parse_input(const vector<string> &input) {
  size_t width = 0;
  size_t height = 0;
  unordered_map<util::Point<size_t>, Node, util::PointHash> cache;

  for (size_t i = 2; i < input.size(); i++) {
    const string &raw = input[i];
    const vector<string> tokens = util::split_by_spaces(raw);

    const string fs = tokens[0];

    string used_raw = tokens[2];
    string avail_raw = tokens[3];
    used_raw.pop_back();
    avail_raw.pop_back();

    const auto [x, y] = parse_position(fs);

    uint16_t used = stoi(used_raw);
    uint16_t avail = stoi(avail_raw);
    const Node node(used, avail);

    width = max(width, x);
    height = max(height, y);

    cache.insert({util::Point(x, y), node});
  }

  width++;
  height++;
  vector<Node> data(width * height, Node(0, 0));
  for (const auto &[k, v] : cache) {
    const size_t x = k.col;
    const size_t y = k.row;
    data[y * width + x] = v;
  }
  data[data.size() - 1].set_target_data();

  return Nodes(width, height, data);
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
