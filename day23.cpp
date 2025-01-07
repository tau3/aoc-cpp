#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Day23 {

using namespace std;

using Graph = unordered_map<string, vector<string>>;

void add_edge(Graph &graph, const string &left, const string &right) {
  if (graph.find(left) != graph.end()) {
    graph[left].push_back(right);
  } else {
    graph[left] = {right};
  }

  if (graph.find(right) != graph.end()) {
    graph[right].push_back(left);
  } else {
    graph[right] = {left};
  }
}

pair<string, string> make_edge(const string &from, const string &to) {
  if (from < to) {
    return {from, to};
  } else {
    return {to, from};
  }
}

bool is_valid_cycle(const string &cycle) {
  return (cycle[0] == 't') || (cycle[3] == 't') || (cycle[6] == 't');
}

size_t solve(vector<pair<string, string>> edges) {
  unordered_set<string> result;
  for (size_t i = 0; i < edges.size(); ++i) {
    for (size_t j = i + 1; j < edges.size(); ++j) {
      const auto &left = edges[i];
      const auto &right = edges[j];
      if (left.first == right.first) {
        const auto edge = make_edge(left.second, right.second);
        if (find(edges.begin(), edges.end(), edge) != edges.end()) {
          vector<string> edges = {left.first, left.second, right.second};
          sort(edges.begin(), edges.end());
          const string cycle = edges[0] + "," + edges[1] + "," + edges[2];
          if (is_valid_cycle(cycle)) {
            cout << cycle << endl;
            result.insert(cycle);
          }
        }
      }
    }
  }
  return result.size();
}

size_t solve_day23_pt1(const vector<string> &input) {
  vector<pair<string, string>> edges;
  for (const string &line : input) {
    const vector<string> tokens = split(line, "-");
    const string left = tokens[0];
    const string right = tokens[1];
    edges.push_back(make_edge(left, right));
  }
  return solve(edges);
}

} // namespace Day23
