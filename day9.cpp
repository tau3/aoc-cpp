#include "day9.hpp"
#include "util.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Day9 {

using Graph = unordered_map<string, vector<pair<string, int>>>;

class DisjointSet {
  unordered_map<string, string> parents;
  unordered_map<string, int> ranks;

  void link(const string &x, const string &y) {
    if (ranks[x] > ranks[y]) {
      parents[y] = x;
    } else {
      parents[x] = y;
      if (ranks[x] == ranks[y]) {
        ranks[y] = ranks[y] + 1;
      }
    }
  }

public:
  void make_set(const string &x) {
    parents[x] = x;
    ranks[x] = 0;
  }

  string find_set(const string &x) {
    if (x != parents[x]) {
      parents[x] = find_set(parents[x]);
    }
    return parents[x];
  }

  void union_(const string &x, const string &y) {
    link(find_set(x), find_set(y));
  }
};

void mst_kruskal(const Graph &graph) {
  unordered_set<Edge> a;
  DisjointSet vs;
  for (const string &v : graph.key_set()) {
    vs.make_set(v);
  }
  vector<Edge> edges = graph.edges();
  edges.sort_ascending_by_weight();
  for (const Edge &edge : edges) {
    if (vs.find_set(edge.u()) != vs.find_set(edge.v())) {
      a.insert(edge);
      vs.union_(edge.u(), edge.v());
    }
  }

  return a;
}

template <typename K, typename V>
void compute_if_absent(unordered_map<K, V> &map, const K &key, const V &val) {
  if (map.find(key) == map.end()) {
    map[key];
  }
}

int solve_day9_pt1(const vector<string> &input) {
  Graph graph;
  for (const string &line : input) {
    const vector<string> tokens = util::split(line, " ");
    const string from = tokens[0];
    const string to = tokens[2];
    const int distance = stoi(tokens[4]);

    vector<pair<string, int>> adj = graph[from];
    adj.push_back({to, distance});
    adj = graph[to];
    adj.push_back({from, distance});
  }


  int result = 0;
  const unordered_set<Edge> mst = mst_kruskal(graph);
  for (const Edge &edge : mst) {
    result += graph.weight(edge);
  }
  return result;
}

} // namespace Day9
