#ifndef INCLUDE_DAY_22_H
#define INCLUDE_DAY_22_H

#include <deque>
#include <unordered_map>

namespace Day22 {

using namespace std;

enum class Effects { SHIELD, POISON, RECHARGE };

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
  unordered_map<Effects, int> dots;
};

int solve(deque<State> &states);

} // namespace Day22

#endif
