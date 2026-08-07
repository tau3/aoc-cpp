#include "day15.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

namespace Day15 {

struct Ingredient {
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
};

Ingredient parse_line(const std::string &line) {
  const std::vector<std::string> tokens = util::split(line, " ");
  std::string capacity = tokens[2];
  std::string durability = tokens[4];
  std::string flavor = tokens[6];
  std::string texture = tokens[8];
  std::string calories = tokens[10];

  capacity.pop_back();
  durability.pop_back();
  flavor.pop_back();
  texture.pop_back();

  return Ingredient{std::stoi(capacity), std::stoi(durability),
                    std::stoi(flavor), std::stoi(texture), std::stoi(calories)};
}

int calc_total(const std::vector<Ingredient> &ingredients,
               const std::vector<int> &proportion) {
  assert(ingredients.size() == proportion.size());
  assert(std::accumulate(proportion.begin(), proportion.end(), 0) == 100);

  int capacity = 0;
  int durability = 0;
  int flavor = 0;
  int texture = 0;
  for (size_t i = 0; i < ingredients.size(); i++) {
    capacity += ingredients[i].capacity * proportion[i];
    durability += ingredients[i].durability * proportion[i];
    flavor += ingredients[i].flavor * proportion[i];
    texture += ingredients[i].texture * proportion[i];
  }
  return std::max(capacity, 0) * std::max(durability, 0) * std::max(flavor, 0) *
         std::max(texture, 0);
}

int solve(const std::vector<Ingredient> &ingredients) {
  const int MAX = 100;
  int result = 0;
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX - i; j++) {
      for (int k = 0; k < MAX - i - j; k++) {
        const int l = MAX - i - j - k;
        const int total = calc_total(ingredients, {i, j, k, l});
        if (total > result) {
          result = total;
        }
      }
    }
  }
  return result;
}

int solve_day15_pt1(const std::vector<std::string> &input) {
  std::vector<Ingredient> ingredients;
  for (const auto &line : input) {
    const Ingredient ingredient = parse_line(line);
    ingredients.push_back(ingredient);
  }

  return solve(ingredients);
}

} // namespace Day15
