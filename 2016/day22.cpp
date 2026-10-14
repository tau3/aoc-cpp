#include "day22.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace Day22 {

class Node {
private:
  uint8_t used;
  uint8_t avail;

public:
  explicit Node(const uint8_t used, const uint8_t avail)
      : used(used), avail(avail) {}

  bool is_empty() const { return used == 0; }

  uint8_t get_used() const { return used; }

  uint8_t get_avail() const { return avail; }
};

bool operator==(const Node &lhs, const Node &rhs) {
  return (lhs.get_used() == rhs.get_used()) &&
         (lhs.get_avail() == rhs.get_avail());
}

Node make_node(const string &raw) {
  const vector<string> tokens = util::split_by_spaces(raw);

  string used = tokens[2];
  string avail = tokens[3];

  used.pop_back();
  avail.pop_back();

  return Node(stoi(used), stoi(avail));
}

size_t solve(const vector<string> &input) {
  vector<Node> nodes;
  for (size_t i = 2; i < input.size(); i++) {
    const string &line = input[i];
    const Node node = make_node(line);
    nodes.push_back(node);
  }

  size_t result = 0;
  const size_t count = nodes.size();
  for (size_t i = 0; i < count; i++) {
    const Node &left = nodes[i];
    if (left.is_empty()) {
      continue;
    }

    for (size_t j = 0; j < count; j++) {
      const Node &right = nodes[j];
      if (left == right) {
        continue;
      }

      if (left.get_used() <= right.get_avail()) {
        result++;
      }
    }
  }
  return result;
}

} // namespace Day22
