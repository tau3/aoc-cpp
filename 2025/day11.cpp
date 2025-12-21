#include "day11.hpp"
#include "util.hpp"
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day11 {
using namespace std;

using Graph = unordered_map<string, vector<string>>;
using Memo = unordered_map<string, int>;

int count_paths(const Graph &graph, const string &from,
                const vector<string> &path, Memo &memo) {
  if (const auto search = memo.find(from); search != memo.end()) {
    return search->second;
  }

  if (from == "out") {
    int i = 0;
    for (const string &vertice : path) {
      if ((vertice == "dac") || (vertice == "fft")) {
        i += 1;
      }
      if (i == 2) {
        break;
      }
    }
    return (i == 2) ? 1 : 0;
  }

  const auto search = graph.find(from);
  if (search == graph.end()) {
    memo.emplace(path[path.size() - 1], 0);
    return 0;
  }

  vector<string> adjacent = search->second;
  if (adjacent.empty()) {
    memo.emplace(path[path.size() - 1], 0);
    return 0;
  }

  for (const string &vertice : path) {
    const auto search = find(adjacent.begin(), adjacent.end(), vertice);
    if (search != adjacent.end()) {
      adjacent.erase(search);
    }
  }

  int result = 0;
  for (const string &vertice : adjacent) {
    vector<string> new_path = path;
    new_path.push_back(from);
    result += count_paths(graph, vertice, new_path, memo);
  }
  if (!path.empty()) {
    memo.emplace(path[path.size() - 1], result);
  }
  return result;
}

Graph make_graph(const vector<string> &input) {
  Graph result;
  for (const string &line : input) {
    const vector<string> tokens = util::split(line, " ");
    const string from = tokens[0].substr(0, tokens[0].length() - 1);
    vector<string> to;
    for (size_t i = 1; i < tokens.size(); i++) {
      to.push_back(tokens[i]);
    }
    result.emplace(from, to);
  }
  return result;
}

int solve_day11_pt2(const vector<string> &input) {
  const Graph graph = make_graph(input);
  Memo memo;
  return count_paths(graph, "svr", {}, memo);
}

} // namespace Day11
