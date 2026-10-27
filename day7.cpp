#include "day7.hpp"
#include "util.hpp"
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Day7 {

string solve_pt1(const vector<string> &input) {
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
        if (child.ends_with(',')) {
          child.pop_back();
        }

        children.insert(child);
        nodes.insert(child);
      }
    }
  }

  for (const string &node : nodes) {
    if (!children.contains(node)) {
      return node;
    }
  }

  throw runtime_error("unreachable");
}

string find_unbalanced_node(
    const string &node,
    const unordered_map<string, vector<string>> &node_to_children) {
  const vector<string> &children = node_to_children.at(node);

  unordered_map<int, int> weights;
  for (const string &child : children) {
    const int total = total_weight(child);
    if (weights.find(total) == weights.end()) {
      weights.insert({total, 1});
    } else {
      weights[total]++;
    }
  }

  int unbalanced_total_weight = -1;
  for (const auto &[weight, count] : weights) {
    if (count == 1) {
      unbalanced_total_weight = weight;
      break;
    }
  }

  if (unbalanced_total_weight == -1) {
    return node;
  }

  for (const string &child : children) {
    if (total_weight(child) == unbalanced_total_weight) {
      return find_unbalanced_node(child, node_to_children);
    }
  }

  throw runtime_error("unreachable");
}

// tknk or eqgvf
int solve_pt2(const vector<string> &input, const string &root) {
  unordered_map<string, vector<string>> node_to_children;
  unordered_map<string, int> node_to_weight;

  for (const string &line : input) {
    vector<string> tokens = util::split(line, " ");
    const string &parent = tokens[0];

    // TODO extract
    string weight_str = tokens[1];
    weight_str = weight_str.substr(1, weight_str.size() - 1);
    const int weight = stoi(weight_str);

    node_to_weight.insert({parent, weight});

    const size_t count = tokens.size();
    if (count > 2) {
      vector<string> children;
      for (size_t i = 3; i < count; i++) {
        string &child = tokens[i];
        if (child.ends_with(',')) {
          child.pop_back();
        }

        children.push_back(child);
      }

      node_to_children.insert({parent, children});
    }
  }

  const string target = find_unbalanced_node(root, node_to_children);
  const vector<string> siblings = find_siblings(target);
  const int target_weight = total_weight(siblings[0]);
  const vector<string> &children = node_to_children.at(target);
  target_weight -= total_weight(children[0]) * children.size();
  return target_weight;
}

} // namespace Day7
