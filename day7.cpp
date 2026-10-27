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

using Tree = unordered_map<string, vector<string>>;
using Weights = unordered_map<string, int>;

int total_weight(const string &node, const Tree &tree, const Weights &weights) {
  int result = weights.at(node);
  if (tree.find(node) == tree.end()) {
    return result;
  }

  const vector<string> &children = tree.at(node);
  for (const string &child : children) {
    result += total_weight(child, tree, weights);
  }
  return result;
}

string find_unbalanced_node(const string &node, const Tree &tree,
                            const Weights &weights) {
  const vector<string> &children = tree.at(node);

  unordered_map<int, int> total_weights;
  for (const string &child : children) {
    const int total = total_weight(child, tree, );
    if (total_weights.find(total) == total_weights.end()) {
      total_weights.insert({total, 1});
    } else {
      total_weights[total]++;
    }
  }

  int unbalanced_total_weight = -1;
  for (const auto &[total_weight, count] : total_weights) {
    if (count == 1) {
      unbalanced_total_weight = total_weight;
      break;
    }
  }

  if (unbalanced_total_weight == -1) {
    return node;
  }

  for (const string &child : children) {
    if (total_weight(child, tree, weights) == unbalanced_total_weight) {
      return find_unbalanced_node(child, tree, weights);
    }
  }

  throw runtime_error("unreachable");
}

// tknk or eqgvf
int solve_pt2(const vector<string> &input, const string &root) {
  Tree tree;
  Weights weights;

  for (const string &line : input) {
    vector<string> tokens = util::split(line, " ");
    const string &parent = tokens[0];

    // TODO extract
    string weight_str = tokens[1];
    weight_str = weight_str.substr(1, weight_str.size() - 1);
    const int weight = stoi(weight_str);

    weights.insert({parent, weight});

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

      tree.insert({parent, children});
    }
  }

  const string target = find_unbalanced_node(root, tree, weights);
  const vector<string> siblings = find_siblings(target, tree);
  int target_weight = total_weight(siblings[0], tree, weights);
  const vector<string> &children = tree.at(target);
  target_weight -= total_weight(children[0], tree, weights) * children.size();
  return target_weight;
}

} // namespace Day7
