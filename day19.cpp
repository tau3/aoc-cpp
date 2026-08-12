#include "day19.hpp"
#include "util.hpp"
#include <cstddef>
#include <deque>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Day19 {

size_t solve(const Replacements &replacements, const string &molecule) {
  unordered_set<string> result;
  for (const auto &entry : replacements) {
    const auto &key = entry.first;
    const auto &value = entry.second;

    size_t from = molecule.find(key, 0);
    while (from != molecule.npos) {
      auto copy = molecule;
      copy.replace(from, key.size(), value);
      result.emplace(copy);
      from = molecule.find(key, from + key.size());
    }
  }

  return result.size();
}

size_t solve_day19_pt1(const vector<string> &input) {
  Replacements replacements;
  for (size_t i = 0; i < input.size() - 2; i++) {
    const auto &tokens = util::split(input[i], " => ");
    replacements.push_back({tokens[0], tokens[1]});
  }

  const auto molecule = input[input.size() - 1];

  return solve(replacements, molecule);
}

using Graph = unordered_map<string, vector<string>>;

void insert_edge(Graph &graph, const string &from, const string &to) {
  if (graph.find(from) != graph.end()) {
    graph[from].push_back(to);
  } else {
    graph[from] = {to};
  }
}

struct State {
  string m;
  int depth;
  vector<string> variants;
};

vector<string> make_all_replacements(const vector<string> &vs,
                                     const string &key, const string &value) {
  vector<string> result;
  for (const auto &molecule : vs) {
    size_t from = molecule.find(key, 0);
    while (from != molecule.npos) {
      auto copy = molecule;
      copy.replace(from, key.size(), value);
      result.push_back(copy);
      from = molecule.find(key, from + key.size());
    }
  }
  return result;
}

size_t solve_day19_pt2(const vector<string> &input) {
  Graph graph;
  for (size_t i = 0; i < input.size() - 2; i++) {
    const auto tokens = util::split(input[i], " => ");
    const auto from = tokens[0];
    const auto to = tokens[1];
    insert_edge(graph, from, to);
  }

  const auto molecule = input[input.size() - 1];

  deque<State> q;
  unordered_set<string> visited;

  q.push_back({"e", 0, {"e"}});
  while (!q.empty()) {
    const auto &[v, d, vs] = q.front();
    q.pop_front();

    const auto &adjacent = graph.at(v);
    for (const auto &w : adjacent) {

      vector<string> variants = make_all_replacements(vs, v, w);
      for (const auto &variant : variants) {
        if (variant == molecule) {
          cout << "FOUND" << endl;
          return 0;
        }
      }

      if (visited.find(w) == visited.end()) {
        visited.emplace(w);
        q.push_back({w, d + 1, variants});
      }
    }
  }

  throw runtime_error("unreachable");
}

} // namespace Day19
