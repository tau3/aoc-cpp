#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Day23 {

using namespace std;

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

unordered_set<string> union_set(const unordered_set<string> &lhs,
                                const unordered_set<string> &rhs) {
  unordered_set<string> result;
  for (const string &item : lhs) {
    result.insert(item);
  }
  for (const string &item : rhs) {
    result.insert(item);
  }
  return result;
}

unordered_set<string> intersection(const unordered_set<string> &lhs,
                                   const unordered_set<string> &rhs) {
  unordered_set<string> result;
  const auto l = lhs;
  const auto r = rhs;
  set_intersection(l.begin(), l.end(), r.begin(), r.end(),
                   std::inserter(result, result.begin()));
  return result;
}

unordered_set<string> neighbour(const string &vertice,
                                const vector<pair<string, string>> &graph) {
  unordered_set<string> result;
  for (const auto &[lhs, rhs] : graph) {
    if (lhs == vertice) {
      result.insert(rhs);
    } else if (rhs == vertice) {
      result.insert(lhs);
    }
  }
  return result;
}

void bron_kerbosh(const unordered_set<string> &r, unordered_set<string> &p,
                  unordered_set<string> &x,
                  vector<unordered_set<string>> &cliques,
                  const vector<pair<string, string>> &graph) {
  if (p.empty() && x.empty()) {
    cliques.push_back(r);
  }

  while (!p.empty()) {
    const auto v = *p.begin();
    const auto neighbours = neighbour(v, graph);
    auto rr = r;
    rr.insert(v);
    auto p2 = intersection(p, neighbours);
    auto x2 = intersection(x, neighbours);
    bron_kerbosh(rr, p2, x2, cliques, graph);
    p.erase(v);
    x.insert(v);
  }
}

size_t solve_day23_pt2(const vector<string> &input) {
  vector<pair<string, string>> edges;
  unordered_set<string> p;
  for (const string &line : input) {
    const vector<string> tokens = split(line, "-");
    const string left = tokens[0];
    const string right = tokens[1];
    edges.push_back(make_edge(left, right));
    p.insert(left);
    p.insert(right);
  }

  vector<unordered_set<string>> cliques;
  unordered_set<string> r;
  unordered_set<string> x;
  bron_kerbosh(r, p, x, cliques, edges);

  size_t result = 0;
  for (const auto &clique : cliques) {
    result = max(result, clique.size());
    print(clique);
  }

  return result;
}

} // namespace Day23
