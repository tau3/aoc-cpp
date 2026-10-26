#include "day7.hpp"
#include "util.hpp"
#include <cstddef>
#include <stdexcept>
#include <unordered_set>

namespace Day7 {

string solve(const vector<string> &input) {
  unordered_set<string> nodes;
  unordered_set<string> children;

  for (const string &line : input) {
    vector<string> tokens = util::split(line, " ");
    const string &parent = tokens[0];
    nodes.insert(parent);

    const size_t count = tokens.size();

    if (count > 2) {
      for (size_t i = 3; i < count; i++) {
        string &child = tokens[i];
        child.pop_back();

        children.insert(child);
        nodes.insert(child);
      }
    }

    for (const string &node : nodes) {
      if (!children.contains(node)) {
        return node;
      }
    }
  }

  throw runtime_error("unreachable");
}

} // namespace Day7
