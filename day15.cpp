#include "day15.hpp"
#include "util.hpp"
#include <algorithm>

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

int solve(const std::vector<Ingredient> &ingredients) {
  const int MAX = 100;
  int result = 0;
  for (int i = 0; i < MAX; i++) {
    int j = MAX - i;
    const int capacity =
        ingredients[0].capacity * i + ingredients[1].capacity * j;
    const int durability =
        ingredients[0].durability * i + ingredients[1].durability * j;
    const int flavor = ingredients[0].flavor * i + ingredients[1].flavor * j;
    const int texure = ingredients[0].texture * i + ingredients[1].texture * j;
    int total = std::max(capacity, 0) * std::max(durability, 0) *
                std::max(flavor, 0) * std::max(texure, 0);
    if (total > result) {
      result = total;
      std::cout << i << " " << j << std::endl;
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
