#include "day19.hpp"
#include "util.hpp"
#include <cstddef>
#include <string>
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

      // cout << molecule << ": " << key << " -> " << value << " = " << copy
      //      << endl;

      from = molecule.find(key, from + key.size());
    }
  }
  // util::print(result);

  return result.size();
}

size_t solve_day_19_pt1(const vector<string> &input) {
  Replacements replacements;
  for (size_t i = 0; i < input.size() - 2; i++) {
    const auto &tokens = util::split(input[i], " => ");
    replacements.push_back({tokens[0], tokens[1]});
  }

  const auto molecule = input[input.size() - 1];

  return solve(replacements, molecule);
}

} // namespace Day19
