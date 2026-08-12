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

unordered_set<string> make_all_replacements(const unordered_set<string> &vs,
                                            const string &key,
                                            const string &value) {
  unordered_set<string> result;
  for (const auto &molecule : vs) {
    size_t from = molecule.find(key, 0);
    while (from != molecule.npos) {
      auto copy = molecule;
      copy.replace(from, key.size(), value);
      result.emplace(copy);
      from = molecule.find(key, from + key.size());
    }
  }
  return result;
}

void add_all(unordered_set<string> &left, const unordered_set<string> &right) {
  for (const auto &r : right) {
    left.emplace(r);
  }
}

size_t solve_day19_pt2(const vector<string> &input) {
  Replacements replacements;
  for (size_t i = 0; i < input.size() - 2; i++) {
    const auto tokens = util::split(input[i], " => ");
    replacements.push_back({tokens[0], tokens[1]});
  }

  const auto molecule = input[input.size() - 1];

  unordered_set<string> variants = {"e"};
  size_t i = 0;
  while (true) {
    unordered_set<string> new_variants;
    for (const auto &[from, to] : replacements) {
      unordered_set<string> new_variants_1 =
          make_all_replacements(variants, from, to);
      for (const auto &v : new_variants_1) {
        cout << v << endl;
        if (v == molecule) {
          return i + 1;
        }
      }
      add_all(new_variants, new_variants_1);
      cout << i << endl;
    }
    i++;
    variants = new_variants;
  }
  throw runtime_error("unreachable");
}

} // namespace Day19
