#ifndef INCLUDE_DAY_22_H
#define INCLUDE_DAY_22_H

#include <unordered_map>

namespace Day22 {

using namespace std;

enum class Effect { SHIELD, POISON, RECHARGE };

struct Player {
  int hp;
  int mana;
};

struct Boss {
  int hp;
  int damage;
};

struct State {
  Player player;
  Boss boss;
  bool is_player;
  int mana_spent;
  unordered_map<Effect, int> dots;
};

int solve(const State &states);

} // namespace Day22

#endif
